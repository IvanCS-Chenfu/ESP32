#include <WiFi.h>

// Función para inicializar la conexión WiFi
void inicializarWiFi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password); // Inicia la conexión WiFi

    Serial.print("Conectando a WiFi");
    int intentos = 0;

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
        intentos++;

        // Manejo de errores de conexión
        if (WiFi.status() == WL_NO_SSID_AVAIL) {
            Serial.println("\nError: SSID no disponible.");
        } else if (WiFi.status() == WL_CONNECT_FAILED) {
            Serial.println("\nError: Fallo en la conexión. Verifica la contraseña.");
        } else if (WiFi.status() == WL_DISCONNECTED) {
            Serial.println("\nError: Desconectado. Reintentando...");
        } else if (WiFi.status() == WL_IDLE_STATUS) {
            Serial.println("\nEstado inactivo. Intentando reconectar...");
        }

        // Si los intentos exceden un límite, reinicia la conexión
        if (intentos >= 10) {
            Serial.println("\nExceso de intentos. Reiniciando WiFi...");
            WiFi.disconnect();
            WiFi.begin(ssid, password);
            intentos = 0;
        }
    }

    Serial.println("\nWiFi conectado.");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
}

void setup() {
    Serial.begin(115200);

    const char* ssid = "TU_SSID";
    const char* password = "TU_PASSWORD";

    inicializarWiFi(ssid, password); // Llama a la función para conectar a WiFi
}

void loop() {
    // Código principal
}
