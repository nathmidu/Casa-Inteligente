//bibliotecas
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>
#include <DHT.h>
#include <DHT_U.h>

int PIR = 2;
const int ledBranco = 13;

const int MQ135 = A0;
const int buzzer = 12;



//
#define DHTPINO A1
#define DHTTIPO DHT11

DHT dht(DHTPINO, DHT11);
LiquidCrystal_I2C lcd(0x27, 20, 4);


 void acenderLEDAoDetectarPresenca(){

 int estadoPIR = digitalRead(PIR);

if (estadoPIR == HIGH){ 
  digitalWrite(ledBranco, HIGH);
  Serial.println("LED ligado");
}

 else {
  digitalWrite(ledBranco, LOW);
  Serial.println("LED desligado");
}
Serial.println(estadoPIR);
}

void verificarVazamentoDeGas(){

int estadoMQ135 = analogRead(MQ135);

//Serial.println(estadoMQ135);
if(estadoMQ135 >= 50){
  alarme_dois_tons();

}
else{
  noTone(buzzer);
}
}

void alarme_dois_tons() {


  
  int freqAlta = 2000;
  int freqBaixa = 800;
  int duracaoTom = 250;

  tone(buzzer, freqAlta, duracaoTom);
  delay(duracaoTom);
  tone(buzzer, freqBaixa, duracaoTom);
  delay(duracaoTom);
}
void verificarTemperaturaEUmidade() {
float temperatura = dht.readTemperature();
float umidade = dht.readHumidity();

lcd.clear(); 
lcd.setCursor(0, 0);
lcd.print("Temperatura: " + String(temperatura) + "C");
lcd.setCursor(0, 1);
lcd.print("Umidade: " + String(umidade) + "%");

//Serial.println("Temperatura: " + String(temperatura) + "C");
//Serial.println("Umidade: " + String(umidade) + "%");
delay(5000);

  }
void setup() {

 Serial.begin(9600);

dht.begin();
lcd.init();

lcd.backlight();

 pinMode(ledBranco, OUTPUT);
 pinMode(PIR, INPUT);
pinMode(buzzer, OUTPUT);
pinMode(MQ135, INPUT);



 Serial.println("Sensores sendo calibrados, aguente firme!!!");
 delay(10000);
 Serial.println("Sensores calibrados! obrigada por esperar!!!");

lcd.setCursor(0, 0);
lcd.print("Senaizeiras");
lcd.setCursor(0, 1);
lcd.print("Obrigada!");
}

void loop() {
  //acenderLEDAoDetectarPresenca();
  //verificarVazamentoDeGas();
  //alarme_dois_tons();
  verificarTemperaturaEUmidade();
 }
