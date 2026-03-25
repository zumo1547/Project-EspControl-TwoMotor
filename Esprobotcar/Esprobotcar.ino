/*#include <WiFi.h>
#include <WebServer.h>

// ===== PIN SETUP =====
#define IN1 27
#define IN2 26
#define IN3 25
#define IN4 33

#define TRIG 13
#define ECHO 12

#define BUZZER 32

// ===== WIFI AP =====
const char* ssid = "RobotCar";
const char* password = "12345678";

WebServer server(80);

// ===== HTML PAGE =====
String html_page = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
button{
  width:120px;height:60px;font-size:22px;margin:10px;
  border-radius:15px;
}
</style>
<script>
function send(cmd){
  fetch("/cmd?c=" + cmd);
}
</script>
</head>
<body style="text-align:center;background:#efefef;">
<h2>🤖 Robot WiFi Controller</h2>
<div>
  <button onclick="send('F')">Forward</button><br>
  <button onclick="send('L')">Left</button>
  <button onclick="send('S')">Stop</button>
  <button onclick="send('R')">Right</button><br>
  <button onclick="send('B')">Backward</button>
</div>
</body>
</html>
)=====";

// ===== MOTOR FUNCTIONS =====
void motorStop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void motorForward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void motorBackward(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  // Buzzer ตื๊ดๆ สำหรับ Active buzzer
  digitalWrite(BUZZER, HIGH);
  delay(150);
  digitalWrite(BUZZER, LOW);
  delay(120);
}

void motorLeft(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void motorRight(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ===== ULTRASONIC =====
long readDistance(){
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  return duration * 0.034 / 2;
}

// ===== COMMAND =====
void handle_cmd(){
  String c = server.arg("c");

  int dist = readDistance();
  if(dist < 15){
    motorStop();
    return;
  }

  if(c == "F") motorForward();
  else if(c == "B") motorBackward();
  else if(c == "L") motorLeft();
  else if(c == "R") motorRight();
  else if(c == "S") motorStop();

  server.send(200, "text/plain", "OK");
}

void handle_root(){
  server.send(200, "text/html", html_page);
}

// ===== SETUP =====
void setup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(BUZZER, OUTPUT);
  motorStop();

  WiFi.softAP(ssid, password);

  server.on("/", handle_root);
  server.on("/cmd", handle_cmd);
  server.begin();
}

// ===== LOOP =====
void loop(){
  server.handleClient();

  // เบรกฉุกเฉินอัตโนมัติ
  int dist = readDistance();
  if(dist < 15){
    motorStop();
  }
}
*/
