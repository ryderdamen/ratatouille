#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

#ifndef STASSID
#define STASSID "SampleSSID"
#define STAPSK  "SamplePassword"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
ESP8266WebServer server(80);
const int led = 13;

Servo front;
Servo rear;
Servo left;
Servo right;

int startingPosition = 32;

int frontPos = startingPosition;
int rearPos = startingPosition;
int leftPos = startingPosition;
int rightPos = startingPosition;


void pull(Servo servo, int pos, int startingPosition, int endingPosition, int writeDelay, int pullDelay) {
  for (pos = startingPosition; pos <= endingPosition; pos +=1) {
    servo.write(pos);
    delay(writeDelay);
  }
  delay(pullDelay);
  for (pos = endingPosition; pos >= startingPosition; pos -=1) {
    servo.write(pos);
    delay(writeDelay);
  }
}


void pullFront() {
  int startingPosition = 35;
  int endingPosition = 65;
  int writeDelay = 8;
  int pullDelay = 200;
  pull(front, frontPos, startingPosition, endingPosition, writeDelay, pullDelay);
  server.send(200, "text/plain", "front");
}


void pullRear() {
  int startingPosition = 35;
  int endingPosition = 65;
  int writeDelay = 8;
  int pullDelay = 200;
  pull(rear, rearPos, startingPosition, endingPosition, writeDelay, pullDelay);
  server.send(200, "text/plain", "rear");
}


void pullLeft() {
  int startingPosition = 35;
  int endingPosition = 65;
  int writeDelay = 8;
  int pullDelay = 200;
  pull(left, leftPos, startingPosition, endingPosition, writeDelay, pullDelay);
  server.send(200, "text/plain", "left");
}


void pullRight() {
  int startingPosition = 35;
  int endingPosition = 65;
  int writeDelay = 8;
  int pullDelay = 200;
  pull(right, rightPos, startingPosition, endingPosition, writeDelay, pullDelay);
  server.send(200, "text/plain", "right");
}


void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "home");
  digitalWrite(led, 0);
}


void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}


void setup(void) {
  pinMode(led, OUTPUT);
  front.attach(14);
  rear.attach(13);
  left.attach(12);
  right.attach(15);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/forwards", pullFront);
  server.on("/backwards", pullRear);
  server.on("/left", pullLeft);
  server.on("/right", pullRight);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}


void loop(void) {
  server.handleClient();
  MDNS.update();
}
