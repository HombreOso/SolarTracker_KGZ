
const int BOTTOMSensorPin = A2; // нижний
const int UPSensorPin = A5; // верхний


void setup() {
  Serial.begin(9600);
}

void loop() {
  int BOTTOM_val = analogRead(BOTTOMSensorPin);
  int UP_val = analogRead(UPSensorPin);

  Serial.print("Нижний  = ");
  Serial.print(BOTTOM_val);
  Serial.print("\tВерхний = ");
  Serial.println(UP_val);
  delay(200);
}
