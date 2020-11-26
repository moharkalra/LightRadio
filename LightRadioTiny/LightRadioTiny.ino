#include <Servo.h>
#include <Si4703_Tiny.h>



#include <LRWire.h>



int MOTOR = 5;
int OUT = A3;
int OUT2 = A1;
int resetPin = A2;
int SDIO = A6;
int SCLK = A4;
Si4703_Tiny radio(resetPin, SDIO, SCLK);
Servo servo;

int pos = 0;
int channel = 0;
void setup() {
    
  
    servo.attach(MOTOR);
    servo.write(90);
    radio.powerOn();
    
    radio.setVolume(0);
    
    radio.setSNRThresh(0x0030);
    radio.setSeekThresh(0x2F);
    pinMode(OUT, OUTPUT);
    digitalWrite(OUT, LOW);
    pinMode(OUT2, OUTPUT);
    digitalWrite(OUT2, HIGH);
}

void loop() {
 
  radioCycle(radio.readRSSI());

  delay(2000);
}
void radioCycle(int snr){
  if(snr<25 || channel == 0){
 
    channel = radio.seekUp();
    
    int rssi = radio.readRSSI();
    while(channel!= 0 && rssi<=40){
       channel = radio.seekUp();
       rssi = radio.readRSSI();
       delay(70);
     
    }
  }
  pivot();

}
void pivot(){
  if(channel==0){ 
    
    servo.write(0); 
    pos = 90; 
    digitalWrite(OUT, HIGH);
    digitalWrite(OUT2, LOW);
    radio.setChannel(875);
    
    radio.setVolume(0);
   
  }
  else{
    servo.write(90); 
    pos = 0;
    digitalWrite(OUT, LOW);
    digitalWrite(OUT2, HIGH);
    radio.setVolume(5);
  
  }
  
}
