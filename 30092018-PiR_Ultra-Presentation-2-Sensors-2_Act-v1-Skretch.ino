//PiR Sensor Constants
const int pinoPIR = 3;                    //PINO DIGITAL UTILIZADO PELO SENSOR DE PRESENÇA
const int pinoLED = 7;                   //PINO DIGITAL UTILIZADO PELO LED

//Ultrasonic Sensor Constants
#include "Ultrasonic.h"   //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO

const int echoPin = 11;   //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 8;  //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
const int pinoBuzzer = 13;  //PINO DIGITAL EM QUE O BUZZER ESTÁ CONECTADO

Ultrasonic ultrasonic(trigPin,echoPin);   //INICIALIZANDO OS PINOS

int distancia;    //CRIA UMA VARIÁVEL CHAMADA "distancia" DO TIPO INTEIRO
String result;    //CRIA UMA VARIÁVEL CHAMADA "result" DO TIPO STRING

void setup(){
  //Define PIN PiR
  pinMode(pinoLED, OUTPUT);               //DEFINE O PINO 7 COMO SAÍDA
  pinMode(pinoPIR, INPUT);                   //DEFINE O PINO 3 COMO ENTRADA

  //Define PIN Ultrasonic
  pinMode(echoPin, INPUT);     //DEFINE O PINO 11 COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT);     //DEFINE O PINO 8 COMO SAÍDA (ENVIA)
  pinMode(pinoBuzzer, OUTPUT);  //DECLARA O PINO 13 COMO SENDO SAÍDA
}
void loop(){
  //Programming PiR
 if(digitalRead(pinoPIR) == HIGH){          //SE A LEITURA DO PINO FOR IGUAL A HIGH, FAZ
    digitalWrite(pinoLED, HIGH);              //ACENDE O LED
 }else{                                                           //SENÃO, FAZ
  digitalWrite(pinoLED, LOW);                 //APAGA O LED
 }

 //Programming Ultrasonic
hcsr04();     // FAZ A CHAMADA DO MÉTODO "hcsr04()"

if(distancia <= 60){        // SE A DISTÂNCIA ENTRE O OBJETO E O SENSOR ULTRASONICO FOR MENOR     //QUE 60CM, FAZ
tone(pinoBuzzer,1500);      //ACIONA O BUZZER
}else{                      //SENÃO, FAZ
noTone(pinoBuzzer);         //BUZZER PERMANECE DESLIGADO
}
}


  //MÉTODO RESPONSÁVEL POR CALCULAR A DISTÂNCIA
void hcsr04(){
digitalWrite(trigPin, LOW);     //SETA O PINO 8 COM UM PULSO BAIXO "LOW"
delayMicroseconds(2);           // DELAY DE 2 MICROSSEGUNDOS
digitalWrite(trigPin, HIGH);    //SETA O PINO 8 COM PULSO ALTO "HIGH"
delayMicroseconds(10);          // DELAY DE 10 MICROSSEGUNDOS
digitalWrite(trigPin, LOW);     //SETA O PINO 8 COM PULSO BAIXO "LOW" NOVAMENTE
                                // FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
                               //RESPOSTA DO ECHO EM CENTÍMETROS E ARMAZENA
                               //NA VARIÁVEL "distancia"
distancia = (ultrasonic.Ranging(CM));   // VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
delay(500);                     //INTERVALO DE 500 MILISSEGUNDOS
}
