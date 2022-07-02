#include <OneWire.h>
#include <DallasTemperature.h>

 
// Porta do pino de sinal do DS18B20
#define sensorTemp 32
// Porta do pino de sinal da ventoinha
#define ventilacao 37

float setTemp = 27.0; //Setagem da temperatura requirida
 
// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(sensorTemp);
 
// Armazena temperaturas minima e maxima
float tempMin = 999;
float tempMax = 0;

DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;
 
void setup(void){
  
  Serial.begin(9600);
  sensors.begin();
  sensorTempIniciar();
  pinMode(ventilacao, OUTPUT);
  digitalWrite(ventilacao,0);
}

void sensorTempIniciar(){

  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println("Sensores de Temperatura  nao encontrados !"); 
}
void mostra_endereco_sensor(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void leituraSensor(){

  // Le a informacao do sensor
  sensors.requestTemperatures();
  float tempC = sensors.getTempC(sensor1);
  // Atualiza temperaturas minima e maxima
  if (tempC < tempMin)
  {
    tempMin = tempC;
  }
  if (tempC > tempMax)
  {
    tempMax = tempC;
  }
  // Mostra dados no serial monitor
  Serial.print("Temp Atual: ");
  Serial.print(tempC);
  Serial.print("       ");
  Serial.print(" Min : ");
  Serial.print(tempMin);
  Serial.print(" Max : ");
  Serial.println(tempMax);
  delay(1000);
}

void controleTemp(){
  int aux;
  float tempControle = sensors.getTempC(sensor1);
  
  if(tempControle<=setTemp){
    aux = 0;
    digitalWrite(ventilacao,1);
  }
  if(tempControle>setTemp){
        aux = 1;
        if(tempControle > (setTemp + 0.2) and aux == 1){
          digitalWrite(ventilacao, 0);
        }
      }
      Serial.println(aux);
}


 
void loop(){
  
  leituraSensor();
  controleTemp();
}
