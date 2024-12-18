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
const char* topicSub1 = "topic/receive1";
const char* topicSub2 = "topic/receive2";

void setup() 
{
  Serial.begin(115200);

  // Conexión WiFi
  conectarWiFi();

  // Configuración MQTT
  client.setServer(mqttServer, mqttPort);
  mqtt_client.setBufferSize(512);                       // Número máximo de bytes del buffer
  client.setCallback(callbackMQTT);

  conectarMQTT();

  // Suscripción a los tópicos
  client.subscribe(topicSub1);
  client.subscribe(topicSub2);
}

void loop() 
{
  // Mantener conexión MQTT
  if (!client.connected())
  {
    conectarMQTT();
  }
  client.loop();
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


// Callback para manejar mensajes recibidos
void callbackMQTT(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Mensaje recibido en tópico: ");
  Serial.println(topic);

  String mensaje=String(std::string((char*) payload,length).c_str());

  Serial.print("Mensaje JSON recibido: ");
  Serial.println(mensaje);

  // Procesar JSON
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, mensaje);

  if (error) 
  {
    Serial.print("Error al parsear JSON: ");
    Serial.println(error.c_str());
    return;
  }

  if (String(topic) == topicSub1)
  {
    int valor1 = doc["clave1"] | 0;
    Serial.print("Valor recibido en tópico 1: ");
    Serial.println(valor1);
  }
  else if (String(topic) == topicSub2)
  {
    int valor2 = doc["clave2"] | 0;
    Serial.print("Valor recibido en tópico 2: ");
    Serial.println(valor2);
  }
}
