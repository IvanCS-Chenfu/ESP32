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
  uint32_t chipID = (uint32_t)ESP.getEfuseMac();
  Serial.print("Chip ID: ");
  Serial.println(chipID, HEX);

  // Frecuencia de la CPU
  int cpuFreq = getCpuFrequencyMhz();
  Serial.print("Frecuencia de la CPU: ");
  Serial.print(cpuFreq);
  Serial.println(" MHz");

  // Memoria Flash
  size_t flashSize = ESP.getFlashChipSize() / (1024 * 1024);
  Serial.print("Tamaño de Flash: ");
  Serial.print(flashSize);
  Serial.println(" MB");

  // Memoria libre
  size_t freeHeap = ESP.getFreeHeap();
  Serial.print("Memoria Libre (Heap): ");
  Serial.print(freeHeap);
  Serial.println(" bytes");

  // Tiempo desde el inicio
  uint32_t uptime = millis() / 1000;
  Serial.print("Tiempo desde inicio: ");
  Serial.print(uptime);
  Serial.println(" segundos");
}
