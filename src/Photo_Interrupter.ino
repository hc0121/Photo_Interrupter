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

const String serverName = "http://192.168.0.111:3000/api/database/PhotoInterrupter/";

unsigned long lastTime = 0;
// 如果要設定為10分鐘 timerDelay = 600000;
// 如果要設定為5秒鐘 timerDelay = 1000;
// 如果要設定為10分鐘 timerDelay = 600000;
// 如果要設定為5秒鐘 timerDelay = 1000;
unsigned long timerDelay = 1000;

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
    if ((millis() - lastTime) > timerDelay) {
    //檢查 WIFI 連接狀況
        if(WiFi.status()== WL_CONNECTED){
            WiFiClient client;
            HTTPClient http;
            //URL路徑或IP位置
            String serverName = "http://192.168.0.111:3000/api/database/PhotoInterrupter/";
            val = digitalRead(P_I); //讀取感應器的值
            val1 = analogRead(P_I);
            Serial.println(val1);
            if(val == HIGH) // 當感應器被觸發時LED亮
            {
                Serial.println("correct");
                digitalWrite(Led,HIGH);
                String serverPath = serverName ;
                serverName=serverName+ "/";
                Serial.println(serverName);
      
                // Your Domain name with URL path or IP address with path
                http.begin(client, serverPath.c_str());
      
                // 發送 HTTP GET request
                int httpResponseCode = http.GET();
      
                if (httpResponseCode>0) {
                    Serial.print("HTTP Response code: ");
                    Serial.println(httpResponseCode);
                    String payload = http.getString();
                    Serial.println(payload);
                }
                else {
                    Serial.print("Error code: ");
                    Serial.println(httpResponseCode);
                }
                http.end();
            }
            else
            {
                Serial.println("error");
                //serverName = serverName + "false";
                digitalWrite(Led,LOW);
            }
            
        }
        else {
            Serial.println("WiFi Disconnected");
        }
        lastTime = millis();
    }
}
