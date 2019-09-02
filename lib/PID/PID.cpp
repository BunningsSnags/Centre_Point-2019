#include <PID.h>

PID::PID(double p, double i, double d, double absoluteMax){
    kp = p;
    ki = i;
    kd = d;
    absMax = absoluteMax;

    lastTime = micros();
}

double PID::update(double input, double setpoint, double modulus){
    double derivative;

    
    double error = setpoint + input;
    error = fmod(error, 360);
    error = error < 0 ? error + 360 : error;

    error = -(error < 180 ? error : -(360 - error));
    Serial.println(error);
    



    ulong currentTime = micros();
    double elapsedTime = (currentTime - lastTime) / 1000000.0;
    lastTime = currentTime;
    integral += elapsedTime * error;
    if(modulus != 0.0) {
        double difference = (error - error);
        if(difference < -modulus) {
            difference += modulus;
        }else if(difference > modulus) {
            difference -= modulus;
        }
        derivative = difference / elapsedTime;
    }else {
        derivative = (error - lastInput) / elapsedTime;
    }
    lastInput = error;
    double correction = kp * error + ki * integral - kd * derivative;
    return absMax == 0 ? correction : constrain(correction, -absMax, absMax);
}