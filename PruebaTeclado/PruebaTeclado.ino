#include <Keypad.h>
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>

// Constructor de la librería de LCD 16x2
// Aqui se configuran los pines asignados a la pantalla del PCF8574
LiquidCrystal_I2C lcd(0x27,16,2);

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

void setup()
{
  // Inicializar el LCD
  lcd.init();

  //Encender la luz de fondo.
  lcd.backlight();
  //Serial.begin(9600);   //Inicializo el puerto serie
}

void loop()
{
  char tecla_presionada = teclado.getKey();    //Almaceno en una variable la tecla presionada

  // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.home ();
  
  if (tecla_presionada)
  {
    Serial.println(tecla_presionada);   //Muestra la tecla presionada en el monitor serie
    lcd.print("Hola Vale");
    // Mover el cursor a la segunda linea (1) primera columna
    lcd.setCursor ( 0, 1 );
    lcd.print(tecla_presionada);
  }
}
