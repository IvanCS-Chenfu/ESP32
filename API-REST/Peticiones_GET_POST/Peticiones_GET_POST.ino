#include <WiFi.h>
#include <HTTPClient.h>

// Configuración WiFi
const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";

HTTPClient http;

// Ejemplo de uso
String payload;
const char* url = "http://example.com/api/data";

int http_request(const char* method, const char* url, String& payload, const String& postData = "")
{
  int httpResponseCode = -1; // Código de respuesta inicial

  if (http.begin(url))
  { // Común: Inicializar la conexión HTTP
    
    if (method == "POST")
    { // Si el método es POST
      http.addHeader("Content-Type", "application/json"); // Cabecera necesaria para que el servidor sepa que los mensajes enviados son tipo JSON
      httpResponseCode = http.POST(postData); // Realiza la petición POST
    }
    else if (method == "GET")
    { // Si el método es GET
      httpResponseCode = http.GET(); // Realiza la petición GET
    }
    else
    {
      Serial.println("Error: Método no soportado. Usa 'GET' o 'POST'.");
      http.end();
      return -2; // Código de error para método no soportado
    }

    // Manejo de la respuesta
    if (httpResponseCode > 0)
    {
      payload = http.getString(); // Obtiene la respuesta
      Serial.println("Respuesta del servidor:");
      Serial.println(payload);
    }
    else
    {
      Serial.print("Error en la petición HTTP. Código: ");
      Serial.println(httpResponseCode);
      switch (httpResponseCode)
      {
        case HTTPC_ERROR_CONNECTION_REFUSED:
          Serial.println("Error: Conexión rechazada.");
          break;
        case HTTPC_ERROR_SEND_HEADER_FAILED:
          Serial.println("Error: Fallo al enviar cabeceras.");
          break;
        case HTTPC_ERROR_SEND_PAYLOAD_FAILED:
          Serial.println("Error: Fallo al enviar datos.");
          break;
        case HTTPC_ERROR_NOT_CONNECTED:
          Serial.println("Error: No conectado al servidor.");
          break;
        case HTTPC_ERROR_READ_TIMEOUT:
          Serial.println("Error: Tiempo de espera agotado.");
          break;
        default:
          Serial.println("Error: Código desconocido.");
          break;
      }
    }
  }
  else
  {
    Serial.println("Error: No se pudo conectar a la URL proporcionada.");
    return -3; // Código de error para fallo de conexión
  }

  http.end(); // Finaliza la conexión HTTP
  return httpResponseCode; // Devuelve el código de respuesta o error
}

void setup()
{
  Serial.begin(115200);

  // Conexión WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado.");

  // Ejemplo de GET
  int responseGET = http_request("GET", url, payload);
  Serial.print("Código de respuesta GET: ");
  Serial.println(responseGET);

  // Ejemplo de POST
  String postData = "{\"key\": \"value\"}";
  int responsePOST = http_request("POST", url, payload, postData);
  Serial.print("Código de respuesta POST: ");
  Serial.println(responsePOST);
}

void loop() 
{
  // No se utiliza en este ejemplo
}
