#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

// Estructura para recibir mensajes
typedef struct 
{
  char mensaje[32];  // Mensaje recibido
  int contador;      // Ejemplo de otro dato que se recibe
} mensaje_t;

mensaje_t datosRecibidos;

// Callback al recibir datos
void onDataRecv(const esp_now_recv_info *info, const uint8_t *data, int len) 
{
  // Copiar los datos recibidos en la estructura
  memcpy(&datosRecibidos, data, sizeof(datosRecibidos));

  // Mostrar el mensaje recibido
  Serial.print("Mensaje recibido: ");
  Serial.println(datosRecibidos.mensaje);

  // Mostrar la MAC del remitente
  Serial.print("Desde la MAC: ");
  for (int i = 0; i < 6; i++) 
  {
    Serial.printf("%02X", info->src_addr[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
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

  // Registrar callback para recepción
  esp_now_register_recv_cb(onDataRecv);
}

void loop() 
{
  // Mantener el programa activo
  delay(1000);
}
