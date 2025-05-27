#include <WiFi.h>
#include <HTTPClient.h>

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Pinos
const int trigPin = 5;
const int echoPin = 18;
const int moisturePin = 36;
const int pumpPin = 2;

// CallMeBot - WhatsApp
String phoneNumber = "+553599701989"; // Seu número
String apiKey = "1081572";            // Sua API Key

bool bombaLigada = false;

void setup_wifi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando-se ao WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" conectado!");
}

void sendWhatsAppMessage(String msg) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber +
                 "&text=" + urlencode(msg) +
                 "&apikey=" + apiKey;

    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.println("✅ Mensagem enviada via WhatsApp!");
    } else {
      Serial.print("❌ Erro ao enviar mensagem: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi não conectado");
  }
}

String urlencode(String str) {
  String encodedString = "";
  char c;
  char code0;
  char code1;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == ' ') {
      encodedString += '+';
    } else if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) code1 = (c & 0xf) - 10 + 'A';
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) code0 = c - 10 + 'A';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
    }
  }
  return encodedString;
}

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  setup_wifi();
}

void loop() {
  // Leitura da distância
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  // Leitura da umidade
  int moistureValue = analogRead(moisturePin);
  float moisturePercent = map(moistureValue, 0, 4095, 100, 0);

  // Controle da bomba
  if (moisturePercent < 30 && distance < 10) {
    digitalWrite(pumpPin, HIGH);
    bombaLigada = true;
  } else {
    digitalWrite(pumpPin, LOW);
    bombaLigada = false;
  }

  // Envio de mensagem periódica com todos os dados
  String mensagem = "📡 Leitura do sistema:\n";
  mensagem += "🌡 Umidade do solo: " + String(moisturePercent, 1) + "%\n";
  mensagem += "📏 Nível da água: " + String(distance, 1) + " cm\n";
  mensagem += "🚰 Bomba: " + String(bombaLigada ? "Ligada" : "Desligada");

  Serial.println(mensagem); // Exibe no Serial Monitor
  sendWhatsAppMessage(mensagem);

  delay(30000); // Aguarda 30 segundos
}
