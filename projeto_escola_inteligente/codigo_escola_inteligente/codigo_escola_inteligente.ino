//bibliotecas

#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>
#include <DHT.h>
#include <DHT_U.h>

//verificar vazamento de gas

const int mq135 = A0;
const int buzzer = 12;
//Sensor de movimento
const int PIR = 2;
const int LED = 13;


//
const int rele = 7;



//
#define DHTPINO A1
#define DHTTYPE DHT11

DHT dht(DHTPINO, DHT11);
LiquidCrystal_I2C Lcd(0x27, 20, 4);

//
Servo motor;  //vairavel do tipo servo para o motor

/*void acenderLEDaoDetectarPresenca(){
 int estadoPIR = digitalRead(PIR);
if (estadoPIR == HIGH) {
Serial.println("LED LIGADO");
digitalWrite(LED, HIGH);
} else {
 Serial.println("LED DESLIGADO");
 digitalWrite(LED, LOW);

}*/
void verificarVazamentoDeGas() {
  int estadoMQ135 = analogRead(mq135);
  Serial.println(estadoMQ135);
  if (estadoMQ135 >= 50) {
    alarme_dois_tons();
  } else {
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
  Lcd.clear();  //Limpa o Lcd
  Lcd.setCursor(0, 0);
  Lcd.print("temperatura: " + String(temperatura) + "C");
  Lcd.setCursor(0, 1);
  Lcd.print("umidade: " + String(umidade) + "%");

  //Serial.println("temperatura: " + String(temperatura) + "C");
  //Serial.println("umidade: " + String(umidade) + "%");
  delay(5000);  //5 segundos
}



void abrirPortaAutomatica() {
  motor.write(180);
  delay(1500);
}
void fecharPortaAutomatica() {
  motor.write(0);
  delay(1500);
}


void trancarPorta(){
 
digitalWrite(rele, LOW);
Serial.println("Porta trancada...")
delay(1500);
}

void destrancarPorta(){
  String senhaDigitada;

 Serial.println("por gentileza a senha para destravar a porta");
 while (!Serial.available());
 senhaDigitada = Serial.readString();

 if(senhaDigitada == "Senai@134"){
  digitalwrite(rele, HIGH);
  Serial.println("Porta sendo destrancada...");
  
  abrirPortaComServo(); //Chamado a funcao que ira abrir a porta automatica er dermora 3s
  trancarPorta(); //fecha a porta apos 3s 
 }else{
  if(motor.read() != 0){
   fecharaPortaComServo();
 }

  Seial.println("Senha invalida! Na terceira tentativa vou chamar a swat, fica esperto(a)");
}



void setup() {
  Serial.begin(9600);

  dht.begin();  //inicializa o dht11
  Lcd.init();   //inicia o LCD

  Lcd.backlight();



  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(mq135, INPUT);
  motor.attach(3);
  pinMode(rele, OUTPUT);

//
digitalWrite(rele, LOW);


  //
  motor.write(0);  //por enquanto ser o angulo 0


  Serial.println("Calibrando o sensor PIR...");
  Serial.println("Por favor, nao se mova na frente do sensor.");
  delay(15000);
  Serial.println("Sensor PIR calibrado e pronto!");

  Lcd.setCursor(0, 0);  //Primeira linha
  Lcd.print("Iniciando leituras");
  Lcd.setCursor(0, 1);  //Segunda linha
  Lcd.print("Obrigada");
}


void loop() {
  //acenderLEDaoDetectarPresenca();
  //verificarVazamentoDeGas();
  //alarme_dois_tons();
  //verificarTemperaturaEUmidade();
  abrirPortaAutomatica();
  fecharPortaAutomatica();
}
