#include <Servo.h>
#include <ESP32Servo.h>

Servo motor;
const int servoMotor = 13;

// Componentes
const int pirPin = 12;        // Sensor de movimento (PIR)
const int buzzerPin = 14;     // Buzzer
const int ledNoturno = 27;    // LED noturno

// Simulando horário com millis()
const unsigned long horaAbrir = 7UL * 3600000;     // 07:00 = 25.200.000 ms
const unsigned long horaFechar = 23UL * 3600000;   // 23:00 = 82.800.000 ms

bool janelaAberta = false;

void abrirJanela() {
  motor.write(90);  // Ângulo para abrir
  janelaAberta = true;
  Serial.println("Janela aberta.");
}

void fecharJanela() {
  motor.write(0);   // Ângulo para fechar
  janelaAberta = false;
  Serial.println("Janela fechada.");
}

void setup() {
  Serial.begin(9600);
  motor.attach(servoMotor);

  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledNoturno, OUTPUT);

  Serial.println("Sistema iniciado.");
}

void loop() {
  unsigned long tempoAtual = millis();

  // Controle de abertura e fechamento da janela
  if (tempoAtual >= horaFechar || tempoAtual < horaAbrir) {
    if (janelaAberta) {
      fecharJanela(); 
    }
    digitalWrite(ledNoturno, HIGH); // Acende LED noturno
  } else {
    if (!janelaAberta) {
      abrirJanela();
    }
    digitalWrite(ledNoturno, LOW); // Apaga LED noturno
  }

  // Se a janela estiver fechada e houver movimento → buzzer dispara
  int movimento = digitalRead(pirPin);
  if (!janelaAberta && movimento == HIGH) {
    Serial.println("⚠️ Movimento detectado com a janela fechada!");
    digitalWrite(buzzerPin, HIGH);
    delay(3000);
    digitalWrite(buzzerPin, LOW);
  }

  delay(1000);
}
}