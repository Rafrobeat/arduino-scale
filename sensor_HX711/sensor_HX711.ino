#include <HX711.h>

// ==================================================================================================
//      Sensor HX711 maneja pesos desde 0,01 g
// ==================================================================================================

#include <LiquidCrystal_I2C.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Conexiones:
// GND - GND
// VCC - 5V
// SDA - ANALOG A0
// SCL - ANALOG A1


HX711 scale;  

long pesoBruto;                 // Valor bruto entregado por el HX711
long offset = -115920;          // offset
float Scale = 6647.4;           // escala
float Masa;                  // berechnete Masa in g

const int buttonPin = 13;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status


// =====================
// ======= SETUP =======
// =====================

void setup()
   { 
    Serial.begin(115200); 

    scale.begin(A1, A0);
    
    scale.set_gain(128);   // A-Kanal: gain = 64 oder 128; B-Kanal: fix 32
    
    pinMode(buttonPin, INPUT);
    
    lcd.init();                      // initialize the lcd

    // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(2,0);
    lcd.print("Iniciando...");
    
    delay(3000);
    
    lcd.setCursor(4,0);
    lcd.print("             ");
    lcd.setCursor(0,0);
    lcd.print("Peso = ");    
   }


// ============================
// ======= HAUPTSCHLEIFE ======
// ============================

void loop()
   {
    buttonState = digitalRead(buttonPin);    // Boton para nueva tara (offset)
    
    if (buttonState == HIGH)
       {        
        scale.read_average(20);
        offset = scale.read_average(20);   //  Lectura de 20 valores brutos para determinar la tara (offset)
       }
     
    scale.read_average(20);
    pesoBruto = scale.read_average(20);   // Lectura de 20 valores brutos
  
    Masa = (pesoBruto - offset) / Scale;  // Cálculo de la masa en gramos
  
    /*
    Serial.print("Wert = ");
    Serial.println(pesoBruto);
    */
    
    Serial.print("Masa = ");
    Serial.println(Masa,2);
    
    
    lcd.setCursor(7,0);
    lcd.print("            ");
    lcd.setCursor(7,0);
    lcd.print(Masa,2);
    lcd.setCursor(5,1);
    lcd.print(" gramos");
        
    delay(50);
   }   
