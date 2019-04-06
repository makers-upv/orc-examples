#include <SoftwareSerial.h>
#include <HC_SR04.h>
#include <ORC.h>
// Ejemplo Librería para el kit de robótica de la ORC 2.16 Organizada por Makers UPV
// http://www.makersupv.com
// Incluye la librería de Ultrasonidos HC-SR04: http://playground.arduino.cc/Code/SR04
// Codificado por Guillermo Orts y por Germán Torres

/*
 * Ejemplo control velocidad mediante joystick robot ORC
 * Instalar libreria ORC antes de usar (Gestor de librerias -> Olympic Robotic Challenge)
 * por Jaime Laborda
 */

//Límites de motores
const int MOT_L_MIN = -255;
const int MOT_L_MAX = 255;
const int MOT_R_MIN = 255;
const int MOT_R_MAX = -255;
int limites_motores[4];

SoftwareSerial BT(4, 2);

void setup() {
  //Inicializa la librería
  inicializar();
  //Metemos en el vector de límites los límites de los motores;
  limites_motores[0] = MOT_L_MIN;
  limites_motores[1] = MOT_L_MAX;
  limites_motores[2] = MOT_R_MIN;
  limites_motores[3] = MOT_R_MAX;

  Serial.begin(9600);
  BT.begin(9600);

  //Espera a que se pulse el botón de inicio:
  //espera();
}

void loop() {
  //Código aquí:
  static int motorL, motorR;
  int X, Y;

  if (BT.available() >= 2) //Si hay mas de dos bytes disponibles en el buffer
  {
    //Los lee y los muestra por Serial
    Serial.print("X: "); //X
    Serial.print(X = BT.read(), DEC);
    Serial.print("  Y: "); //Y
    Serial.println(Y = BT.read(), DEC);

    if (Y > 128) //FORWARD
    {
      motorL = map(Y, 128, 255, 0, 255);
      motorR = map(Y, 128, 255, 0, 255);
      //Serial.println("FORWARD: " + motorL);
    }
    if (Y < 128) //BACKWARD
    {
      motorL = map(Y, 128, 0, 0, -255);
      motorR = map(Y, 128, 0, 0, -255);
      //Serial.println("BACKWARD: " + motorL);
    }
    if (Y == 128)
    {
      motorL = 0;
      motorR = 0;
    }
  }


  motores(motorL, motorR, limites_motores);
}
