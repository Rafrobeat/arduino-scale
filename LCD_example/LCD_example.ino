/**
   GeekFactory - "Construye tu propia tecnologia"
   Distribucion de materiales para el desarrollo e innovacion tecnologica
   www.geekfactory.mx

   EJEMPLO BÁSICO PARA EL USO DEL LCD 16X2 A TRAVÉS DE I2C

   ESTE PROGRAMA MUESTRA UN MENSAJE EN UNA PANTALLA DE 16X2 Y REALIZA UNA ANIMACION
   DE DESPLAZAMIENTO DE UN EXTREMO A OTRO DE LA PANTALLA.
*/
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>

// Constructor de la librería de LCD 16x2
// Aqui se configuran los pines asignados a la pantalla del PCF8574
LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  // Inicializar el LCD
  lcd.init();

  //Encender la luz de fondo.
  lcd.backlight();
  // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.home ();
  // Imprimir "Hola Mundo" en la primera linea
  lcd.print("Hola Vale");
  // Mover el cursor a la segunda linea (1) primera columna
  lcd.setCursor ( 0, 1 );
  // Imprimir otra cadena en esta posicion
  lcd.print("NO PUEDO PESAR!");
  // Esperar un segundo
  delay(1000);
}

void loop()
{
  // EN EL CICLO PRINCIPAL SOLAMENTE RECORREMOS EL MENSAJE DE UN LADO A OTRO
  // Variable para conteo de ciclos
  int i;

  // Desplazar la pantalla a la derecha 2 veces
  for ( int i = 0; i < 5; i++ ) {
    lcd.scrollDisplayRight();
    delay (1000);
  }

  // Desplazar la pantalla a la izquierda 2 veces
  for ( int i = 0; i < 5; i++ ) {
    lcd.scrollDisplayLeft();
    delay (1000);
  }
}
