# CaptivePortal-Esp8266

# CaptivePortal-Esp8266

[cite_start]Este é um projeto de Captive Portal desonesto que roda na placa de desenvolvimento ESP8266, como o NodeMCU (clones incluídos)[cite: 2]. [cite_start]É uma ferramenta de engenharia social que gera uma rede Wi-Fi para incentivar as pessoas a se conectarem a ela e inserir credenciais[cite: 3].

![NodeMCU](https://raw.githubusercontent.com/seu-usuario/CaptivePortal-Esp8266/main/nodemcu_image.jpg)

## Funcionalidades

* [cite_start]**Painel de Administração:** Permite selecionar qualquer tema de portal cativo[cite: 4].
* **Temas Customizáveis:** As interfaces web do usuário (temas) são armazenadas no LittleFS. [cite_start]É possível selecionar o tema ativo e fazer upload de novos temas diretamente pela página web[cite: 5].
* [cite_start]**Armazenamento Persistente:** As configurações como SSID, senha, canal e tema da página são salvas na EEPROM[cite: 6].
* [cite_start]**Captura de Dados:** Os dados dos usuários cadastrados são salvos no LittleFS[cite: 7].

## Exemplo de Interface

A interface padrão simula um portal de login de um CyberCafé, solicitando nome completo e e-mail para acessar a rede Wi-Fi gratuita.

![Exemplo de Portal](https://raw.githubusercontent.com/seu-usuario/CaptivePortal-Esp8266/main/portal_example.jpg)

## Configuração

### Pré-requisitos

* [cite_start]Arduino IDE v1.8.19[cite: 14].
* [cite_start]Placa de desenvolvimento ESP8266 (ex: NodeMCU)[cite: 2, 13].
* [cite_start]Drivers da placa devidamente instalados[cite: 13].
* [cite_start]Plugin LittleFS para ESP8266 instalado na Arduino IDE[cite: 15].

### Passos

1.  [cite_start]Conecte seu ESP8266 ao computador[cite: 13].
2.  Abra o projeto na Arduino IDE.
3.  Certifique-se de que a placa e a porta COM estão selecionadas corretamente.
4.  Faça o upload do sistema de arquivos LittleFS para o ESP8266.
5.  Carregue o código para o ESP8266.

## Uso

### Rede Wi-Fi Padrão

* [cite_start]**SSID:** CyberCafe-Padrao [cite: 38]
* [cite_start]**Senha:** visitante [cite: 39]

### Acesso ao Painel de Administração

1.  Conecte-se à rede Wi-Fi criada pelo ESP8266.
2.  [cite_start]Em alguns dispositivos, pode ser necessário selecionar a opção "Usar esta rede como está" para que o portal de login apareça[cite: 55].
3.  [cite_start]Acesse o painel de administração através do seguinte endereço: `http://172.217.28.1/admin`[cite: 52].

* [cite_start]**Usuário:** admin [cite: 53]
* [cite_start]**Senha:** cafe123 [cite: 54]

![Acesso ADM](https://raw.githubusercontent.com/seu-usuario/CaptivePortal-Esp8266/main/admin_login.jpg)

## ISENÇÃO DE RESPONSABILIDADE

[cite_start]O código fonte fornecido neste repositório é apenas para **uso educacional**[cite: 9]. [cite_start]O roubo de credenciais é ilegal[cite: 10]. [cite_start]O autor não se responsabiliza por quaisquer ações feitas em seu nome[cite: 11]. [cite_start]Este código é fornecido sem garantias ou responsabilidades[cite: 11]. Seja responsável.
