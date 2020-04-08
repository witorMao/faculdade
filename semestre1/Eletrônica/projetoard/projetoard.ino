/*
 * Witor Matheus Alves de Oliveiro - 10692190 - witor.mao@usp.br
 * Victor Machado Gonzaga - 10692033 - machado.prx@gmail.com
 * Rafael Albrecht Ribeiro - 10783305 - rafaelribeiro2108@gmail.com 
 * 
 * BIBLIOTECAS: DHT-sensor-library-master
 *              Liquid Crystal
 * 
 * 
 */


#include "DHT.h"//inclusão da biblioteca para usar o módulo dht11
#include <LiquidCrystal.h>//inclusão da biblioteca para usar o lcd

#define DHTPIN A1 // O pino que as saida de dados do dht esta conectada A1
#define DHTTYPE DHT11 // DHT 11 
#define Luz_Fundo  7//definição do pino de saida para o controle de contraste do lcd
#define led 8//definição do pino de saida para o led
#define buzzer 13//definição do pino de saida para o buzzer
#define TempMax 25// definição 
#define UmiMin 60 // umidade mínima para ativar o buzzer e o led

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//definição dos pinos de daos do lcd
byte grau[8] = { B00001100,
                 B00010010,
                 B00010010,
                 B00001100,
                 B00000000,
                 B00000000,
                 B00000000,
                 B00000000,
               };

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Iniciando o objeto "lcd" de 2 linhas e 16 colunas
  lcd.createChar(0, grau);
  pinMode(Luz_Fundo, OUTPUT); //define o pino como saída
  analogWrite(Luz_Fundo, 130); // Liga a luz do display.
  dht.comeco();
  pinMode(led, OUTPUT); //Define os pinos led e buzzer como saida
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Ler temperatura ou umidade leva cerca de 250 milissegundos
  // As leituras do sensor tambem podem ser 'velhas' (Se o sensor for muito lento)
  float h = dht.le_umidade();
  float t = dht.ler_Temperatura();
  // Verifica se os retornos são validos, Se forem NAN (not a number - não um numero) então algo deu errado!
  if (isnan(t) || isnan(h)) {
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Falha ao ler do sensor");
    for (int posicao = 0; posicao < 40; posicao++){
      lcd.scrollDisplayLeft();
      delay(400);
    }
  } else {
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
    
    lcd.setCursor(0, 0); // seta o cursor para: (coluna = 0, linha = 0)
    lcd.print("Tempertura: ");
    lcd.setCursor(12, 0);
    lcd.print(t);
    lcd.setCursor(14, 0);
    lcd.write((byte)0);// printar símbolo ° para temperatura
    lcd.setCursor(15, 0);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Umidade: ");
    lcd.setCursor(13, 1);
    lcd.print(h);
    lcd.setCursor(15, 1);
    lcd.print("%");

     if(t > TempMax) //Condiçao: Se a temperatura for maior que TempMax...
    {
        digitalWrite(led, HIGH); // Liga o Led
        digitalWrite(buzzer, HIGH); //Dá um "Bip" no buzzer
        delay(1000);
        digitalWrite(buzzer, LOW); // desliga o buzzer
        delay(10); //Aguarda 10 Segundos
        digitalWrite(led, LOW); //Desliga o led
     } // Fecha o loop if
  
     if(h < UmiMin) //Condiçao: Se a umidade for menor que umiMin...
     {
         digitalWrite(led, HIGH); // Liga o Led
         lcd.clear(); // clean no LED
         lcd.setCursor(1,0);  
         lcd.print("Umidade abaixo do ideal");
         lcd.setCursor(5,1);  
         lcd.print("Beba agua!!!");
         for (int posicao = 0; posicao < 40; posicao++){
            lcd.scrollDisplayLeft();
            delay(400);
         }
         
         for(int buz=0; buz<=3; buz++) //Dá 3 "Bips" no buzzer
         {
            digitalWrite(buzzer, HIGH);
            delay(100);h
            digitalWrite(buzzer, LOW);
            delay(100);
          }
          lcd.clear();
          lcd.setCursor(0, 0); // seta o cursor para: (coluna = 0, linha = 0)
          lcd.print("Tempertura: ");
          lcd.setCursor(12, 0);
          lcd.print(t);
          lcd.setCursor(14, 0);
          lcd.write((byte)0);//printar símbolo ° para temperatura
          lcd.setCursor(15, 0);
          lcd.print("C");

          lcd.setCursor(0, 1);
          lcd.print("Umidade: ");
          lcd.setCursor(13, 1);
          lcd.print(h);
          lcd.setCursor(15, 1);
          lcd.print("%");

  
        delay(20); //Aguarda 5 Segundos
        digitalWrite(led, LOW); //Desliga o led
      } // Fecha o loop if
     }
    
}
