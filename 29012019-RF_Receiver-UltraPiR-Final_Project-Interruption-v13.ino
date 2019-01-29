//#include <TimerOne.h> //TIMER FUNCTION FOR PIR SENSOR
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <avr/io.h>
#include <avr/interrupt.h>

//Armazena os dados recebidos
int recebidos [1];

//Inicializa a placa nos pinos 9 (CE) e 10 (CS) do Arduino
RF24 radio(9,10);

//Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE14BC8F482LL;

//Define os pinos dos leds = Rodas
int LED1 = 5;  //Continua Andando

//Valores para PiR
int pinPiR = 6;        // value read from the port 6

void setup() {

//Define os pinos dos leds/Rodas como Saída
  pinMode(LED1, OUTPUT);
  pinMode(pinPiR, INPUT);
  
//Inicializa a serial
  Serial.begin(57600);

//Inicializa a comunicacao
  radio.begin();
  
//Entra em modo de recepcao
  radio.openReadingPipe(1,pipe);
  radio.startListening();

  // initialize timer1 

  TIMSK1 = 0X03;                        // ativa o Timer/Counter1 com os modos dos bits 0 e 1, ou seja,// ativa Comparador A e detector de overflow

  TCCR1A = 0x00;                        // desabilita inicialmente o timer
  TCCR1B = 0x00;                        // desabilita inicialmente o timer
  
 }
 
void zeroCross() {
TCCR1B=0x04;                            // habilita o timer no modo que divide o clock real por 256
TCNT1=0;                                // zera o contador do timer
//TCNT1 = 0xC2F7;                          // inicia timer com valor para que estouro ocorra em 1 segundo//65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7
 }

 
ISR(TIMER1_COMPA_vect)         // rotina de serviço de interrupção que envolve uma função definida pelo usuário fornecida pelo attachInterrupt
{
//#if 0
 attachInterrupt(0,zeroCross, RISING); 
if (digitalRead(pinPiR) == HIGH)  //Se Alguém passar na frente do carro o mesmo para através da sensibilidade do sensor PiR
    {
      TCNT1 = 0xC2F7;                          // inicia timer com valor para que estouro ocorra em 1 segundo//65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7
    digitalWrite(LED1, LOW);
    }
      else 
      {
      recebidos[0];
      }
           detachInterrupt(0);
//#endif     
}

ISR(TIMER1_OVF_vect) {

attachInterrupt(0,zeroCross, RISING); 
if (digitalRead(pinPiR) == HIGH)
    {  
    //TCCR1B = 0;                // desativa o timer que foi inicialmente ativado pela nossa funcao zeroCross().
    TCNT1 = 0xC2F7;                          // inicia timer com valor para que estouro ocorra em 1 segundo//65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7
    digitalWrite(LED1, LOW);
    }
      else 
      {
      recebidos[0];
      }
       detachInterrupt(0);
}

void loop() {

  //Verifica se ha sinal de radio
  if (radio.available())
  {
    
    bool done = false;    
    while (!done)
    {
      radio.read(recebidos,1);                  //Havia erro de sintaxe retirado "done = radio.read(recebidos,1)"
      Serial.print("Dados recebidos : ");    
      Serial.println(recebidos[0]);
      
      //Se recebeu o numero 1, acende o LED1/IN do Relé para acionamento das Rodas
      
  if (recebidos[0] == 1)
      {
        delay(10);
        digitalWrite(LED1, HIGH);
      }
      else 
      {
        digitalWrite(LED1, LOW);
       }
  
  attachInterrupt(0,zeroCross, RISING); 
  if (digitalRead(pinPiR) == HIGH) //-->> OK//Se Alguém passar na frente do carro o mesmo para através da sensibilidade do sensor PiR
    {
      TCNT1 = 0xC2F7;                          // inicia timer com valor para que estouro ocorra em 1 segundo//65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7
      //attachInterrupt(0,zeroCross, RISING); 
      digitalWrite(LED1, LOW);
       }
      else 
      {
      recebidos[0];
      
   
      }
        detachInterrupt(0);
      //delay(100);
      
       }
   
  }
  else
  {
  Serial.println("Aguardando dados...");
  }
}
