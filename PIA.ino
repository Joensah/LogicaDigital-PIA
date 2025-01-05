//Jorge Enrique Salas Hernández
//Lógica Digital     Grupo: 004
//Avance #10


//Incluimos nuestras librerías y declaramos nuestras variables
#include <Wire.h> //Para el lcd
#include <LiquidCrystal_I2C.h>  //Esta es la librería que utilizaremos para utilizar la pantalla LCD con el módulo I2C
LiquidCrystal_I2C lcd(0x27,16,2); //Creamos un objeto de tipo liquidCrystal
const int echoPin1 = 11;  //ECHO de mi sensor ultrasónico 1
const int trigPin1 = 12;  //TRIG de mi sensor ultrasónico 1
const int echoPin2 = 8;  //ECHO de mi sensor ultrasónico 2
const int trigPin2 = 9;  //TRIG de mi sensor ultrasónico 2
int contador=0;  //num de personas dentro
const int buzzPin=7;  //para nuestro buzzer 
int ledEntra=6;  //Para nuestro led verde
int ledSale=5; //led rojo

long duracion1; //duracion de la onda
int distancia1; // distancia respecto el sensor

long duracion2;
int distancia2;
 
void setup() 
{
  pinMode(trigPin1, OUTPUT); //inicializamos el TRIG (manda la señal de SALIDA)
  pinMode(echoPin1, INPUT); //inicializamos dentro del setup el ECHO (RECIBE la señal que manda el TRIG)
  pinMode(trigPin2, OUTPUT); //inicializamos el TRIG (manda la señal de SALIDA)
  pinMode(echoPin2, INPUT); //inicializamos dentro del setup el ECHO (RECIBE la señal que manda el TRIG)
  Serial.begin(9600); //inicializamos nuesto monitor serial
  lcd.init();  //inicializamos el lcd
  lcd.backlight();  //control de la backlight
  pinMode(buzzPin,OUTPUT);  //el buzzer en modo OUTPUT
  pinMode(ledEntra,OUTPUT);  //el led en modo OUTPUT
  pinMode(ledSale,OUTPUT);  //el led en modo OUTPUT
}

void loop() 
{
  //PARA NUESTRO PRIMER SENSOR
  digitalWrite(trigPin1, LOW); //apagamos nuestro sensor HC-SR04 (si es que nuestro sensor ultrasónico está encendido)
  delayMicroseconds(2);  //Lo apagamos por 2 microsegundos
  digitalWrite(trigPin1, HIGH);  //Encendemos el sensor para que envíe una onda
  delayMicroseconds(10);  //Esa onda se va a estar enviando por 10 microsegundos(lo mínimo para que funcione)
  digitalWrite(trigPin1, LOW); //apagamos el sensor de nuevo
  duracion1 = pulseIn(echoPin1, HIGH);  //recibimos la onda de regreso y calculamos la duracion del pulso
  distancia1 = (duracion1 * 0.034) / 2;  //ahora se calcula la distancia con la fórmula (Velocidad=tiempo(0.034)*duracion/2)
  //velocidad =340 m/s     pero como son microsegundos es 0.034 cm/microsegundos
   // Se hace /2 por que no queremos que nos de la distancia del sensor al objeto y del objeto al sensor
  Serial.println(distancia1);  //Imprimimos la distancia en nuestro monitor serie

  //PARA EL SEGUNDO SENSOR
 digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duracion2 = pulseIn(echoPin2, HIGH);
  distancia2 = (duracion2 * 0.034) / 2;
  Serial.println(distancia2);
  
  if(distancia1 <6) //si la distancia es menor a 6
  {  
    contador++;     //suma el contador 
    digitalWrite(ledEntra,HIGH);  //enciende led verde
    tone(buzzPin,600); //funcion tone(pin, frecuencia)
    delay(200);  //duracion
    digitalWrite(ledEntra,LOW);  //apaga led
    noTone(buzzPin);  //funcion noTone(pin) que apaga el buzzer
  }

   if(distancia2 <6)  //si la distancia es menor a 6
  {
    contador--;  //resta el contador
    digitalWrite(ledSale,HIGH);  //enciende el led rojo
    tone(buzzPin,600); //funcion tone (pin, frecuencia)
    delay(200); //duracion
    digitalWrite(ledSale,LOW); //apaga el led
    noTone(buzzPin);  //apaga el buzzer
  }
  if(contador>=9){  //si el contador llegara mayor a 9
    contador=9;  //se queda en 9
  }
  if(contador<=0){  //si contador es menor a 0
    contador=0;  //se queda en 0
  }
  
    lcd.setCursor(0,0);  //Colocamos el cursor en la fila 0, columna 0
    lcd.print("   BIENVENIDO"); //imprimo el texto
    lcd.setCursor(0, 1); //Colocamos el cursor en la fila 0, columna 1
    lcd.print(" Hay "); //imprimo el texto
    lcd.print(contador);
    lcd.print(" personas"); //imprimo el texto
  
  delay(1000);  //retraso de 1 segundo
} 
