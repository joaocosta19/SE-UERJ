#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Ultrasonic Sensor Constants
#include "Ultrasonic.h"   //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO
const int echoPin = 5;   //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)  //
const int trigPin = 6;  //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)     // 
const int pinoBuzzer = 3;  //PINO DIGITAL EM QUE O BUZZER ESTÁ CONECTADO // = Tx -->>Rx - Acionando Rodas em Rx

Ultrasonic ultrasonic(trigPin,echoPin);   //INICIALIZANDO OS PINOS
int distancia;    //CRIA UMA VARIÁVEL CHAMADA "distancia" DO TIPO INTEIRO
String result;    //CRIA UMA VARIÁVEL CHAMADA "result" DO TIPO STRING


//Armazena os dados enviados
int dados[1];

//Inicializa a placa nos pinos 9 (CE) e 10 (CS) do Arduino
RF24 radio(9,10);

//Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE14BC8F482LL;

//Define os pinos dos botoes
int pino_botao1 = 7;
//int pino_botao2 = 2;

void setup()
{
  //Define os botoes como entrada e
  //ativa pull-up
  pinMode(7, INPUT);
  digitalWrite(7,HIGH);
//  pinMode(2, INPUT);
//  digitalWrite(2,HIGH);

  //Inicializa a serial
  Serial.begin(57600);
  Serial.println("Pressione botao 1 ou 2 para iniciar a comunicacao...");
  
  //Inicializa a comunicacao
  radio.begin();
  //Entra em modo de transmissao
  radio.openWritingPipe(pipe);

     //Define PIN Ultrasonic
  //pinMode(echoPin, INPUT);     //DEFINE O PINO 5 COMO ENTRADA (RECEBE)
  DDRD = DDRD & B11101111;
  //pinMode(trigPin, OUTPUT);     //DEFINE O PINO 6 COMO SAÍDA (ENVIA)
  DDRD = DDRD | B01000000;
  //pinMode(pinoBuzzer, OUTPUT);  //DECLARA O PINO 3 COMO SENDO SAÍDA
  DDRD = DDRD | B00001000;
}

void loop()
{
  hcsr04();     // FAZ A CHAMADA DO MÉTODO "hcsr04()"

if(distancia <= 15){        // SE A DISTÂNCIA ENTRE O OBJETO E O SENSOR ULTRASONICO FOR MENOR     //QUE 30CM, FAZ
tone(pino_botao1,1500);      //ACIONA O PINO 7 Tx SINAL PARA O Rx
//tone ((PORTB = PORTB & B00100000),1500); DESLIGAVA O CCTO
}else{                      //SENÃO, FAZ
noTone(pino_botao1);         //BUZZER PERMANECE DESLIGADO
}
  //Envia o numero 1 caso o botao1 seja pressionado
  if (digitalRead(pino_botao1) == LOW)
  //if(distancia <= 30)
  {
    Serial.println("Botao 1 pressionado !");
    dados[0] = 1;
    radio.write(dados, 1);
  }
  
  //Envia o numero 2 caso o botao2 seja pressionado
//  if (digitalRead(pino_botao2) == LOW)
  //{
    //Serial.println("Botao 2 pressionado !");
    //dados[0] = 2;
  //  radio.write(dados, 1);
  //}
 }
 void hcsr04(){
//digitalWrite(trigPin, LOW);     //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
PORTD = PORTD & B01000000;
delayMicroseconds(2);           // DELAY DE 2 MICROSSEGUNDOS
//digitalWrite(trigPin, HIGH);    //SETA O PINO 6 COM PULSO ALTO "HIGH"
PORTD = PORTD | B00000001;
delayMicroseconds(10);          // DELAY DE 10 MICROSSEGUNDOS
//digitalWrite(trigPin, LOW);     //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
PORTD = PORTD & B00000000;
                                // FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
                               //RESPOSTA DO ECHO EM CENTÍMETROS E ARMAZENA
                               //NA VARIÁVEL "distancia"
distancia = (ultrasonic.Ranging(CM));   // VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
}
