/* Including library */
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
WiFiClient client;

/* Defining WiFi Credentials */
const char* ssid = "Wifi"; /* Your SSID */
const char* password = "12345678"; /* Your Password */

String  direction = "";
int speed = 400; /* 400 to 1023 */

/* Thingspeak channel details */
unsigned long channelId = 1203972;
unsigned int field1 = 1;
unsigned int field2 = 2;
const char * readKey = "R8DF3NSJPS26J1PU";

/* Defining right and left motor pins */
int RMotor_1 = 0;/* Right Motor GPIO0(D3) */
int RMotor_2 = 2;/* Right Motor GPIO2(D4) */
int LMotor_1 = 13;/* Left Motor GPIO13(D7) */
int LMotor_2 = 15;/* Left Motor GPIO15(D8) */

/* Defining L298N enable pins */
int REnable = 14;/* Right Motor Enable Pin GPIO14(D5) */
int LEnable = 12;/* Right Motor Enable Pin GPIO12(D6)  */

void setup() {
  Serial.begin(115200);
  Serial.println("GPIO test!");

  ThingSpeak.begin(client);

  /* Initialize Motor Control Pins as Output */
  pinMode(RMotor_1, OUTPUT);
  pinMode(RMotor_2, OUTPUT);
  pinMode(LMotor_1, OUTPUT);
  pinMode(LMotor_2, OUTPUT);
  /* Initialize Motor Enable Pins as Output */
  pinMode(REnable, OUTPUT);
  pinMode(LEnable, OUTPUT);

  /* Connectinf to WiFi */
  connectingToWiFi();

}
void loop() {
  analogWrite(REnable, speed);
  analogWrite(LEnable, speed);

  direction = ThingSpeak.readStringField(channelId, field1, readKey);   /* Getting field 1 value (direction) from Thingspeak */
  speed = ThingSpeak.readIntField(channelId, field2, readKey);   /* Getting field 2 value (speed) from Thingspeak */

  if (direction == "F") {
    move_forward(); /* If direction F moves Forward */
  }
  else if (direction == "B") {
    move_backward(); /* If direction B moves Backward */
  }
  else if (direction == "R") {
    turn_right(); /* If direction R moves Turn Right */
  }
  else if (direction == "L") {
    turn_left(); /* If direction L moves Turn Left */
  }
  else if (direction == "S") {
    move_stop(); /* If direction S moves Stop Moving */
  }
  direction = "";
  //speed = "";
}

void connectingToWiFi() {
  delay(3000);
  WiFi.disconnect();
  delay(1000);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.println("Local IP is : ");
  Serial.print((WiFi.localIP().toString()));
  delay(5000);
}

/* Move Forward */
void move_forward() {
  digitalWrite(RMotor_1, LOW);
  digitalWrite(RMotor_2, HIGH);
  digitalWrite(LMotor_1, LOW);
  digitalWrite(LMotor_2, HIGH);
  delay(2000);
  move_stop();
}

/* Move Backward */
void move_backward() {
  digitalWrite(RMotor_1, HIGH);
  digitalWrite(RMotor_2, LOW);
  digitalWrite(LMotor_1, HIGH);
  digitalWrite(LMotor_2, LOW);
  delay(2000);
  move_stop();
}

/* Turn Right */
void turn_right() {
  digitalWrite(RMotor_1, LOW);
  digitalWrite(RMotor_2, HIGH);
  digitalWrite(LMotor_1, HIGH);
  digitalWrite(LMotor_2, LOW);
  delay(2000);
  move_stop();
}

/* Turn Left */
void turn_left() {
  digitalWrite(RMotor_1, HIGH);
  digitalWrite(RMotor_2, LOW);
  digitalWrite(LMotor_1, LOW);
  digitalWrite(LMotor_2, HIGH);
  delay(2000);
  move_stop();
}

/* Stop Move */
void move_stop() {
  digitalWrite(RMotor_1, LOW);
  digitalWrite(RMotor_2, LOW);
  digitalWrite(LMotor_1, LOW);
  digitalWrite(LMotor_2, LOW);
}
