#include <WiFi.h>
#include <PubSubClient.h>

#define PIR_PIN 13
#define LED_PIN 2

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

bool ultimoEstado = false;

void setupWifi() {
  WiFi.begin(ssid, password);

  Serial.print("Conectando ao WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");

    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println(" conectado!");
    } else {
      Serial.println(" falhou!");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  setupWifi();

  client.setServer(mqtt_server, 1883);
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  bool movimento = digitalRead(PIR_PIN);

  digitalWrite(LED_PIN, movimento);

  if (movimento != ultimoEstado) {

    if (movimento) {
      Serial.println("Movimento detectado");
      Serial.println("Publicando MQTT...");

      client.publish(
        "matheus/iluminacao/presenca",
        "MOVIMENTO_DETECTADO"
      );
      Serial.println("MQTT enviado");

    } else {

      Serial.println("Sem movimento");

      client.publish(
        "matheus/iluminacao/presenca",
        "SEM_MOVIMENTO"
      );
    }

    ultimoEstado = movimento;
  }

  delay(100);
}