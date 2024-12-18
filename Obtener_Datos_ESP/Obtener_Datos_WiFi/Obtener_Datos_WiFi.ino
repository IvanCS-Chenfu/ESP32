#include <WiFi.h>

// Configuración WiFi
const char* ssid = "TU_SSID";      // Reemplaza con tu SSID
const char* password = "TU_PASSWORD"; // Reemplaza con tu contraseña

void setup() {
  Serial.begin(115200);

  // Conexión WiFi
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado.");

  // Obtener y mostrar información del ESP32
  mostrarInformacionESP32();
}

void loop() {
  // El loop está vacío porque solo necesitamos mostrar la información una vez
}

void mostrarInformacionESP32() {
  // Dirección IP
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Dirección MAC
  Serial.print("Dirección MAC: ");
  Serial.println(WiFi.macAddress());

  // Hostname
  Serial.print("Hostname: ");
  Serial.println(WiFi.getHostname());

  // Gateway
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());

  // Máscara de subred
  Serial.print("Máscara de Subred: ");
  Serial.println(WiFi.subnetMask());

  // Dirección IP del DNS primario
  Serial.print("DNS Primario: ");
  Serial.println(WiFi.dnsIP());

  // Intensidad de la señal WiFi (RSSI)
  Serial.print("Intensidad de Señal (RSSI): ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}
