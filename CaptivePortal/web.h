#pragma once
#include <pgmspace.h>

// Conteúdo da página de administração (admin.html)
const char ADMIN_HTML[] PROGMEM = R"raw(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Painel de Administração</title>
    <style>
        body { font-family: Arial, sans-serif; background-color: #f4f4f4; margin: 0; padding: 20px; }
        .container { max-width: 600px; margin: auto; background: #fff; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }
        h1, h2 { color: #333; }
        label { display: block; margin-bottom: 5px; font-weight: bold; }
        input[type="text"], input[type="password"], input[type="number"], select {
            width: calc(100% - 22px); padding: 10px; margin-bottom: 15px; border: 1px solid #ddd; border-radius: 4px;
        }
        input[type="submit"], button {
            background-color: #007bff; color: white; padding: 10px 15px; border: none; border-radius: 4px; cursor: pointer; font-size: 16px;
        }
        input[type="submit"]:hover, button:hover { background-color: #0056b3; }
        hr { border: 0; border-top: 1px solid #eee; margin: 20px 0; }
        table { width: 100%; border-collapse: collapse; margin-top: 10px; }
        th, td { padding: 10px; text-align: left; border-bottom: 1px solid #ddd; }
        th { background-color: #f8f8f8; }
        #user-list-container { max-height: 300px; overflow-y: auto; border: 1px solid #ddd; border-radius: 4px; padding: 5px; }
    </style>
</head>
<body>
    <div class="container">
        <h1>Painel de Administração</h1>
        
        <h2>Configurações Gerais</h2>
        <form action="/saveconfig" method="POST">
            <label for="ssid">Nome da Rede (SSID):</label>
            <input type="text" id="ssid" name="ssid" required>

            <label for="password">Senha da Rede:</label>
            <input type="password" id="password" name="password">

            <label for="channel">Canal (1-13):</label>
            <input type="number" id="channel" name="channel" min="1" max="13" required>

            <label for="theme">Tema da Página de Cadastro:</label>
            <select id="theme" name="theme">
                <!--THEME_OPTIONS-->
            </select>

            <input type="submit" value="Salvar e Reiniciar">
        </form>

        <hr>

        <h2>Adicionar Novo Tema</h2>
        <form action="/upload" method="POST" enctype="multipart/form-data">
            <label for="file">Selecione o arquivo (.html):</label>
            <input type="file" id="file" name="file_upload" required>
            <input type="submit" value="Fazer Upload">
        </form>
        
        <hr>

        <h2>Usuários Cadastrados</h2>
        <div id="user-list-container">
            <!--USER_LIST-->
        </div>
    </div>
</body>
</html>
)raw";
