/*
 Sample Line Following Code for the Robojunkies LF-2 robot
*/

#define speedL 10
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define speedR 5 

int P, D, I, previousError, PIDvalue, error;
int lsp, rsp;
int lfspeed = 60;

float Kp = 0;
float Kd = 0;
float Ki = 0;

void setup()
{
  Serial.begin(9600);
  DDRC &= ~(0x1F);
  pinMode(speedL, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(speedR, OUTPUT);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

}


void loop()
{
  int x = analogRead(16);
  Kp = 0.07;
  Ki = 0.07;
  Kd = 0;
  //Kp = 0.0006 * (1000 - x);
  //Kd = 10 * Kp;
  //Ki = 10 * Kp;
  // Serial.print("Mid sensor = ");
  // Serial.println(x);
  // Serial.print("Kp = ");
  // Serial.println(Kp);
  // Serial.print("Kd = ");
  // Serial.println(Kd);
  // Serial.print("Ki = ");
  // Serial.println(Ki);
  //Ki = 0.0001;
  linefollow();
  delay(50);
}

void linefollow()
{
  int error = (analogRead(17) - analogRead(15));
  Serial.print("Error = ");
  Serial.println(error);

  P = error;
  I = I + error;
  D = error - previousError;

  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
  // Serial.print("P = ");
  // Serial.println(P);
  // Serial.print("I = ");
  // Serial.println(I);
  // Serial.print("D = ");
  // Serial.println(D);
  // Serial.print("PID = ");
  // Serial.println(PIDvalue);
  previousError = error;

  lsp = lfspeed - PIDvalue;
  rsp = lfspeed + PIDvalue;

  if (lsp > 120) {
    lsp = 120;
  }
  if (lsp < 0) {
    lsp = 0;
  }
  if (rsp > 120) {
    rsp = 120;
  }
  if (rsp < 0) {
    rsp = 0;
  }
  analogWrite(speedL, lsp);
  analogWrite(speedR, rsp);
}

// void calibrate()
// {
//   for ( int i = 1; i < 6; i++)
//   {
//     minValues[i] = analogRead(i);
//     maxValues[i] = analogRead(i);
//   }
  
//   for (int i = 0; i < 3000; i++)
//   {
//     motor1.drive(50);
//     motor2.drive(-50);

//     for ( int i = 1; i < 6; i++)
//     {
//       if (analogRead(i) < minValues[i])
//       {
//         minValues[i] = analogRead(i);
//       }
//       if (analogRead(i) > maxValues[i])
//       {
//         maxValues[i] = analogRead(i);
//       }
//     }
//   }

//   for ( int i = 1; i < 6; i++)
//   {
//     threshold[i] = (minValues[i] + maxValues[i]) / 2;
//     Serial.print(threshold[i]);
//     Serial.print("   ");
//   }
//   Serial.println();
  
//   motor1.drive(0);
//   motor2.drive(0);
// }