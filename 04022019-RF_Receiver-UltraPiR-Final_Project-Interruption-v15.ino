//#include <TimerOne.h> //TIMER FUNCTION FOR PIR SENSOR
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

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

  // Configuração do timer1 
  TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0;                        //limpa registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1
 
  TCNT1 = 31250;                    // incia timer com valor para que estouro ocorra em 1 segundo
                                     // 65536-(16MHz/1024/1Hz)"15625 34286" = 49911 = 0xC2F7
  
  TIMSK1 |= (1 << TOIE1);           // habilita a interrupção do TIMER1

}

ISR(TIMER1_OVF_vect)              //interrupção do TIMER1 Quando passar em frente ao pinPiR deve acionar timer por 2 segundos antes parar completamente o LED1/Rodas
{
      TCNT1 = 31250;                // incia timer
 if (digitalRead(pinPiR) == HIGH)
      {
       digitalWrite(LED1, LOW);
       }
      else 
      {
      recebidos[0];
      }
      TIMSK1 |= (1 << TOIE1);       // interrupção do TIMER1
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

  if (digitalRead(pinPiR) == HIGH)
      {
       digitalWrite(LED1, LOW);
       }
      else 
      {
      recebidos[0];
      }
       
      //delay(100);
      
       }
   
  }
  else
  {
  Serial.println("Aguardando dados...");
  }
}
