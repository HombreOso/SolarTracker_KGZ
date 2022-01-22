#include <CustomStepper.h>              // Подключаем библиотеку CustomStepper

  CustomStepper stepper(8, 9, 10, 11);  // Указываем пины, к которым подключен драйвер шагового двигателя
  boolean rotate1 = false;              // Переменная для смены режимов
  boolean rotatedeg = false;            // Переменная для смены режимов
  boolean crotate = false;              // Переменная для смены режимов 

void setup()
{
  stepper.setRPM(15);                 // Устанавливаем количество оборотов в минуту
  stepper.setSPR(4075.7728395);       // Устанавливаем количество шагов на полный оборот. Максимальное значение 4075.7728395
}

void loop()
{
//когда команда будет завершена, isDone вернет true,
  if (stepper.isDone() &&  rotate1 == false){
    stepper.setDirection(CCW);        // Устанавливает направление вращения (по против часовой)
    stepper.rotate(2);                // Устанавливает вращение на заданное количество оборотов
    rotate1 = true;
  }
  if (stepper.isDone() && rotate1 == true && rotatedeg == false){
    stepper.setRPM(5);               // Устанавливаем количество оборотов в минуту
    stepper.setDirection(CW);         // Устанавливает направление вращения (по часовой)
    stepper.rotateDegrees(360);       //вращение на заданное количество градусов,можно и такие как 90,5
    rotatedeg = true;
  }
  if (stepper.isDone() && rotatedeg == true && crotate == false){
    stepper.setRPM(15);               // Устанавливаем количество оборотов в минуту
    stepper.setDirection(CCW);
    stepper.rotate();                 //это будет вращаться до тех пор, пока не остановите его другой командой
    crotate = true;
  }
  stepper.run();                        // команда запуска двигателя
}
