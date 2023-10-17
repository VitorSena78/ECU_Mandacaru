//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif


//variaves velocimetro
float velo = 0;
long int time = 0;
const int pinoInterrupcao = 2;

// Variáveis Sensor Hall
const int sensorPin = A1; // Pino de entrada analógica
const int baixoLimite = 510; // Limite inferior para o nível baixo
const int medioLimite = 495; // Limite inferior para o nível médio
int valorLido = 0;

// Variáveis combustivel/rpm
const int switchPin = 3; // Pino do interruptor
int contadorPulso = 0;
int contadorRotacao = 0;

/*//parte do rpm
 double lastTime = 0; // Último tempo de leitura
float rpm = 0; // RPM calculadas
double elapsedTime=0;
*/

// Variáveis do painel
const int ledVerde = 9;
const int ledAmarelo = 8;
const int ledVermelho = 10;

uint8_t LT[8]  = {0xF, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
uint8_t UB[8]  = {0x1F, 0x1F, 0x1F, 0x0, 0x0, 0x0, 0x0, 0x0};
uint8_t RT[8] = { 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
uint8_t LL[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0xF};
uint8_t LB[8]  = {0x0, 0x0, 0x0, 0x0, 0x0, 0x1F, 0x1F, 0x1F};
uint8_t LR[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1E};
uint8_t UMB[8] = {0x1F, 0x1F, 0x1F, 0x0, 0x0, 0x0, 0x1F, 0x1F};
uint8_t LMB[8] = {0x1F, 0x0, 0x0, 0x0, 0x0, 0x1F, 0x1F, 0x1F};

int cursor=5;//posição do cursor
int x=cursor;
  
LiquidCrystal_I2C lcd(0x27,12,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display



void n0()//Seleciona os segmentos para formar o numero 0
{ 
  lcd.setCursor(x, 0); //Seleciona a linha superior
  lcd.printByte((byte)0);  //Segmento 0 selecionado
  lcd.printByte(1);  //Segmento 1 selecionado
  lcd.printByte(2);
  lcd.setCursor(x, 1); //Seleciona a linha inferior
  lcd.printByte(3);  
  lcd.printByte(4);  
  lcd.printByte(5);
}
void n1() //Seleciona os segmentos para formar o numero 1
{
  lcd.setCursor(x+1,0);
  lcd.printByte(2);
  lcd.setCursor(x+1,1);
  lcd.printByte(5);
}
void n2() //Seleciona os segmentos para formar o numero 2
{
  lcd.setCursor(x,0);
  lcd.printByte(6);
  lcd.printByte(6);
  lcd.printByte(2);
  lcd.setCursor(x, 1);
  lcd.printByte(3);
  lcd.printByte(7);
  lcd.printByte(7);
}
void n3()  //Seleciona os segmentos para formar o numero 3
{
  lcd.setCursor(x,0);
  lcd.printByte(6);
  lcd.printByte(6);
  lcd.printByte(2);
  lcd.setCursor(x, 1);
  lcd.printByte(7);
  lcd.printByte(7);
  lcd.printByte(5); 
}
void n4()  //Seleciona os segmentos para formar o numero 4
{
  lcd.setCursor(x,0);
  lcd.printByte(3);
  lcd.printByte(4);
  lcd.printByte(2);
  lcd.setCursor(x+2, 1);
  lcd.printByte(5);
}
void n5()  //Seleciona os segmentos para formar o numero 5
{
  lcd.setCursor(x,0);
  lcd.printByte((byte)0);
  lcd.printByte(6);
  lcd.printByte(6);
  lcd.setCursor(x, 1);
  lcd.printByte(7);
  lcd.printByte(7);
  lcd.printByte(5);
}
void n6()  //Seleciona os segmentos para formar o numero 6
{
  lcd.setCursor(x,0);
  lcd.printByte((byte)0);
  lcd.printByte(6);
  lcd.printByte(6);
  lcd.setCursor(x, 1);
  lcd.printByte(3);
  lcd.printByte(7);
  lcd.printByte(5);
}
void n7() //Seleciona os segmentos para formar o numero 7
{
  lcd.setCursor(x,0);
  lcd.printByte(1);
  lcd.printByte(1);
  lcd.printByte(2);
  lcd.setCursor(x+2,1);
  lcd.printByte(5);
}
void n8()  //Seleciona os segmentos para formar o numero 8
{
  lcd.setCursor(x,0);
  lcd.printByte((byte)0);
  lcd.printByte((byte)6);
  lcd.printByte(2);
  lcd.setCursor(x, 1);
  lcd.printByte(3);
  lcd.printByte(7);
  lcd.printByte(5);
}
void n9()  //Seleciona os segmentos para formar o numero 9
{
  lcd.setCursor(x,0);
  lcd.printByte((byte)0);
  lcd.printByte((byte)6);
  lcd.printByte((byte)2);
  lcd.setCursor(x+2, 1);
  lcd.printByte((byte)5);
}
void mostraNumero(int numero) //Mostra o numero na posicao definida por "X"
{
  lcd.clear();
  int n=numero/10;
  for(int i=0;i<2;i++){
  switch(n)
    {
      case 0:n0();
      break;
      case 1:n1();
      break;
      case 2:n2();
      break;
      case 3:n3();
      break;
      case 4:n4();
      break;
      case 5:n5();
      break;
      case 6:n6();
      break;
      case 7:n7();
      break;
      case 8:n8();
      break;
      case 9:n9();
      break;
    }
    x=cursor+3;//posição do cursor n1
    n=numero%10;
  }
  x=cursor;//posição do cursor n0
}

//função acelerometro
void velocidade() {
  velo = 1.7278 / (millis() - time); // velocidade em m/ms
  velo = velo * 3600;
  time = millis();
}

void pulso(){
 contadorPulso++;
}


void setup()
{
  // Setup do painel
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  
  //setup lcd
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  
  //Associa cada segmento criado, a um número
  lcd.createChar(0, LT);
  lcd.createChar(1, UB);
  lcd.createChar(2, RT);
  lcd.createChar(3, LL);
  lcd.createChar(4, LB);
  lcd.createChar(5, LR);
  lcd.createChar(6, UMB);
  lcd.createChar(7, LMB);
  lcd.home();
  
  lcd.print("iniciando...");
  lcd.setCursor(0, 1);
  lcd.print("Boa sorte!");
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledAmarelo, HIGH);
  digitalWrite(ledVermelho, HIGH);
  delay(3000);
  lcd.clear();

  
  //setup velocimetro
  Serial.begin(9600);
  pinMode(pinoInterrupcao, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinoInterrupcao), velocidade, FALLING);

  // setup snssor de combustivel/rpm
  pinMode(switchPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(switchPin), pulso, RISING);
  
}

void loop()
{

  if (millis() - time > 3000) {
    velo = 0;
  }
  Serial.println(velo);
  mostraNumero(velo);
  Serial.println(digitalRead(pinoInterrupcao));
  delay(1000);
  
  // Código Sensor de combustivel/rpm
  contadorRotacao = contadorPulso*4;
    
  if (contadorRotacao > 186210) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
  }
  else if (contadorRotacao > 93105) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, HIGH);
  }
  else {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, HIGH);
  }
}
