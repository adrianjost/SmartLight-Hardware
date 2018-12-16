/**
Author: Adrian Jost
Version: 0.2.1
Date: 16 December 2018
**/
#include <FS.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <Hash.h>

// WIFI-Manager
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic


WebSocketsServer webSocket = WebSocketsServer(80);

// "NeoPixel", "Analog RGB"
//char lampType[64] = "Analog RGB";
int lampType = 2;


struct RGB {
  byte r;
  byte g;
  byte b;
};

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {
  switch(type) {
    case WStype_DISCONNECTED:{
        //color={0,0,0};
        //set_color();
        /*RGB oldcol = color;
        color={55,0,0};
        set_color();
        delay(1000);
        color=oldcol;
        set_color();
        */
      }
      break;
    case WStype_CONNECTED:{
      /*
        IPAddress ip = webSocket.remoteIP(num);
        RGB oldcol = color;
        color={0,55,0};
        set_color();
        delay(1000);
        color=oldcol;
        set_color();
        webSocket.sendTXT(num,"{\"hostname\":\""+host+"\"}");
        */
      }
      break;
    case WStype_TEXT:{
        String text = String((char *) &payload[0]);
        if(text=="RESET"){
          setColor(RGB{0,0,0});
        }
        else if(text.startsWith("J")){
          StaticJsonBuffer<100> jsonBuffer;
          String raw = (text.substring(text.indexOf("J")+1,text.length()));
          JsonObject& values = jsonBuffer.parseObject(raw);
          if (!values.success()) {
            setColor(RGB{55,55,0});
          }else{
            setColor(RGB{values["r"],values["g"],values["b"]});
          }
        }
      }
      break;
    case WStype_BIN:{
        //hexdump(payload, lenght);
        // echo data back to browser
        //webSocket.sendBIN(num, payload, lenght);
      }
      break;
  }
}

void setup() {
  initStrip();

  setColor(RGB{0,0,55});

  setupSpiffs();
  setupWifi();

  setColor(RGB{0,0,0});

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop(); // listen for websocket events
}
