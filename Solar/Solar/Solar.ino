
#include <CustomStepper.h>
  CustomStepper stepper(8, 9, 10, 11);
  

  const int BOTTOMSensorPin = A3;                           // Подключение нижнего Фоторезистора
  const int UPSensorPin = A4;                               // Подключение верхнего Фоторезистора

  int UPSensorRead = 0;                                     // Считанные значения верхнего Фоторезистора
  int BOTTOMSensorRead = 0;                                 // Считанные значения нижнего Фоторезистора
  int UPLightPct = 0;                                       // Процент верхнего Фоторезистора
  int BOTTOMLightPct = 0;                                   // Процент нижнего Фоторезистора
  int degreeChange = 1;                                     // Изменение на 1 градус
  int degreesUP = 0;                                          // count steps so that the motor does not rotate ...
  int degreesDOWN = 0;                                        // ... endlessly in one direction

void setup() {
  Serial.begin(9600);
  stepper.setRPM(5);
  stepper.setSPR(4075.7728395);
}

void loop() {
  UPSensorRead = analogRead(UPSensorPin);                   // Считываем и сохраняем значение верхнего Фоторезистора
  BOTTOMSensorRead = analogRead(BOTTOMSensorPin);           // Считываем и сохраняем значение нижнего Фоторезистора
  UPLightPct = map(UPSensorRead, 0, 1023, 0, 100);          // Переводим значение верхнего Фоторезистора от 0-100
  BOTTOMLightPct = map(BOTTOMSensorRead, 0, 1023, 0, 100);  // Переводим значение нижнего Фоторезистора от 0-100
  degreeChange = map(abs(UPLightPct-BOTTOMLightPct),0,100,2,10);
  Serial.print("Верхний = ");                               // Выводим значение верхнего Фоторезистора
  Serial.print(UPSensorRead);
  Serial.print(" Нижний = ");                               // Выводим значение нижнего Фоторезистора
  Serial.print(BOTTOMSensorRead);
  Serial.print(" Соотношение Верх/Низ = ");
  Serial.print(UPLightPct);
  Serial.print("/");
  Serial.println(BOTTOMLightPct);
  if(UPLightPct > 150 && BOTTOMLightPct > 150){               
    Serial.println("Солнце не обнаружено!");
  }else if(UPLightPct == BOTTOMLightPct){
    Serial.println("Стоим, ждём 10 секунд");                 // В реальной жизни надо ставить минут 5
    delay(10000);
  }else if(UPLightPct > BOTTOMLightPct){
    Serial.println("Крутим вверх");
    if (degreesUP < 50) {
      rotateUP();
      stepper.run();
      degreesUP = degreesUP + degreeChange;
      degreesDOWN = max(0, degreesDOWN - degreeChange);
      Serial.print("Degrees up = ");
      Serial.println(degreesUP);
      Serial.print("Degrees down = ");
      Serial.println(degreesDOWN);
      }
    
  }
  else{
    Serial.println("Крутим вниз");
    if (degreesDOWN < 50)  {
      rotateBOTTOM();
      stepper.run();
      degreesUP = max(0, degreesUP - degreeChange);
      degreesDOWN = degreesDOWN + degreeChange;
      Serial.print("Degrees up = ");
      Serial.println(degreesUP);
      Serial.print("Degrees down = ");
      Serial.println(degreesDOWN);
      }
    
  }
  delay(1000);
}

void rotateBOTTOM(){
  stepper.setDirection(CCW);
  stepper.rotateDegrees(degreeChange);
  while(stepper.isDone() == false){
    stepper.run();
  }
}
void rotateUP(){
  stepper.setDirection(CW);
  stepper.rotateDegrees(degreeChange);
  while(stepper.isDone() == false){
    stepper.run();
  }
}
