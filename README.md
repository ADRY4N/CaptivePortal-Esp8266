# CaptivePortal-Esp8266

Este é um projeto de Captive Portal desonesto que roda na placa de desenvolvimento ESP8266, como o NodeMCU. É uma ferramenta de engenharia social que gera uma rede Wi-Fi para incentivar as pessoas a se conectarem a ela e inserir credenciais.

![Image](https://github.com/user-attachments/assets/774dc5e3-ff41-41f0-8cf7-e1f0d61bf6b5)
![Image](https://github.com/user-attachments/assets/8ec9bda7-9f34-4565-93e0-b64d2807f552)
![Image](https://github.com/user-attachments/assets/67b7b3ff-22d0-4cb5-a7d6-cc6ef91c435b)

<img width="473" height="713" alt="Image" src="https://github.com/user-attachments/assets/76ae4dce-2c96-43f8-a215-95bfa502ed3e" />

## Funcionalidades

**Painel de Administração:** Permite selecionar qualquer tema de portal cativo.
* **Temas Customizáveis:** As interfaces web do usuário (temas) são armazenadas no LittleFS. É possível selecionar o tema ativo e fazer upload de novos temas diretamente pela página web.
**Armazenamento Persistente:** As configurações como SSID, senha, canal e tema da página são salvas na EEPROM.
* **Captura de Dados:** Os dados dos usuários cadastrados são salvos no LittleFS.

## Exemplo de Interface

A interface padrão simula um portal de login de um CyberCafé, solicitando nome completo e e-mail para acessar a rede Wi-Fi gratuita.

![Exemplo de Portal](https://raw.githubusercontent.com/seu-usuario/CaptivePortal-Esp8266/main/portal_example.jpg)

## Configuração

### Pré-requisitos

* Arduino IDE v1.8.19.
* Placa de desenvolvimento ESP8266 (ex: NodeMCU).
* Drivers da placa devidamente instalados.
* Plugin LittleFS para ESP8266 instalado na Arduino IDE.

### Passos

1.  Conecte seu ESP8266 ao computador.
2.  Abra o projeto na Arduino IDE.
3.  Certifique-se de que a placa e a porta COM estão selecionadas corretamente.
4.  Faça o upload do sistema de arquivos LittleFS para o ESP8266.
5.  Carregue o código para o ESP8266.

## Uso

### Rede Wi-Fi Padrão

**SSID:** CyberCafe-Padrao
**Senha:** visitante 

### Acesso ao Painel de Administração

1.  Conecte-se à rede Wi-Fi criada pelo ESP8266.
2.  Em alguns dispositivos, pode ser necessário selecionar a opção "Usar esta rede como está" para que o portal de login apareça.
3.  Acesse o painel de administração através do seguinte endereço: `http://172.217.28.1/admin`.

**Usuário:** admin
**Senha:** cafe123

![Acesso ADM](https://raw.githubusercontent.com/seu-usuario/CaptivePortal-Esp8266/main/admin_login.jpg)

## ISENÇÃO DE RESPONSABILIDADE

O código fonte fornecido neste repositório é apenas para **uso educacional**. O roubo de credenciais é ilegal. O autor não se responsabiliza por quaisquer ações feitas em seu nome. Este código é fornecido sem garantias ou responsabilidades. Seja responsável.
