#include <Arduino.h>

#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;


// Broches du L298N
const int motorPWM1 = 2;
const int motorPWM2 = 4;
const int motorIN1 = 5;
const int motorIN2 = 18;
const int motorIN3 = 19;
const int motorIN4 = 21;

// Broches des encodeurs
const int encoderPinA1 = 33;
const int encoderPinB1 = 25;
const int encoderPinB2 = 26;
const int encoderPinA2 = 27;

volatile long encoderCount1 = 0;
volatile long encoderCount2 = 0;
int dif = 0;
int a = 0;
int corr = 0.05;
int vit = 150;
int vit2 = 90;

void setup() {
  pinMode(motorPWM1, OUTPUT);
  pinMode(motorPWM2, OUTPUT);
  pinMode(motorIN1, OUTPUT);
  pinMode(motorIN2, OUTPUT);
  pinMode(motorIN3, OUTPUT);
  pinMode(motorIN4, OUTPUT);

  pinMode(encoderPinA1, INPUT);
  pinMode(encoderPinA2, INPUT);
  pinMode(encoderPinB1, INPUT);
  pinMode(encoderPinB2, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoderPinA1), updateEncoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderPinA2), updateEncoder2, RISING);

  // Serial.begin(9600);

  encoderCount1 = 0;
  encoderCount2 = 0;

  SerialBT.begin("PAMI 1"); //Bluetooth device name
  // Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  // for (int i = 0; i < 15; i++) {
  //   Serial.println(); // Envoyer plusieurs retours à la ligne
  // }
  // Serial.print("encodeur 1 : ");
  // Serial.println(encoderCount1);
  // Serial.print("encodeur 2 : ");
  // Serial.println(encoderCount2);
  // Serial.print("dif : ");
  // Serial.println(dif);
  // delay(100);

  // if (SerialBT.connected()) droite(vit2, vit2);
  // else avancer(0, 0);

  if (SerialBT.available()) {
    // Serial.println("loop");
    int r = SerialBT.read();
    // Serial.print("input : ");
    // Serial.println(r);
    if(r == '1'){
      avancer(vit+corr*dif, vit-corr*dif);
      a = 1;
      // Serial.print("encodeur 1 : ");
      // Serial.println(encoderCount1);
      // Serial.print("encodeur 2 : ");
      // Serial.println(encoderCount2);
      // Serial.print("dif : ");
      // Serial.println(dif);
    }
    if(r == '2'){
      avancer(vit2, 0);
    }
    if(r == '3'){
      droite(vit2, vit2);
    }
    if(r == '4'){
      reculer(vit2, 0);
    }    
    if(r == '5'){
      reculer(vit, vit);
    }    
    if(r == '6'){
      reculer(0, vit2);
    }    
    if(r == '7'){
      gauche(vit2, vit2);
    }    
    if(r == '8'){
      avancer(0, vit2);
    }    
    if(r == 'a'){
      encoderCount1 = 0;
      encoderCount2 = 0;
      dif=0;
      char cestpasbon=1;
      while(cestpasbon){
        int temp_dif=dif;
        avancer(150+a*dif, 150-a*dif);
        delay(500);
        if(abs(temp_dif - dif)<2) cestpasbon = 0;
      }
      corr = (int)(a*dif);
      r = 48;
    }

    if(r == 'b'){
      corr++;
    }   
    if(r == 'd'){
      corr--;
    }   
    if(r == 'c'){
      droite(60,60);
      /*
      int red = 700;
      delay(6000);
      avancer(vit, vit);
      delay(red);
      avancer(0, vit);
      delay(400);
      avancer(vit, vit);
      delay(red);
      reculer(vit, vit);
      delay(red);
      reculer(100, vit);
      delay(red);
      avancer(0,0);
      avancer(vit, vit);
      delay(red);
      avancer(0, vit);
      delay(400);
      avancer(vit, vit);
      delay(red);
      reculer(vit, vit);
      delay(red);
      reculer(100, vit);
      delay(red);
      avancer(0,0);
      avancer(vit, vit);
      delay(red);
      avancer(0, vit);
      delay(400);
      avancer(vit, vit);
      delay(red);
      reculer(vit, vit);
      delay(red);
      reculer(100, vit);
      delay(red);
      avancer(0,0);
      */
    }


    if(r == '0'){
      avancer(0, 0);
      a=0;
      // Serial.print("encodeur 1 : ");
      // Serial.println(encoderCount1);
      // Serial.print("encodeur 2 : ");
      // Serial.println(encoderCount2);
      // Serial.print("dif : ");
      // Serial.println(dif);
      // encoderCount1 = 0;
      // encoderCount2 = 0;
    }
  }

  /*
  avancer(150, 150);
  delay(1000);
  for(int i=0; i<5; i++){
    droite(150, 150);
    delay(1500);
    arret();
    delay(900);
  }
  */



  /*
  int vit = 0;
  encoderCount1 = 0;
  encoderCount2 = 0;
  while (vit<250){
    avancer(255-vit, vit);
    delay(100);
    vit++;
    Serial.print("Compteur Encoder 1 : ");
    Serial.println(encoderCount1);
    Serial.print("Compteur Encoder 2 : ");
    Serial.println(encoderCount2);
  }
  */
}


// int avancer2(int vm1, int vm2) {
//   digitalWrite(motorIN1, HIGH); 
//   digitalWrite(motorIN2, LOW); 
//   digitalWrite(motorIN3, HIGH); 
//   digitalWrite(motorIN4, LOW);
//   analogWrite(motorPWM1, vm1); 
//   analogWrite(motorPWM2, vm2);
//   return encoderCount2 - encoderCount1;
// }

void avancer(int vm1, int vm2) {
  digitalWrite(motorIN1, HIGH); 
  digitalWrite(motorIN2, LOW); 
  digitalWrite(motorIN3, HIGH); 
  digitalWrite(motorIN4, LOW);
  analogWrite(motorPWM1, vm1); 
  analogWrite(motorPWM2, vm2);
}

void reculer(int vm1, int vm2) {
  digitalWrite(motorIN1, LOW); 
  digitalWrite(motorIN2, HIGH); 
  digitalWrite(motorIN3, LOW); 
  digitalWrite(motorIN4, HIGH);
  analogWrite(motorPWM1, vm1); 
  analogWrite(motorPWM2, vm2);
}

void droite(int vm1, int vm2) {
  digitalWrite(motorIN1, HIGH); 
  digitalWrite(motorIN2, LOW); 
  digitalWrite(motorIN3, LOW); 
  digitalWrite(motorIN4, HIGH);
  analogWrite(motorPWM1, vm1); 
  analogWrite(motorPWM2, vm2);
}

void gauche(int vm1, int vm2) {
  digitalWrite(motorIN1, LOW); 
  digitalWrite(motorIN2, HIGH); 
  digitalWrite(motorIN3, HIGH); 
  digitalWrite(motorIN4, LOW);
  analogWrite(motorPWM1, vm1); 
  analogWrite(motorPWM2, vm2);
}

void arret() {
  digitalWrite(motorPWM1, LOW);
  digitalWrite(motorPWM2, LOW);
}

void updateEncoder1() {
  if (a==1){
    if (digitalRead(encoderPinB1) == digitalRead(encoderPinA1)) {
      encoderCount1++;
    } else {
      encoderCount1--;
    }
    dif = encoderCount2 - encoderCount1;
  }
}

void updateEncoder2() {
  if (a==1){
    if (digitalRead(encoderPinB2) == digitalRead(encoderPinA2)) {
      encoderCount2++;
    } else {
      encoderCount2--;
    }
  }
}
