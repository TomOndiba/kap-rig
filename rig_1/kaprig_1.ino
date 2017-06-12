
#include <Servo.h> 
 
Servo panServo;
Servo tiltServo;

#define PIN_PAN 2
#define PIN_TILT 3

#define PAUSE_FOR_PHOTO 3000

#define HALT_PAN 80
#define STEP_PAN 180
#define DURATION_PAN 2000

#define STEP_TILT 20
#define START_TILT 90
#define MIN_TILT START_TILT - 60
#define MAX_TILT START_TILT + 60

int currentTilt = START_TILT;
 
void setup()
{
    // Setup and halt the motors. Bring the tilt motor to zero postion and wait 
    // to be able to adjust the tilt.
    panServo.attach(PIN_PAN);
    tiltServo.attach(PIN_TILT);
    panServo.write(HALT_PAN);
    tiltServo.write(START_TILT);
    delay(10000);
}

void pan() {
    // panning is simple. The motor is modified for continous rotaton
    panServo.write(STEP_PAN);
    delay(DURATION_PAN);
    panServo.write(HALT_PAN);
}

void tiltStep(int pos) {
    int step = 0;
    if (pos < currentTilt) {
        step = -1;
    }
    else {
        step = 1;
    }
  
    while (currentTilt != pos) {
        currentTilt += step;
        tiltServo.write(currentTilt);
        delay(15);
    } 
}

void tiltUp() {
    int i = currentTilt;
    for (; i <= MAX_TILT; i += STEP_TILT) {
        tiltStep(i);
        delay(PAUSE_FOR_PHOTO);
    }
}

void tiltDown() {
    int i = currentTilt;
    for (; i >= MIN_TILT; i -= STEP_TILT) {
        tiltStep(i);
        delay(PAUSE_FOR_PHOTO);
    }
}
 
void loop() 
{
    if (currentTilt >= MAX_TILT) {
        tiltDown();
    }
    else {
        tiltUp();
    }
    pan();
}


