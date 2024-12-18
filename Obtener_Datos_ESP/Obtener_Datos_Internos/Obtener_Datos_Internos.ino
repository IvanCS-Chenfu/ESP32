void setup() 
{
  Serial.begin(115200);

  mostrarInformacionESP32();
}

void loop()
{
  // El loop está vacío porque solo necesitamos mostrar la información una vez
}

void mostrarInformacionESP32() 
{
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
