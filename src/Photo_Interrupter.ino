#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SPI.h>
#include "WIFI_SET.h"

int Led = 13; // 設定LED腳位
int P_I = 14; // 設定 photo interrupter 腳位
int val; //設定變數
int val1; //設定變數1

void setup()
{
    Serial.begin(115200);
    WIFI();
    Serial.println("");
    Serial.print("Connecting to ");
    Serial.println(ssid);
    Serial.println("WiFi connected");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    delay(5000);
    pinMode(Led, OUTPUT); // LED 腳位作為輸出
    pinMode(P_I, INPUT); //photo interrupter 腳位作為輸出
}

void loop()
{
    val=digitalRead(P_I); //讀取感應器的值
    val1 = analogRead(P_I);
    if(val == HIGH) // 當感應器被觸發時LED亮
    {
        digitalWrite(Led,HIGH);
        Serial.println(val1);
    }
    else
    {
        digitalWrite(Led,LOW);
        Serial.println(val1);
    }
}
