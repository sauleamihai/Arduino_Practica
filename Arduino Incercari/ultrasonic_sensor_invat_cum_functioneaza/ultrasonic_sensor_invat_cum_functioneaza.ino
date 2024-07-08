long distance;
long duration;

const int trigPin = 10;
const int echoPin = 11;
const int ledPin = 13;
const int ledPinGreen = 12; 
byte prevStateLedGreen = HIGH;
byte prevStateLedRed = LOW;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  
  Serial.begin(115200);
  
  digitalWrite(ledPinGreen, HIGH);
  digitalWrite(ledPin, LOW);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  
  distance = duration * 0.034 / 2; 

 
  Serial.print("Distance: ");
  Serial.println(distance);
  

  if (distance < 10) {
    digitalWrite(ledPinGreen, LOW);
    digitalWrite(ledPin, HIGH); 
  } else {
    digitalWrite(ledPinGreen, HIGH);
    digitalWrite(ledPin, LOW);
  }
  
  delay(1000); 
}
