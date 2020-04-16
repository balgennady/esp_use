#include <Arduino.h>

String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

String html_1 = R"=====(
	<!DOCTYPE html>
	<html>
	<head>
	<meta name='viewport' content='width=device-width, initial-scale=1.0'/>
	<meta charset='utf-8'>
	<style>
		body    { font-size:120%;} 
		#main   { display: table; width: 300px; margin: auto;  padding: 10px 10px 10px 10px; border: 3px solid blue; border-radius: 10px; text-align:center;} 
		.button { width:200px; height:40px; font-size: 110%;  }
	</style>
	<title>Websockets</title>
	</head>
	<body>
	<div id='main'>
		<h3>LED CONTROL</h3>
		<div id='content'>
		<p id='LED_status'>LED is off</p>
		<button id='BTN_LED'class="button">Turn on the LED</button>
		</div>
		<br />
	</div>
	</body>
	
	<script>
	var Socket;
	function init() 
	{
		Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
	}
	
	document.getElementById('BTN_LED').addEventListener('click', buttonClicked);
	function buttonClicked()
	{   
		var btn = document.getElementById('BTN_LED')
		var btnText = btn.textContent || btn.innerText;
		if (btnText ==='Turn on the LED') { btn.innerHTML = "Turn off the LED"; document.getElementById('LED_status').innerHTML = 'LED is on';  sendText('1'); }  
		else                              { btn.innerHTML = "Turn on the LED";  document.getElementById('LED_status').innerHTML = 'LED is off'; sendText('0'); }
	}
	
	function sendText(data)
	{
		Socket.send(data);
	}
	
	window.onload = function(e)
	{ 
		init();
	}
	</script>
	</html>
	)=====";

#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

WiFiServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

// byte pin_led = D2;
byte pin_led = BUILTIN_LED;

char ssid[] = "Tenda_99";
char pass[] = "0984881148";

void setup() {

	pinMode(pin_led, OUTPUT);
	digitalWrite(pin_led, LOW);

	Serial.begin(115200);
	Serial.println();
	Serial.println("Serial started at 115200");
	Serial.println();

	// Подключиться к сети WiFi
	Serial.print(F("Присоединение к сети"));
	Serial.println(ssid);
	WiFi.begin(ssid, pass);

	// связь с таймаутом
	int count = 0;
	while ((WiFi.status() != WL_CONNECTED) && count < 17) {
		Serial.print(".");
		delay(500);
		count++; 
	}

	if (WiFi.status() != WL_CONNECTED) {
		Serial.println("");
		Serial.print("Не удалось подключиться к ");
		Serial.println(ssid);
		while (1)
			;
	}

	Serial.println("");
	Serial.println(F("[CONNECTED]"));
	Serial.print("[IP ");
	Serial.print(WiFi.localIP());
	Serial.println("]");

	// запустить сервер
	server.begin();
	Serial.println("Сервер запущен");

	webSocket.begin();
	webSocket.onEvent(webSocketEvent);
}

void loop() {

	webSocket.loop();

	WiFiClient client = server.available();

	// Проверьте, подключен ли клиент
	if (!client) {
		return;
	}

	client.flush();
	client.print(header);
	client.print(html_1);
	Serial.println("Новая страница обслуживается");

	delay(5);
}

void webSocketEvent(byte num, WStype_t type, uint8_t *payload, size_t length) {

	if (type == WStype_TEXT) {
		if (payload[0] == '0') {
			digitalWrite(pin_led, LOW);
			Serial.println("LED=off");
		}
		else if (payload[0] == '1') {
			digitalWrite(pin_led, HIGH);
			Serial.println("LED=on");
		}
	}

	else {
		Serial.print("WStype = ");
		Serial.println(type);
		Serial.print("WS payload = ");
		for (int i = 0; i < length; i++) {
			Serial.print((char)payload[i]);
		}
		Serial.println();
	}
}