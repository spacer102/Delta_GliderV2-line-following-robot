#include <elapsedMillis.h>
elapsedMillis stratenyCas;
elapsedMillis ignorujSenzory;

#define MID_PROX A0
const int LEFT_PROX = 4;
const int RIGHT_PROX = 2;

const int ENA = 8;
const int IN1 = 9;
const int IN2 = 10;
const int IN3 = 6;
const int IN4 = 5;
const int ENB = 7;

int AVOID_LEFT;
int AVOID_RIGHT;

#define OUT0 11
#define OUT1 A5
#define OUT2 A4
#define OUT3 A3
#define OUT4 A2
#define OUT5 A1
#define OUT6 12

void setup() {
 AVOID_LEFT = digitalRead(LEFT_PROX);
 AVOID_RIGHT = digitalRead(RIGHT_PROX);
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 
 pinMode(OUT0, INPUT);
 pinMode(OUT1, INPUT);
 pinMode(OUT2, INPUT);
 pinMode(OUT3, INPUT);
 pinMode(OUT4, INPUT);
 pinMode(OUT5, INPUT);
 pinMode(OUT6, INPUT);

}

void loop() {

int FULL_RIGHT = digitalRead(OUT0);     
int RIGHT = analogRead(OUT1);
int RIGHT_MID = analogRead(OUT2);
int MID = analogRead(OUT3);       
int LEFT_MID = analogRead(OUT4);
int LEFT = analogRead(OUT5);
int FULL_LEFT = digitalRead(OUT6);

int AVOID_MID = analogRead(MID_PROX);

if(ignorujSenzory>800) {
AVOID_LEFT = digitalRead(LEFT_PROX);
AVOID_RIGHT = digitalRead(RIGHT_PROX); }


/*Serial.print("MID_PROX => ");
Serial.println(AVOID_MID);
Serial.println();

Serial.print("RIGHT_PROX => ");
Serial.println(AVOID_RIGHT);
Serial.println();

Serial.print("LEFT_PROX => ");
Serial.print(digitalRead(LEFT_PROX));
Serial.println();

Serial.print("FULL RIGHT => ");
Serial.print(FULL_RIGHT);
Serial.println();

Serial.print("RIGHT => ");
Serial.print(RIGHT);
Serial.println();

Serial.print("RIGHT MID => ");
Serial.print(RIGHT_MID);
Serial.println();

Serial.print("MID => ");
Serial.print(MID);
Serial.println();

Serial.print("LEFT MID => ");
Serial.print(LEFT_MID);
Serial.println();

Serial.print("LEFT => ");
Serial.print(LEFT);
Serial.println();

Serial.print("FULL LEFT => ");
Serial.print(FULL_LEFT);
Serial.println();*/

if(AVOID_MID<850) {
  move_backward(120);
  delay(140);
  Stop();
  delay(100);
 
  do {
  spin_left(70);
  RIGHT=analogRead(OUT1);
  }while(RIGHT>=500);

  spin_left(82);
  delay(90);

  move_forward(100);
  delay(420);
  spin_right(80);
  delay(180);

  elapsedMillis long_last;
  while(long_last<=290){
    if(AVOID_LEFT==0 || AVOID_RIGHT==0) { break;}
    move_forward(100);
  }
  
  Stop();
  delay(100);
  elapsedMillis dlzka_trv;
  move_forward(100);
  delay(50);
   

  while(1) {
    avoid_left(70);
    RIGHT_MID = analogRead(OUT2);
    LEFT_MID = analogRead(OUT4);
    AVOID_LEFT = digitalRead(LEFT_PROX);
    AVOID_RIGHT = digitalRead(RIGHT_PROX);

    if(AVOID_LEFT==0 && AVOID_RIGHT==0){
      move_forward(60);
    }

    if(!(AVOID_LEFT==0 && AVOID_RIGHT==0)){
       if(AVOID_LEFT==0) {
            spin_right(225); }
    
       if(AVOID_RIGHT==0) {
            spin_left(225);  }
    }
    
    if(RIGHT_MID<500 && dlzka_trv>700) {
      move_forward(150);
      delay(100);
      Stop();
      delay(50);
      spin_left(140);
      delay(180);
      break;
    }
    if(LEFT_MID<500 && dlzka_trv>700){
      move_forward(150);
      delay(100);
      Stop();
      delay(50);
      spin_right(140);
      delay(180);
      break;
    }
  }
  ignorujSenzory=0;
  AVOID_LEFT=1;
  AVOID_RIGHT=1;
  Stop();
}


if(AVOID_LEFT==0){
  move_backward(120);
  delay(50);
  spin_left(140);
  delay(200);
  Stop();
  delay(50);                           //vyjdi s ciary
  avoid_right(80);
  delay(200);
  elapsedMillis wasteTime;

  do {                                //zatacaj doprava a zaroven sleduj vzdialenosti senzorov
    AVOID_MID = analogRead(MID_PROX);
    AVOID_RIGHT = digitalRead(RIGHT_PROX);
    
    if(AVOID_MID<800 || AVOID_RIGHT==0) {
      spin_left(120);
    }
    else {
      avoid_left(75);
    }
    RIGHT = analogRead(OUT1);
    LEFT = analogRead(OUT5);

    if(wasteTime<750) {
      RIGHT=900;
      LEFT=900;
    }
    
  }while(RIGHT>500 && LEFT>500);

  Stop();                              //ked zachytis ciaru vyrovnaj sa na nej
  delay(50);
  move_forward(150);
  delay(100);
  spin_left(140);
  delay(240);
}


if(AVOID_RIGHT==0){
  move_backward(120);
  delay(50);
  spin_right(140);
  delay(200);
  Stop();
  delay(50);
  avoid_left(80);
  delay(200);
  elapsedMillis wasteTime;

  do {
    AVOID_MID = analogRead(MID_PROX);
    AVOID_LEFT = digitalRead(LEFT_PROX);
    
    if(AVOID_MID<800 || AVOID_LEFT==0) {
      spin_right(120);
    }
    else {
      avoid_right(75);
    }
    RIGHT = analogRead(OUT1);
    LEFT = analogRead(OUT5);

    if(wasteTime<750) {
      RIGHT=900;
      LEFT=900;
    }
    
  }while(RIGHT>500 && LEFT>500);

  Stop();
  delay(50);
  move_forward(150);
  delay(100);
  spin_right(140);
  delay(240);
}

if(FULL_RIGHT == 1) {
  stratenyCas=0;
  //Serial.println("UPLNE DOPRAVA");
  spin_right(80);
}

if(RIGHT < 500) {
  //Serial.println("DOPRAVA");
  spin_right(80);
}
if(RIGHT_MID < 500) {
  //Serial.println("TROCHU DOPRAVA");
  spin_right(50);
}

if(MID < 500) {
  //Serial.println("RYCHLO ROVNO");
  move_forward(140);
}

if(LEFT_MID < 500) {
  //Serial.println("TROCHU DOLAVA");
  spin_left(50);
}
if(LEFT < 500) {            
  spin_left(80);
}

  if(stratenyCas>=400 && FULL_LEFT == 1){spin_left(80);}
  if((stratenyCas<400 && FULL_LEFT == 1) || (FULL_RIGHT==1 && RIGHT<500 && RIGHT_MID<500 && MID<500 && LEFT_MID<500)) { //ak lavy senzor a pravy sa prekryju vo velmi kratkom case tak zacni pohyb na obchadzanie skrvny
    Stop();
    move_backward(80);         //cuvni dozadu
    delay(240);
    Stop();
    
    do{
      FULL_LEFT=digitalRead(OUT6);    //najdi ciaru pravym senzorom, tak aby si bol v uhle cca 70°
      spin_right(120);
    }while(FULL_LEFT==0);
    Stop();
    move_forward(100);        //prekroc ciaru
    delay(100);

    do {
      FULL_LEFT = digitalRead(OUT6);       //zrovnaj sa uplne celkovo 90° uhle od prekazky
      avoid_right(80);
    }while(FULL_LEFT==0);

    elapsedMillis skrvnaTime;
    do {                                     //obchadzaj prekazku 
      LEFT = analogRead(OUT5);
      FULL_LEFT = digitalRead(OUT6);
      
      if(FULL_LEFT==0) {
        spin_left(70); }
      else if(FULL_LEFT==1) {
        avoid_left(90); }
      if(skrvnaTime<1500) { FULL_LEFT=0; LEFT=800;}   
    }while(LEFT >= 500);

    move_forward(120);
    delay(20);
    Stop();                           //ak sa dostanes uz na ciaru trochu pod dopredu a zarovnaj sa s nou
    delay(100);
    spin_left(80);
    delay(50);
    move_forward(120);
    delay(150);

    do {
     LEFT_MID = analogRead(OUT4); //tato cast je pre pripad zeby nezachytila ciaru. V takom to pripade sa toc doprava pokial sa senzor nalavo neprekryje 
     spin_right(70);
    }while(LEFT_MID>=500);

    Stop();
    delay(100);
  }

else if(FULL_RIGHT == 0 && RIGHT >= 500 && RIGHT_MID >= 500 && MID >= 500 && LEFT_MID >= 500 && LEFT >= 500 && FULL_LEFT == 0) {
  //Serial.println("ROVNO");
  push_forward();
}
}


void push_forward() {
  digitalWrite(ENA, HIGH);
  analogWrite(IN1, 255);
  delayMicroseconds(9000);
  analogWrite(IN1, 0);
  delayMicroseconds(15000);

  digitalWrite(ENB, HIGH);
  analogWrite(IN3, 255);
  delayMicroseconds(9000);
  analogWrite(IN3, 0);
  delayMicroseconds(15000);

  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}//--------------------------------------------
void avoid_right (int Speed) {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  analogWrite(IN2, 0);
  analogWrite(IN1, Speed-60);
  analogWrite(IN4, 0);
  analogWrite(IN3, Speed);
}//--------------------------------------------
void avoid_left (int Speed) {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  analogWrite(IN2, 0);
  analogWrite(IN1, Speed);
  analogWrite(IN4, 0);
  analogWrite(IN3, Speed-20);
}//--------------------------------------------
void move_forward (int Speed) {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  analogWrite(IN2, 0);
  analogWrite(IN1, Speed);
  analogWrite(IN4, 0);
  analogWrite(IN3, Speed+18);
}//--------------------------------------------
void move_backward (int Speed) {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  analogWrite(IN2, Speed);
  analogWrite(IN1, 0);
  analogWrite(IN4, Speed);
  analogWrite(IN3, 0);
}//--------------------------------------------
void spin_right (int Speed) {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  analogWrite(IN2, 0);
  analogWrite(IN1, Speed);
  analogWrite(IN4, Speed);
  analogWrite(IN3, 0);
}//--------------------------------------------
void spin_left (int Speed) {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  analogWrite(IN2, Speed);
  analogWrite(IN1, 0);
  analogWrite(IN4, 0);
  analogWrite(IN3, Speed);
}//--------------------------------------------
void Stop(){
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  analogWrite(IN2, 0);
  analogWrite(IN1, 0);
  analogWrite(IN4, 0);
  analogWrite(IN3, 0);                                                     
}//--------------------------------------------
