#include <CustomStepper.h>              // Подключаем библиотеку CustomStepper

  CustomStepper stepper(8, 9, 10, 11);  // Указываем пины, к которым подключен драйвер шагового двигателя
  boolean rotate1 = false;              // Переменная для смены режимов
  boolean rotatedeg = false;            // Переменная для смены режимов
  boolean crotate = false;              // Переменная для смены режимов 

void setup()
{
  stepper.setRPM(5);                   // Устанавливаем количество оборотов в минуту
  stepper.setSPR(4075.7728395);         // Устанавливаем количество шагов на полный оборот. Максимальное значение 4075.7728395
}

void loop()
{
//когда команда будет завершена, isDone вернет true,
  if (stepper.isDone() && rotatedeg == false && crotate == false){
    stepper.setDirection(CW);           // Устанавливает направление вращения (по часовой)
    stepper.rotateDegrees(60);          // 60 градусов вперёд
    rotatedeg = true;
  }
  if (stepper.isDone() && rotatedeg == true){
    stepper.setDirection(CCW);          // Устанавливает направление вращения (против часовой)
    stepper.rotateDegrees(90);          // 45 градусов назад + ещё 45 градусов
    rotatedeg = false;
    crotate = true;
  }
  if (stepper.isDone() && rotatedeg == false && crotate == true){
    stepper.setDirection(CW);           // Устанавливает направление вращения (по часовой)
    stepper.rotateDegrees(90);          // 90 градусов вперёд
    rotatedeg = true;
  }    
  stepper.run();                        // команда запуска двигателя
}
