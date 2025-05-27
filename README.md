# IrrigacaoChuva

# Descrição do projeto

Este projeto utiliza um ESP32 para gerenciar um sistema de captação e armazenamento de água da chuva, com foco na automação e eficiência. O sistema lê o nível de água em um reservatório e a umidade do solo, acionando automaticamente uma bomba d'água quando necessário. Além disso, envia notificações automáticas via WhatsApp, utilizando a API do CallMeBot, sempre que o sistema executa ações importantes ou detecta situações críticas.

O sistema também é capaz de integrar-se com servidores via protocolo MQTT, permitindo o monitoramento remoto e o envio de alertas quando o nível de água atinge 90% da capacidade, garantindo segurança e eficiência.

# Funcionalidades

✅ Monitoramento da umidade do solo.

✅ Medição do nível de água no reservatório.

✅ Acionamento automático da bomba d'água.

✅ Envio de notificações via WhatsApp com informações do sistema.

✅ Comunicação via protocolo MQTT para integração com sistemas remotos.

✅ Comunicação via Internet (TCP/IP).

# Software Desenvolvido

O código foi desenvolvido utilizando  Wokwi, com a linguagem C++ e as bibliotecas:

WiFi.h — para conexão com a internet via rede Wi-Fi.

HTTPClient.h — para realizar requisições HTTP.

Função urlencode() — para garantir o envio correto das mensagens pela URL.

API CallMeBot — serviço gratuito para envio de mensagens via WhatsApp.

# Estrutura do código:

setup_wifi() — conecta o ESP32 à rede Wi-Fi.

sendWhatsAppMessage() — envia mensagens via CallMeBot.

urlencode() — codifica a mensagem para o formato URL.

loop() — realiza leituras, controla a bomba e envia notificações a cada 30 segundos.

O sistema pode ser facilmente expandido para incluir comandos MQTT para controle remoto da bomba ou leituras sob demanda.


# Como executar o projeto
1- Acesse Wowki

2- Realize o upload do arquivo "wifi-scan.ino", "diagram.json", "libraries.txt"

3- Na parte // CallMeBot - WhatsApp, com o numero +34694234184 envie a seguinte mensagem "I allow callmebot to send me messages"

4- Ele te dara seu numero e sua chave unicá

5- Agora substitua no código na parte // CallMeBot - WhatsApp, com seu numero e key

6- Para fazer o teste execute o wokwi, e mande mensagem para o callmebot "Resume"

## 🔩 Hardware Utilizado (Simulado no Wokwi)

| Componente                   | Substituto na Simulação Wokwi        | Função Simulada                                |
|-----------------------------|--------------------------------------|------------------------------------------------|
| Sensor de umidade do solo   | Potenciômetro                        | Simula variação de umidade no solo             |
| Bomba d’água                | LED com resistor de 220Ω             | Representa acionamento da bomba                |
| Sensor de nível HC-SR04     | Sensor ultrassônico (Wokwi nativo)   | Mede a distância até o nível da água           |
| ESP32 NodeMCU               | ESP32 Dev Board                      | Controlador principal com conectividade Wi-Fi  |
| Relé 5V                     | Simulado por controle de LED         | Aciona bomba (LED) conforme leitura dos sensores |

## 🌐 Protocolos e Módulos de Comunicação

- **Wi-Fi (TCP/IP)**: conexão do ESP32 à internet.
- **MQTT (Mosquitto Broker)**: protocolo de mensagens leves para IoT, utilizado para publicar os dados de nível do reservatório.
- **HTTP (API CallMeBot)**: envio de mensagens via requisições HTTP para o WhatsApp.
- **PubSubClient**: biblioteca usada para comunicação MQTT no ESP32.
- **Python Script**: assina o tópico MQTT e interage com a API CallMeBot (no cenário completo com broker externo).

## 📡 Comunicação via Internet e MQTT

- O ESP32 conecta-se a uma rede Wi-Fi e publica mensagens em tópicos MQTT, como nível do reservatório e status de irrigação.
- Quando a caixa d’água atinge 90% de capacidade, uma mensagem MQTT é publicada.
- Um servidor local com um script Python assina esse tópico e envia alertas via API CallMeBot para o WhatsApp.
- Toda a comunicação utiliza o protocolo **TCP/IP**.

