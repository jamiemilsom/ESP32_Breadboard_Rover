#include <Arduino.h>
#include "WiFi.h"
#include <ESP32softPWM.hpp>

#define WIFI_NETWORK "Jamie Room"
#define WIFI_PASSWORD "youwillnevergetthis"
#define WIFI_TIMEOUT_MS 20000

void connectToWiFi(){
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK,WIFI_PASSWORD);

  unsigned long startAttemptTime = millis();

  while(WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS){
    Serial.print(".");
    delay(100);
  }

  if(WiFi.status() != WL_CONNECTED){
    Serial.println(" Failed!");
      //take action
  }else{
    Serial.print("Connected!");
    Serial.println(WiFi.localIP());
  }
}



ESP32softPWM PWM;

const int right_wheel_forward = 32;
const int right_wheel_backward = 33;
const int left_wheel_forward = 25;
const int left_wheel_backward = 26;
const int max_value = 1023;


void setup() {
  Serial.begin(9600);
  connectToWiFi();
  PWM.attach(0, right_wheel_forward);
  PWM.attach(1, right_wheel_backward);
  PWM.attach(2, left_wheel_forward);
  PWM.attach(3, left_wheel_backward);
  

}

void loop() {
  PWM.update();
  PWM.set(0,max_value * 1, 100);
  
}