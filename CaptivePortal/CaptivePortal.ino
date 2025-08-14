/*
  Projeto Portal Cativo para CyberCafé com Painel de Administração
  Versão com Seleção de Tema e Correção de Redirect:
  - Interfaces web do usuário (temas) armazenadas no LittleFS.
  - Administrador pode selecionar o tema ativo e fazer upload de novos temas.
  - Configurações (rede e tema) salvas na EEPROM.
  - Dados dos usuários cadastrados salvos no LittleFS.
*/

#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <EEPROM.h>
#include <LittleFS.h>
#include "web.h"

// --- Estrutura para armazenar as configurações na EEPROM ---
struct Config {
  char ssid[33];
  char password[65];
  int channel;
  char theme[33]; // Nome do arquivo do tema ativo
  int magic;
};

// --- Configurações de Rede e Servidor ---
const byte DNS_PORT = 53;
DNSServer dnsServer;
AsyncWebServer server(80);
Config config;

// --- Credenciais do Admin ---
const char* adminUser = "admin";
const char* adminPass = "cafe123";

// --- Nome do arquivo de usuários ---
const char* userFile = "/usuarios.csv";

// --- Protótipos de Funções ---
void loadConfiguration();
void saveConfiguration();
String generateAdminPage();
void handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);

void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando Portal Cativo (versão com Correção de Redirect)...");

  EEPROM.begin(sizeof(Config));
  loadConfiguration();

  if (!LittleFS.begin()) {
    Serial.println("Erro ao montar o LittleFS.");
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAP(config.ssid, config.password, config.channel);
  
  IPAddress apIP = WiFi.softAPIP();
  Serial.print("SSID: "); Serial.println(config.ssid);
  Serial.print("IP do Portal: http://"); Serial.println(apIP);
  Serial.print("Tema Ativo: "); Serial.println(config.theme);

  dnsServer.start(DNS_PORT, "*", apIP);

  // --- Rotas do Servidor Web ---

  // Rota para a página de administração (deve ser específica e vir primeiro)
  server.on("/admin", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (!request->authenticate(adminUser, adminPass)) return request->requestAuthentication();
    request->send(200, "text/html", generateAdminPage());
  });

  // Rota para salvar as configurações
  server.on("/saveconfig", HTTP_POST, [](AsyncWebServerRequest *request) {
    if (!request->authenticate(adminUser, adminPass)) return request->requestAuthentication();
    if (request->hasParam("ssid", true)) strlcpy(config.ssid, request->getParam("ssid", true)->value().c_str(), sizeof(config.ssid));
    if (request->hasParam("password", true)) strlcpy(config.password, request->getParam("password", true)->value().c_str(), sizeof(config.password));
    if (request->hasParam("channel", true)) config.channel = request->getParam("channel", true)->value().toInt();
    if (request->hasParam("theme", true)) strlcpy(config.theme, request->getParam("theme", true)->value().c_str(), sizeof(config.theme));
    
    saveConfiguration();
    
    String responsePage = "<html><head><title>Reiniciando...</title><meta http-equiv='refresh' content='5;url=/admin'></head><body>";
    responsePage += "<h2>Configuracoes salvas!</h2><p>O dispositivo esta reiniciando. Voce sera redirecionado para a pagina de administracao em 5 segundos.</p>";
    responsePage += "</body></html>";
    request->send(200, "text/html", responsePage);
    
    delay(1000);
    ESP.restart();
  });

  // Rota para o formulário de cadastro do usuário
  server.on("/register", HTTP_POST, [](AsyncWebServerRequest *request){
      String allData = "";
      int params = request->params();
      for(int i=0; i<params; i++){
        AsyncWebParameter* p = request->getParam(i);
        if(i > 0) allData += ", ";
        allData += p->name() + ": " + p->value();
      }
      
      File file = LittleFS.open(userFile, "a");
      if(file) {
        file.println(allData);
        file.close();
        Serial.printf("Novo cadastro salvo: %s\n", allData.c_str());
      }
      request->send(200, "text/html", "<h1>Obrigado por se cadastrar!</h1><p>Você já pode acessar a internet.</p>");
  });

  // Rota para upload de novos temas
  server.on("/upload", HTTP_POST, 
    [](AsyncWebServerRequest *request) {
        if (!request->authenticate(adminUser, adminPass)) return request->requestAuthentication();
        String responsePage = "<html><head><title>Upload Concluido</title><meta http-equiv='refresh' content='3;url=/admin'></head><body>";
        responsePage += "<h2>Upload concluido com sucesso!</h2><p>Voce sera redirecionado para a pagina de administracao em 3 segundos.</p>";
        responsePage += "</body></html>";
        request->send(200, "text/html", responsePage);
    }, 
    handleUpload
  );

  // O onNotFound é o coração do portal cativo.
  // Ele captura todas as outras requisições e decide o que fazer.
  server.onNotFound([](AsyncWebServerRequest *request) {
    // Se a requisição for para um arquivo que existe, sirva-o.
    if (LittleFS.exists(request->url())) {
        String contentType = "text/plain";
        if (request->url().endsWith(".css")) contentType = "text/css";
        else if (request->url().endsWith(".js")) contentType = "application/javascript";
        else if (request->url().endsWith(".png")) contentType = "image/png";
        else if (request->url().endsWith(".jpg")) contentType = "image/jpeg";
        else if (request->url().endsWith(".ico")) contentType = "image/x-icon";
        request->send(LittleFS, request->url(), contentType);
        return;
    }
    
    // Se não for um arquivo, é uma requisição de portal cativo.
    // Sirva a página de tema principal diretamente, sem redirecionar.
    String themePath = "/" + String(config.theme);
    if (LittleFS.exists(themePath)) {
        request->send(LittleFS, themePath, "text/html");
    } else {
        request->send(200, "text/plain", "Portal Ativo. Tema nao encontrado.");
    }
  });

  server.begin();
  Serial.println("Servidor HTTP iniciado.");
}

void loop() {
  dnsServer.processNextRequest();
}

// --- Funções Auxiliares ---

String generateAdminPage() {
  String page = FPSTR(ADMIN_HTML);
  
  String themeOptions = "";
  Dir dir = LittleFS.openDir("/");
  while (dir.next()) {
    if (dir.fileName().endsWith(".html")) {
      String themeFile = dir.fileName();
      // CORREÇÃO: Verifica se o nome do arquivo começa com "/" antes de remover.
      if (themeFile.startsWith("/")) {
        themeFile.remove(0, 1);
      }
      themeOptions += "<option value='" + themeFile + "'";
      if (themeFile == String(config.theme)) {
        themeOptions += " selected";
      }
      themeOptions += ">" + themeFile + "</option>";
    }
  }
  page.replace("<!--THEME_OPTIONS-->", themeOptions);

  String userTable = "<table><tr><th>Dados Enviados</th></tr>";
  File file = LittleFS.open(userFile, "r");
  if (file) {
    while (file.available()) {
      String line = file.readStringUntil('\n');
      line.trim();
      if (!line.isEmpty()) {
        userTable += "<tr><td>" + line + "</td></tr>";
      }
    }
    file.close();
  } else {
    userTable += "<tr><td>Nenhum usuário cadastrado ainda.</td></tr>";
  }
  userTable += "</table>";
  page.replace("<!--USER_LIST-->", userTable);

  return page;
}

void handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
    if (!request->authenticate(adminUser, adminPass)) return request->requestAuthentication();
    
    String path = "/" + filename;
    if (index == 0) {
        Serial.printf("Upload iniciado: %s\n", path.c_str());
        request->_tempFile = LittleFS.open(path, "w");
        if (!request->_tempFile) {
            Serial.println("ERRO: Nao foi possivel criar o arquivo para upload.");
            return;
        }
    }
    if (len > 0 && request->_tempFile) {
        if (request->_tempFile.write(data, len) != len) {
            Serial.println("ERRO: Falha ao escrever no arquivo. O disco pode estar cheio.");
        }
    }
    if (final) {
        if (request->_tempFile) {
            request->_tempFile.close();
            Serial.printf("Upload de %s concluído, %u bytes\n", path.c_str(), index + len);
        } else {
            Serial.println("ERRO: Upload finalizado mas o arquivo nao estava aberto.");
        }
    }
}

void loadConfiguration() {
  EEPROM.get(0, config);
  if (config.magic != 12345) {
    Serial.println("EEPROM não inicializada. Usando valores padrão.");
    strlcpy(config.ssid, "CyberCafe-Padrao", sizeof(config.ssid));
    strlcpy(config.password, "visitante", sizeof(config.password));
    config.channel = 6;
    strlcpy(config.theme, "Cybercafe.html", sizeof(config.theme));
    config.magic = 12345;
    saveConfiguration();
  } else {
    Serial.println("Configuração carregada da EEPROM.");
  }
}

void saveConfiguration() {
  EEPROM.put(0, config);
  if (EEPROM.commit()) {
    Serial.println("Configuração salva na EEPROM.");
  } else {
    Serial.println("Erro ao salvar na EEPROM.");
  }
}
