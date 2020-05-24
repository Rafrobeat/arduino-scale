// libreria para el sensor de peso
#include "HX711.h"

// libreria teclado
#include <Keypad.h>

// libreria para la pantalla LCD
#include "LiquidCrystal_I2C.h"
#include "Wire.h"

// entradas del sensor de peso
const int DOUT = A1;
const int CLK = A0;

float peso;

// entradas de la pantalla
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// zumbador y leds
// Declaración de las frecuencias de las notas musicales
const float c = 261.63; // Do (Octava 0)
const float d = 293.66; // Re (Octava 0)
const float e = 329.63; // Mi (Octava 0)
const float f = 349.23; // Fa (Octava 0)
const float g = 392.00; // Sol (Octava 0)
const float gS = 415.30;  // Sol# (Octava 0)
const float a = 440.00; // La (Octava 0)
const float b = 466.16; // La# (Octava 0)
const float cH = 523.25;   // Do (Octava 1)
const float cSH = 554.37;  // Do# (Octava 1)
const float dH = 587.33; // Re (Octava 1)
const float dSH = 622.25; // Re# (Octava 1)
const float eH = 659.26; // Mi (Octava 1)
const float fH = 698.46; // Fa (Octava 1)
const float fSH = 739.99; // Fa# (Octava 1)
const float gH = 783.99;  // Sol (Octava 1)
const float gSH = 830.61; // Sol# (Octava 1)
const float aH = 880.00; // La (Octava 1)

const int zumbador = 12; // Pin digital para el zumbador
const int LED_1 = 10; // Pin digital para el LED 1
const int LED_2 = 11; // Pin digital para el LED 2

// teclado
const byte filas = 4;     //Numero de filas del teclado
const byte columnas = 4;  //Numero de columnas del teclado

//Defino una matriz 4x4 con la posicion de las filas y columnas
char matriz[filas][columnas] =
{
  { 'D', 'C', 'B', 'A'},
  { '#', '9', '6', '3'},
  { '0', '8', '5', '2'},
  { '*', '7', '4', '1'},
};

byte pinesFilas[filas] = {9, 8, 7, 6};       //Pines donde van conectadas las filas del teclado
byte pinesColumnas[columnas] = {5, 4, 3, 2}; //Pines donde van conectadas las columnas del teclado

//Inicializo el teclado con el numero de filas, columnas, los pines del Arduino utilizados y la matriz
Keypad teclado = Keypad( makeKeymap(matriz), pinesFilas, pinesColumnas, filas, columnas);

// opcion teclado
int v1 = 0;

// variables para el rango
float peso_max, peso_min;

HX711 balanza;

void setup() {
  Serial.begin(9600);

  balanza.begin(DOUT, CLK);

  // zumbador y leds
  pinMode(zumbador, OUTPUT); // Pin digital 12 como salida
  pinMode(LED_1, OUTPUT); // Pin digital 10 como salida
  pinMode(LED_2, OUTPUT); // Pin digital 11 como salida

  // initialize the lcd
  lcd.init();

  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Iniciando...");

  balanza.set_scale(380.524905); // Establecemos la escala
  balanza.tare(20);  //El peso actual es considerado Tara.

  delay(100);

  lcd.setCursor(2, 1);
  lcd.print("Listo.");
  delay(1000);
  lcd.clear();
}

void loop() {
  //lcd.clear();
  digitalWrite(LED_2, LOW);
  v1 = GetNumber();
  while (v1 < 5000) {
    while (peso < v1) {
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, LOW);
      peso = balanza.get_units(20);
      peso_min = v1 - 5;
      Serial.println("Peso minimo: ");
      Serial.println(peso_min);
      peso_max = v1 + 5;
      Serial.println("Peso maximo: ");
      Serial.println(peso_max);
      Serial.println("Peso: ");
      Serial.println(peso);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Peso: ");
      lcd.setCursor(7, 0);
      lcd.print(balanza.get_units(20), 1);
      lcd.setCursor(6, 1);
      lcd.print("gramos");
      //delay(500);
      while (peso > peso_min && peso < peso_max) {
        Serial.println("Listo.");
        digitalWrite(LED_1, HIGH);
        tone(zumbador, c, 50);
        delay(250);
        tone(zumbador, d, 50);
        delay(150);
        tone(zumbador, e, 50);
        delay(350);
        peso = balanza.get_units(20);
      }
    }
    while (peso > v1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Peso excedido.");
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, HIGH);
      tone(zumbador, c, 1000);
      peso = balanza.get_units(20);
      delay(500);
    }
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    noTone(zumbador);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("peso no valido.");
  lcd.setCursor(0, 1);
  lcd.print("max. 5000 gramos");
  digitalWrite(LED_2, HIGH);
  tone(zumbador, c, 1000);
  delay(3000);
}

int GetNumber()
{
  int num = 0;
  char key = teclado.getKey();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ing. Peso:");
  lcd.setCursor(1, 1);
  lcd.print("maximo 5000 gr");
  lcd.setCursor(11, 0);
  while (key != '#')
  {
    switch (key)
    {
      case NO_KEY:
        break;

      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        lcd.print(key);
        num = num * 10 + (key - '0');
        break;

      case '*':
        num = 0;
        lcd.clear();
        break;
    }
    key = teclado.getKey();
  }
  return num;
}
