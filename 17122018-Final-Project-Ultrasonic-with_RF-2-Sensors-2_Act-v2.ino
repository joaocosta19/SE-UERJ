#include "Ultrasonic.h"   //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO

//Biblioteca RF24L01
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
//Armazena os dados enviados - RF24L01
int dados[1];
//Inicializa a placa nos pinos 9 (CE) e 10 (CS) do Arduino
RF24 radio(9,10);
//Define o endereco para comunicacao entre os modulos - RF24L01
const uint64_t pipe = 0xE14BC8F482LL;

const int echoPin = 5;   //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 6;  //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
const int pinoBuzzer = 3;  //PINO DIGITAL EM QUE O BUZZER ESTÁ CONECTADO
Ultrasonic ultrasonic(trigPin,echoPin);   //INICIALIZANDO OS PINOS

//Define os pinos dos botoes - Realizando conectividade com Ultra
int pino_botao1 = 7;

int distancia;    //CRIA UMA VARIÁVEL CHAMADA "distancia" DO TIPO INTEIRO
String result;    //CRIA UMA VARIÁVEL CHAMADA "result" DO TIPO STRING

void setup(){
pinMode(echoPin, INPUT);     //DEFINE O PINO 5 COMO ENTRADA (RECEBE)
pinMode(trigPin, OUTPUT);     //DEFINE O PINO 6 COMO SAÍDA (ENVIA)
pinMode(pinoBuzzer, OUTPUT);  //DECLARA O PINO 3 COMO SENDO SAÍDA
//Antigo PinBoton agora Define e ativa pinbuzzer como entrada e
//ativa pull-up
//pinMode(7, INPUT);
//digitalWrite(7,HIGH);

//Inicializa a serial
  Serial.begin(57600);
  Serial.println("Antigo botao 1 Agora Aciona Buzzer para iniciar a comunicacao...");  
  
  //Inicializa a comunicacao
  radio.begin();
  //Entra em modo de transmissao
  radio.openWritingPipe(pipe);
}
void loop(){

hcsr04();     // FAZ A CHAMADA DO MÉTODO "hcsr04()"


if(distancia <= 30){        // SE A DISTÂNCIA ENTRE O OBJETO E O SENSOR ULTRASONICO FOR MENOR     //QUE 60CM, FAZ
tone(pinoBuzzer, 1500);      //ACIONA O BUZZER
//digitalWrite(7,HIGH);
}else{                      //SENÃO, FAZ
noTone(pinoBuzzer);         //BUZZER PERMANECE DESLIGADO
//digitalWrite(7,LOW);
}
//Envia o numero 1 caso o botao1 seja pressionado
if(digitalRead(pino_botao1) == HIGH){
    Serial.println("Antigo Botao 1-Agora Buzzer Acionado. Transmitindo!");
    dados[0] = 1;
    radio.write(dados, 1); 
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
//D777rd 
elay(500);                     //INTERVALO DE 500 MILISSEGUNDOS
}
