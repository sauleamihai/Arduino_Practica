#define CW 0
#define CCW 1

#define motorDirPin 7
#define motorPWMPin 9
#define enablePin 8

#define encoderPinA 2
#define encoderPinB 4

int encoderPos = 0;

float Kp  = 1.0;
int targetPos = 100;
int error;
int control;
int velocity;

void doEncoderA() {
  if (digitalRead(encoderPinB)) {
    encoderPos--;
  } else {
    encoderPos++;
  }
}

void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), doEncoderA, RISING);
  pinMode(motorDirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);
  Serial.begin(9600);
}

void loop() { 
  error = targetPos - encoderPos;
  control = Kp * error;
  velocity = constrain(control, -255, 255);

  if (velocity >= 0) {
    digitalWrite(motorDirPin, CW);
    analogWrite(motorPWMPin, velocity);
  } else {
    digitalWrite(motorDirPin, CCW);
    analogWrite(motorPWMPin, -velocity);
  }

  Serial.println(encoderPos);
}
