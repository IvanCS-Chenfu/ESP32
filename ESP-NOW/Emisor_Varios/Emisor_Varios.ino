#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

uint8_t macESP1[] = {0x24, 0x6F, 0x28, 0x12, 0x34, 0x56}; // Reemplaza con la MAC de la primera placa receptora
uint8_t macESP2[] = {0x24, 0x6F, 0x28, 0x12, 0x34, 0x57}; // Reemplaza con la MAC de la segunda placa receptora
uint8_t macESP3[] = {0x24, 0x6F, 0x28, 0x12, 0x34, 0x58}; // Reemplaza con la MAC de la tercera placa receptora

// Estructura para el mensaje
typedef struct
{
  char mensaje[32];  // Mensaje que se enviará
  int contador;      // Ejemplo de otro dato que quieras enviar
} mensaje_t;

mensaje_t datosEnviar;
int contador = 0;

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

void setup() {
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

  // Configurar los peers
  configurarPeer(macESP1);
  configurarPeer(macESP2);
  configurarPeer(macESP3);

}

void loop() 
{
  // Datos iniciales a enviar
  strcpy(datosEnviar.mensaje, "Hola ESP-NOW!");
  contador++;
  datosEnviar.contador = contador;

  // Enviar datos a cada receptor
  enviarDatos(macESP1);
  enviarDatos(macESP2);
  enviarDatos(macESP3);

  delay(2000); // Pausa entre envíos
}

void configurarPeer(const uint8_t *mac)
{
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, mac, 6);
  
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK) 
  {
    Serial.println("Error al agregar el peer");
  }
}

void enviarDatos(const uint8_t *mac)
{
  esp_err_t result = esp_now_send(mac, (uint8_t *)&datosEnviar, sizeof(datosEnviar));
  if (result == ESP_OK)
  {
    Serial.println("Mensaje enviado correctamente");
  } 
  else
  {
    Serial.println("Error al enviar el mensaje");
  }
}
