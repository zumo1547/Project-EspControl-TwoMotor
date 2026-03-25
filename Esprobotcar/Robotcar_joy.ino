#include <WiFi.h>
#include <WiFiUdp.h>

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

WiFiUDP udp;
unsigned int udpPort = 4210;  // port รับคำสั่ง

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

  digitalWrite(BUZZER, HIGH); delay(120);
  digitalWrite(BUZZER, LOW);
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

void setup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);

  motorStop();

  // เปิดเป็น WiFi Hotspot
  WiFi.softAP(ssid, password);
  udp.begin(udpPort);

  Serial.begin(115200);
  Serial.println("RobotCar Ready!");
}

void loop(){
  int packetSize = udp.parsePacket();
  if (packetSize){
    char cmd = udp.read();

    int dist = readDistance();
    if(dist < 15){
      motorStop();
      return;
    }

    if(cmd == 'F') motorForward();
    else if(cmd == 'B') motorBackward();
    else if(cmd == 'L') motorLeft();
    else if(cmd == 'R') motorRight();
    else if(cmd == 'S') motorStop();
  }

  int dist = readDistance();
  if(dist < 15) motorStop();
}
