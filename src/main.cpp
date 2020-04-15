/**
 * Устройство с ESP8266, отправка данных в реальном времени
 * https://esp8266.ru/forum/threads/ustrojstvo-s-esp8266-otpravka-dannyx-v-realnom-vremeni.4874/post-71451
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
/**
 *  клиент, который может соединяться с указанным IP-адресом через определенный порт 
 * */
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
/**
 * веб-сервер, который знает, как обрабатывать HTTP-запросы, такие как GET и POST, 
 * и может поддерживать только один одновременный клиент
 */
#include <WebSocketsServer.h>

// глобальные переменные
String ssid = "Tenda_99";
String password = "0984881136";

IPAddress ip(192, 168, 0, 157);

ESP8266WebServer server(80);
WebSocketsServer socket = WebSocketsServer(81);

void setup() {
	
	WiFi.begin(ssid, password);

	Serial.begin(115200);
	delay(100);

	// ожидание подключения
	while(WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	// вывод информации о подключении к WiFi
	Serial.println("");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	server.begin(); // старт сервера
	socket.begin(); // старт сокета

	delay(200);
}

void loop() {

	server.handleClient();
	delay(1);
	socket.loop();
	socket.broadcastTXT("hello");
	delay(1000);
}