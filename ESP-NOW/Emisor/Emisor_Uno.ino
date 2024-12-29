// Librerías Necesarias para utilizar ESP-NOW
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

uint8_t macDestino[] = {0xC8, 0x2E, 0x18, 0xF8, 0x58, 0x94}; // Reemplaza con la MAC de la placa esclava

// Estructura para el mensaje
typedef struct 
{
  char mensaje[32];  // Mensaje que se enviará
} mensaje_t;

mensaje_t datosEnviar;

// Callback para verificar el envío
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) 
{
  Serial.print("Envío a ");
  for (int i = 0; i < 6; i++) 
  {
    Serial.printf("%02X", mac_addr[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.print(" --> Estado: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Éxito" : "Fallo");
}

void setup() 
{
  Serial.begin(115200);

  // Configuración WiFi
  WiFi.mode(WIFI_STA);
  Serial.print("MAC de esta placa: ");
  Serial.println(WiFi.macAddress());

  // Inicializar ESP-NOW
  if (esp_now_init() != ESP_OK) 
  {
    Serial.println("Error al inicializar ESP-NOW");
    return;
  }

  // Registrar callback para verificar envío
  esp_now_register_send_cb(onDataSent);

  // Configurar el peer (destinatario)
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, macDestino, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) 
  {
    Serial.println("Error al agregar el peer");
    return;
  }

  // Datos a enviar
  strcpy(datosEnviar.mensaje, "¡Hola ESP-Now Esclavo!");
}

void loop() 
{
  // Enviar datos cada 2 segundos
  esp_err_t result = esp_now_send(macDestino, (uint8_t *)&datosEnviar, sizeof(datosEnviar));
  if (result == ESP_OK) 
  {
    Serial.println("Mensaje enviado correctamente");
  }
  else
  {
    Serial.println("Error al enviar el mensaje"); 
  }

  delay(2000);
}
