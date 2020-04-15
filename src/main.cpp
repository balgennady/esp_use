/**
 * Устройство с ESP8266, отправка данных в реальном времени
 * https://esp8266.ru/forum/threads/ustrojstvo-s-esp8266-otpravka-dannyx-v-realnom-vremeni.4874/post-71451
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h> // клиент, который может соединяться с указанным IP-адресом через определенный порт 
#include <ESP8266WebServer.h>
/**
 * веб-сервер, который знает, как обрабатывать HTTP-запросы, такие как GET и POST, 
 * и может поддерживать только один одновременный клиент
 */
#include <WebSocketsServer.h>

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}