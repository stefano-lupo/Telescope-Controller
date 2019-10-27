#include ".\headers\Remote.h"
#include ".\headers\MotorController.h"
#include ".\headers\CameraController.h"
#include ".\headers\Screen.h"
#include ".\headers\Coordinate.h"
#include ".\headers\Navigator.h"
#include ".\headers\Tracker.h"
#include ".\headers\MotorStepConfig.h"

// Stepper pins
const int DIR_PIN = 2;
const int STEP_PIN = 3;
const int SLEEP_PIN = 4;
const int MS3 = 6;
const int MS2 = 7;
const int MS1 = 8;

// IR Pins
const int REMOTE_PIN = 11;
const int IR_LED_PIN = 10;

// Screen Pins
const int SDA_PIN = A4;
const int SCL_PIN = A5;

// Timer constants
const float MILLISECONDS_PER_SECOND = 1000;
const uint16_t PRESCALER = 256;
const uint16_t EFFECTIVE_CLOCK_RATE = 16000000 / PRESCALER;
const uint16_t INTERRUPT_PERIOD_MS = 50;
const uint16_t T1_LOAD_VALUE = 0;
const uint16_t T1_COMPARE_VALUE = EFFECTIVE_CLOCK_RATE * (INTERRUPT_PERIOD_MS / MILLISECONDS_PER_SECOND);

// Instantiation
Remote remote(REMOTE_PIN);
MotorController motorController(DIR_PIN, STEP_PIN, SLEEP_PIN, MS1, MS2, MS3);
CameraController cameraController(IR_LED_PIN, INTERRUPT_PERIOD_MS);

Tracker tracker(INTERRUPT_PERIOD_MS);
Navigator navigator(motorController, tracker);
Screen screen(navigator, cameraController);


void setup() {
  Serial.begin(9600);
  Serial.println("Starting telescope controller");

  configureTimers();

  screen.setup();
  remote.setup();
  motorController.setup();
  // navigator.setup();
  // cameraController.setup();

  // cameraController.setShutterTime(5000L);
  // cameraController.enableCapturing();
  // navigator.setCurrentCoord(Coordinate(0, 0, 0));
  // navigator.setTargetCoord(Coordinate(5, 30, 30));
  navigator.trackTarget();
}

void printCoord(Coordinate c) {
  char str[16];
  c.formatString(str);
  Serial.println(str);
}

// Configure 16bit timer1 to count in milliseconds (@ 1KHz)
void configureTimers() {
  // Default timer clock is 16MHz, but can be adjusted by a prescaler
  // Prescaler selection isn't continuous, its only 1, 8, 64, 256 or 1024
  // These are configured by CSx2, CSx1, CSx0 (where x is timer index)
  // Prescaler encodings: [0 _ 1] --> 1, [0 1 0] --> 8, [0 1 1] --> 64, [1 0 0] --> 256, [1 0 1] --> 1024
  // Effective clock rate is 16MHz / PS

  // Timer 1 is 16 bit (0 - 65,535), Timer 0 and 2 are only 8 bit (0 - 255)

  // RA fine adjustment knob requires 144 rotations for every RA rotation
  // So we want to do 144 rotations in 24 hours
  // 144 rotations / 24 = 6 rotations per hour = 0.1 rotations per minute
  // Equivalently, 1 rotation every 10 minutes.
  
  // The stepper motor has a default resolution of 200 steps, so 200 steps every 10 minutes (600s)
  // So 1 step every 3 seconds
  // Stepping      Frequency (Steps / sec)   Period (Delay in MS)
  // ------------------------------------------------------------
  //    1/1        |       1/3          |         3000
  //    1/2        |       2/3          |         1500
  //    1/4        |       4/3          |         750
  //    1/8        |       8/3          |         375
  //    1/16       |       16/3         |         187.5
  
  // Going with quarter stepping 

  // I want an interupt every 750ms (3/4s)
  // With a prescaler of 256 --> Effective clock rate is 16 MHz / 256 = 62, 500 counts per second (Hz)
  // Therefore would count to 62,500 * 0.75 = 46,875 in 0.75 seconds

  // Three types of interupts:
  // 1) Input Capture: Stores timer's count when a certain pin goes through a predefined state change (e.g. count of T1 when D1 went high)
  // 2) Overflow: Generates an interupt when timer overflows 
  // 3) Output Compare: We write a target value into a register and generates an interupt when the timer reaches that number

  // Alternative method, generating an interupt every 100ms
  // Count is: 62,500 * 0.1 = 6,250

  // Coordinates Calculations for RA
  // 144 RA knob rotations = 24 hours = 1440 minutes (full rotation)
  // 1 RA knob rotation = 10 minutes
  // Stepping          Num steps          Minutes per step
  // ------------------------------------------------------------
  //    1/1        |       200          |         10 / 200 = 0.05 = 3s
  //    1/2        |       400          |         10 / 400 = 0.025 = 1.5s
  //    1/4        |       800          |         10 / 800 = 0.0125 = 0.75s
  //    1/8        |       1600         |         10 / 1600 = 0.00625 = 0.375s
  //    1/16       |       3200         |         10 / 3200 = 0.003125 = 0.1875s
  
  cli();          // Stop interupts
  TCCR1A = 0;     // Reset timer 1's control registers
//  TCCR1B = 0;     // Reset timer 1's control registers (not sure if this is needed?)
  
  // Setup prescaler of 256
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);

  // Reset timer1 value to 0
  TCNT1 = T1_LOAD_VALUE;
  OCR1A = T1_COMPARE_VALUE;

  // Set Output Compare Interupt Enable for timer 1
  TIMSK1 = (1 << OCIE1A);

  // Enable global interupts
  sei();
}

void cycleRotate() {
  long distance = 1500;
  // motorController.setFullStep();
 
  // motorController.enableMotor();
  motorController.setDirection(MotorController::RA);
  motorController.stepMotor(distance);
  // motorController.disableMotor();
  delay(1000);

  // motorController.enableMotor();
  motorController.setDirection(MotorController::ANTI_RA);
  motorController.stepMotor(distance);
  // motorController.disableMotor();
  delay(1000);
}

void cycleRotateAllSizes() {
  motorController.setStepSize(MotorStepConfigs::FULL_STEP);
  cycleRotate();
  delay(5000);

  motorController.setStepSize(MotorStepConfigs::HALF_STEP);
  cycleRotate();
  delay(5000);

  motorController.setStepSize(MotorStepConfigs::QUARTER_STEP);
  cycleRotate();
  delay(5000);
}


void pollRemote() {
 Event event = remote.checkForPress();
  switch (event) {
    case Event::STOP_TRACKING:
    case Event::STOP_SLEWING:
      navigator.disableNavigation();
      break;
    
    case Event::START_TRACKING:
      navigator.trackTarget();
      break;
    case Event::START_SLEWING:
      navigator.slewToTarget();
      break;
  
    case Event::INCREASE_EXPOSURE_TIME:
      // cameraController.increaseShutterTime();
      break;
    case Event::DECREASE_EXPOSURE_TIME:
      // cameraController.decreaseShutterTime();
      break;
    case Event::START_CAPTURING:
      // cameraController.enableCapturing();
      break;
    case Event::STOP_CAPTURING:
      // cameraController.disableCapturing();
      break;

    case Event::TOGGLE_BOTTOM_ROW:
      screen.toggleBottomRow();
      break;
    case Event::TOGGLE_TOP_ROW:
      // screen.toggleTopRow();
      navigator.nextTrackingConfig();
      break;

    // case Event::MOTOR_TEST:
    //   cycleRotate();
    //   break;

    case Event::BUTTON_HELD:
      break;
    case Event::UNKNOWN:
      break;
    case Event::NONE:
      break;
  }
}


void loop() {
  pollRemote();

  navigator.moveIfNesc();
  // cameraController.shutterIfNesc();

  screen.update();

  delay(10);

}


// Interupt handler for timer 1
ISR(TIMER1_COMPA_vect) {
  // Reset timer1 to zero to consume interupt
  TCNT1 = T1_LOAD_VALUE;
  // cameraController.tick();
  tracker.tick();
  // Serial.println("Interupt");
}
