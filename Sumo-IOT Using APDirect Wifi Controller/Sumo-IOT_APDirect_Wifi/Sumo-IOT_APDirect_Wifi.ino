
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "SUMO-IOT";
const char *password = "SUMO-IOT";

IPAddress ip(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);
const int port = 8080; // Port
ESP8266WebServer server(port);

static const uint8_t pwm_A = 5 ;
static const uint8_t pwm_B = 4;
static const uint8_t dir_A = 0;
static const uint8_t dir_B = 2;

// Motor speed = [0-1024]
int motor_speed = 1024;

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(ssid, password);

  pinMode(pwm_A, OUTPUT); // PMW A
  pinMode(pwm_B, OUTPUT); // PMW B
  pinMode(dir_A, OUTPUT); // DIR A
  pinMode(dir_B, OUTPUT); // DIR B

  server.on("/move", HTTP_GET, handleMoveRequest);
  server.on("/action", HTTP_GET, handleActionRequest);
  server.onNotFound(handleNotFound);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleMoveRequest() {
  if (!server.hasArg("dir")) {
    server.send(404, "text / plain", "Move: undefined");
    return;
  }
  String direction = server.arg("dir");
  if (direction.equals("F")) {
    forward();
    server.send(200, "text / plain", "Move: forward");
  }
  else if (direction.equals("B")) {
    backward();
    server.send(200, "text / plain", "Move: backward");
  }
  else  if (direction.equals("S")) {
    stop_motors();
    server.send(200, "text / plain", "Move: stop");
  }
  else  if (direction.equals("L")) {
    turn_left();
    server.send(200, "text / plain", "Turn: Left");
  }
  else  if (direction.equals("R")) {
    turn_right();
    server.send(200, "text / plain", "Turn: Right");
  }
  else {
    server.send(404, "text / plain", "Move: undefined");
  }
}


void handleActionRequest() {
  if (!server.hasArg("type")) {
    server.send(404, "text / plain", "Action: undefined");
    return;
  }
  String type = server.arg("type");
  if (type.equals("1")) {
    // TODO : Action 1
    server.send(200, "text / plain", "Action 1");
  }
  else if (type.equals("2")) {
    // TODO : Action 2
    server.send(200, "text / plain", "Action 2");
  }
  else if (type.equals("3")) {
    // TODO : Action 3
    server.send(200, "text / plain", "Action 3");
  }
  else if (type.equals("4")) {
    // TODO : Action 4
    server.send(200, "text / plain", "Action 4");
  }
  else if (type.equals("5")) {
    // TODO : Action 5
    server.send(200, "text / plain", "Action 5");
  }
  else if (type.equals("6")) {
    // TODO : Action 6
    server.send(200, "text / plain", "Action 6");
  }
  else if (type.equals("7")) {
    // TODO : Action 7
    server.send(200, "text / plain", "Action 7");
  }
  else if (type.equals("8")) {
    // TODO : Action 8
    server.send(200, "text / plain", "Action 8");
  }
  else {
    server.send(404, "text / plain", "Action: undefined");
  }
}

void handleNotFound() {
  server.send(404, "text / plain", "404: Not found");
}


void stop_motors() {
  analogWrite(pwm_A, 0);
  analogWrite(pwm_B, 0);
}

void backward() {
  analogWrite(pwm_A, motor_speed);
  analogWrite(pwm_B, motor_speed);
  digitalWrite(dir_A, LOW);
  digitalWrite(dir_B, HIGH);
}

void forward() {
  analogWrite(pwm_A, motor_speed);
  analogWrite(pwm_B, motor_speed);
  digitalWrite(dir_A, HIGH);
  digitalWrite(dir_B, LOW);
}

void turn_left() {
  analogWrite(pwm_A, motor_speed);
  analogWrite(pwm_B, motor_speed);
  digitalWrite(dir_A, HIGH);
  digitalWrite(dir_B, HIGH);
}

void turn_right() {
  analogWrite(pwm_A, motor_speed);
  analogWrite(pwm_B, motor_speed);
  digitalWrite(dir_A, LOW);
  digitalWrite(dir_B, LOW);
}
