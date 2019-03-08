/*
-------------------------------------------------------------------
    Ejemplo de control de motores
    ORC 2.19
--------------------------------------------------------------------
    Esta función espera por puerto serie una cadena de forma:
    FX,Y //Mover hacia delante
    BX,Y //Mover hacia detrás
    dónde X e Y son los valores de los motores izquierdo y derecho
    respectivamente para calibrar que el robot vaya recto.
--------------------------------------------------------------------
*/


//Motor A (Left)
#define PIN_IN1 
#define PIN_IN2

// Motor B (Right)
#define PIN_IN3
#define PIN_IN4

char recibido;

void setup() {
    //Inicializamos el puerto serie
    Serial.begin(9600);
    
    //Declaramos los pines de control del driver como salida (PWM)
    pinMode(PIN_IN1, OUTPUT);
    pinMode(PIN_IN2, OUTPUT);
    pinMode(PIN_IN3, OUTPUT);
    pinMode(PIN_IN4, OUTPUT);
}

void loop() {
    //Espera a que le llegue algo al puerto serie
    while (!Serial.available());

    recibido = Serial.read(); //Lee el primer caracter
    if (recibido == 'F') { //Si detecta "F"
        int L, R;
        Serial.println("Recibido F");
        L =int( Serial.parseInt()); //Lee primer valor
        R =int( Serial.parseInt()); //Lee segundo valor
        Serial.print("Rueda L: ");
        Serial.print(L);
        Serial.print(" Rueda R: ");
        Serial.println(R);
        motores(L, R);
    }
    else if (recibido == 'B') { //Si detecta "B"
        int L, R;
        Serial.println("Recibido B");
        L =int( Serial.parseInt()); //Lee primer valor
        R =int( Serial.parseInt()); //Lee segundo valor
        Serial.print("Rueda L: ");
        Serial.print(-L);
        Serial.print(" Rueda R: ");
        Serial.println(-R);
        motores(-L, -R);
    }
}

void motores (int mot_L, int mot_R){
    //Restringe el rango de la entrada (en porcentaje)
    mot_L=constrain(mot_L,-100,100);
    mot_R=constrain(mot_R,-100,100);

    //Mapeo los valores de porcentaje a resolución de 8 bit PWM
    mot_L=map(mot_L,-100,100,-255,255);
    mot_R=map(mot_R,-100,100,-255,255);
    
    //Lógica de decisión:
    if(mot_L>0){
        analogWrite(PIN_IN1,mot_L);
        analogWrite(PIN_IN2,0);
    }
    else if(mot_L==0){
        analogWrite(PIN_IN1,0);
        analogWrite(PIN_IN2,0);
    }else{
        analogWrite(PIN_IN1,0);
        analogWrite(PIN_IN2,-1*mot_L);
    }

    if(mot_R>0){
        analogWrite(PIN_IN3,mot_R);
        analogWrite(PIN_IN4,0);
    }else if(mot_R==0){
        analogWrite(PIN_IN3,0);
        analogWrite(PIN_IN4,0);
    }else{
        analogWrite(PIN_IN3,0);
        analogWrite(PIN_IN4,-1*mot_R);
    }
}