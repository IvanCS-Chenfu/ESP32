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

  // Chip ID
  Serial.print("Chip ID: ");
  Serial.println((uint32_t)ESP.getEfuseMac(), HEX);

  // Frecuencia de la CPU
  Serial.print("Frecuencia de la CPU: ");
  Serial.print(getCpuFrequencyMhz());
  Serial.println(" MHz");

  // Memoria Flash
  Serial.print("Tamaño de Flash: ");
  Serial.print(ESP.getFlashChipSize() / (1024 * 1024));
  Serial.println(" MB");

  // Memoria libre
  Serial.print("Memoria Libre (Heap): ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");

  // Tiempo desde el inicio
  Serial.print("Tiempo desde inicio: ");
  Serial.print(millis() / 1000);
  Serial.println(" segundos");
}
