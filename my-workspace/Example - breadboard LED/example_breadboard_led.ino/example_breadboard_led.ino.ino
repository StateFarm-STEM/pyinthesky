int redLED=8;
int blueLED=4;
int greenLED=6;
int rlond=50;
int rloffd=50;
int glond=50;
int gloffd=50;
int blond=100;
int bloffd=100;


void setup() {
  // put your setup code here, to run once:
  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(blueLED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(redLED,HIGH);
  delay(rlond);
  digitalWrite(redLED,LOW);
  delay(rloffd);
  digitalWrite(redLED,HIGH);
  delay(rlond);
  digitalWrite(redLED,LOW);
  delay(rloffd);
  digitalWrite(redLED,HIGH);
  delay(rlond);
  digitalWrite(redLED,LOW);
  delay(rloffd);

  digitalWrite(greenLED,HIGH);
  delay(glond);
  digitalWrite(greenLED,LOW);
  delay(gloffd);
  digitalWrite(greenLED,HIGH);
  delay(glond);
  digitalWrite(greenLED,LOW);
  delay(gloffd);
  digitalWrite(greenLED,HIGH);
  delay(glond);
  digitalWrite(greenLED,LOW);
  delay(gloffd);

  digitalWrite(blueLED,HIGH);
  delay(blond);
  digitalWrite(blueLED,LOW);
  delay(bloffd);
  digitalWrite(blueLED,HIGH);
  delay(blond);
  digitalWrite(blueLED,LOW);
  delay(bloffd);
  digitalWrite(blueLED,HIGH);
  delay(blond);
  digitalWrite(blueLED,LOW);
  delay(bloffd);
}
