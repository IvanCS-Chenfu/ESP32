#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Configuración WiFi
const char* ssid = "TU_SSID";      // Reemplaza con tu SSID
const char* password = "TU_PASSWORD"; // Reemplaza con tu contraseña

// Configuración MQTT
const char* mqttServer = "broker.hivemq.com"; // Cambia el servidor si es necesario
const int mqttPort = 1883;
const char* mqttUser = ""; // No se necesita usuario para brokers públicos
const char* mqttPassword = "";

WiFiClient espClient;
PubSubClient client(espClient);   // "client" es el objeto que controla las acciones del cliente (Mi ESP32) MQTT

// Tópicos
const char* topicPub1 = "topic/send1";
const char* topicPub2 = "topic/send2";

void setup() 
{
  Serial.begin(115200);

  // Conexión WiFi
  conectarWiFi();

  // Configuración MQTT
  client.setServer(mqttServer, mqttPort);
  mqtt_client.setBufferSize(512);                       // Número máximo de bytes del buffer

  conectarMQTT();
}

void loop() 
{
  // Mantener conexión MQTT
  if (!client.connected())
  {
    conectarMQTT();
  }
  client.loop();

  // Publicar mensajes JSON en los tópicos
  publicarJSON(topicPub1, "mensaje1", 123);
  delay(5000);
  publicarJSON(topicPub2, "mensaje2", 456);
  delay(5000);
}

void conectarWiFi()
{
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void conectarMQTT()
{
  while (!client.connected()) 
  {
    Serial.println("Conectando al servidor MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) // ¿"ESP32Client" es el ID de la Placa? (se saca con ESP.getEfiseMac())
    {
      Serial.println("Conectado al servidor MQTT");
    }
    else
    {
      Serial.print("Error de conexión MQTT: ");
      int errorCode = client.state();
      switch (errorCode)
      {
        case MQTT_CONNECTION_TIMEOUT:
          Serial.println("Timeout de conexión");
          break;
        case MQTT_CONNECTION_LOST:
          Serial.println("Conexión perdida");
          break;
        case MQTT_CONNECT_FAILED:
          Serial.println("Fallo en la conexión");
          break;
        case MQTT_DISCONNECTED:
          Serial.println("Desconectado del servidor");
          break;
        case MQTT_BAD_PROTOCOL:
          Serial.println("Protocolo no soportado");
          break;
        case MQTT_BAD_CLIENT_ID:
          Serial.println("ID de cliente no válido");
          break;
        case MQTT_BAD_CREDENTIALS:
          Serial.println("Credenciales incorrectas");
          break;
        case MQTT_UNAVAILABLE:
          Serial.println("Servidor no disponible");
          break;
        case MQTT_UNSUPPORTED_VERSION:
          Serial.println("Versión no soportada");
          break;
        case MQTT_PAYLOAD_TOO_LARGE:
          Serial.println("Payload demasiado grande");
          break;
        default:
          Serial.println("Error desconocido");
      }
      delay(5000); // Reintento tras 5 segundos
    }
  }
}

// Publicar mensaje JSON
void publicarJSON(const char* topic, const char* key, int value)
{
  JsonDocument doc;
  doc[key] = value;

  char jsonBuffer[200];       // Se puede poner un string
  serializeJson(doc, jsonBuffer);

  client.publish(topic, jsonBuffer);
  Serial.print("Publicado en ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(jsonBuffer);
}