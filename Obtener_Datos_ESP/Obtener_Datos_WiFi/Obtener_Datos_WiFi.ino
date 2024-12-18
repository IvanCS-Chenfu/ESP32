#include <WiFi.h>

// Configuración WiFi
const char* ssid = "TU_SSID";      // Reemplaza con tu SSID
const char* password = "TU_PASSWORD"; // Reemplaza con tu contraseña

void setup()
{
  Serial.begin(115200);

  // Conexión WiFi
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado.");

  // Obtener y mostrar información del ESP32
  mostrarInformacionESP32();
}

void loop()
{
  // El loop está vacío porque solo necesitamos mostrar la información una vez
}

void mostrarInformacionESP32() {
  // Dirección IP
  IPAddress ip = WiFi.localIP();
  Serial.print("Dirección IP: ");
  Serial.println(ip);

  // Dirección MAC
  String mac = WiFi.macAddress();
  Serial.print("Dirección MAC: ");
  Serial.println(mac);

  // Hostname
  const char* hostname = WiFi.getHostname();
  Serial.print("Hostname: ");
  Serial.println(hostname);

  // Gateway
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("Gateway: ");
  Serial.println(gateway);

  // Máscara de subred
  IPAddress subnet = WiFi.subnetMask();
  Serial.print("Máscara de Subred: ");
  Serial.println(subnet));

  // Dirección IP del DNS primario
  IPAddress dns = WiFi.dnsIP();
  Serial.print("DNS Primario: ");
  Serial.println(dns);

  // Intensidad de la señal WiFi (RSSI)
  int32_t rssi = WiFi.RSSI();
  Serial.print("Intensidad de Señal (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}
