#ifndef MOTOR_APPS
#define MOTOR_APPS

/* To test motors use the following API's:
 * void moveForward (int pwmLvl);
 * void moveBackward (int pwmLvl);
 * void turnCenterRight (int pwmLvl);
 * void turnCenterLeft (int pwmLvl);
 * void motorStop (void);
 * Where pwmLvl is a value between 0 to 255 
 */

void motorInit (void){
    int i;
    for(i=5;i<=8;i++)
        pinMode(i, OUTPUT);
}

void rightMotorForward (int pwmLvl){
    analogWrite (5, pwmLvl);
    digitalWrite(7, LOW);
}

void leftMotorForward (int pwmLvl){
    analogWrite (6, pwmLvl);
    digitalWrite(8, LOW);
}

void rightMotorBackward (int pwmLvl){
    analogWrite (5, pwmLvl);
    digitalWrite(7, HIGH);
}

void leftMotorBackward (int pwmLvl){
    analogWrite (6, pwmLvl);
    digitalWrite(8, HIGH);
}

void rightMotorStop (void){
    analogWrite (5, 0);
    digitalWrite(7, LOW); //redundant
}

void leftMotorStop (){
    analogWrite (6, 0);
    digitalWrite(8, LOW); //redundant
}

void moveForward (int pwmLvl){
    rightMotorForward(pwmLvl);
    leftMotorForward(pwmLvl);
}

void moveBackward (int pwmLvl){
    rightMotorBackward(pwmLvl);
    leftMotorBackward(pwmLvl);
}

void motorStop (void){
    rightMotorStop();
    leftMotorStop();
}

void turnCenterRight (int pwmLvl){
    rightMotorBackward(pwmLvl);
    leftMotorForward(pwmLvl);
}

void turnCenterLeft (int pwmLvl){
    leftMotorBackward(pwmLvl);
    rightMotorForward(pwmLvl);
}

#endif
