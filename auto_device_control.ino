#include <Servo.h>

String str;
Servo myservo;

void setup()
{
  Serial.begin(9600);
  myservo.attach(9); //using pin9 for servo PWM control pin
}

void loop()
{
  if (Serial.available()) {
    str = Serial.readStringUntil('\n');

    if (str == "right") {
      Serial.println("turn right");
      turn_right();
    } else if (str == "left") {
      Serial.println("turn left");
      turn_left();
    } else if (str == "get") {
      Serial.println(myservo.read());
    }  
  }
}

void turn_right()
{
    for (int i = 0; i <= 180; i += 1) {
      myservo.write(i); // 使用write，傳入角度，從0度轉到180度
      delay(20);
    }
}

void turn_left()
{
    for (int i = 180; i >= 0; i -= 1) {
      myservo.write(i); // 使用write，傳入角度，從0度轉到180度
      delay(20);
    }
}

//Servo預設的脈衝寬度範圍是544到2400µs，跟SG90的500到2400差了一點,以下是改用脈衝寬度精準控制範例
/*
  #include <Servo.h>

  Servo myservo;

  void setup()
  {


  myservo.attach(9, 500, 2400); // 修正脈衝寬度範圍
  myservo.write(90); // 一開始先置中90度
  delay(3000);
  }

  void loop()
  {
  for(int i = 500; i <= 2400; i+=100){
    myservo.writeMicroseconds(i); // 直接以脈衝寬度控制

    delay(300);
  }
  for(int i = 2400; i >= 500; i-=100){
    myservo.writeMicroseconds(i);

    delay(300);
  }
  }
*/
