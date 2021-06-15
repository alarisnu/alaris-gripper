#ifndef Roller_h
#define Roller_h

/**
 * States
 */
#define READY 0
#define MOVE 1
#define CALIB 2

class Roller{
  public:
    Roller(byte pinA, byte pinB, byte pinE, byte anal){
      in1 = pinA; in2 = pinB; enA = pinE; sensorPin = anal;
      // Set all the motor control pins to outputs
      pinMode(enA, OUTPUT);
      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT);
      
      // Turn off motors - Initial state
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
    }

    void tick();

    void setGoal(byte goal){
      x = goal;
    };
  private:
    byte enA,in1,in2,sensorPin;

    int lightCalib;
    int sensorValue;
    byte state = CALIB;
    int lightCal;
    byte x;

    byte prev = 4;
    byte curr = 4;

    void directionControl(bool toTheRight) {
      analogWrite(enA, 255);
      digitalWrite(in1, toTheRight);
      digitalWrite(in2, !toTheRight);
    }
    
    bool is_next_on_right(int prev, int curr){
      bool is_right = false;
      
      int delta = curr - prev;
      if(delta > 0 && delta < 4) is_right = true;
      if(delta < -4 && delta > -8) is_right = true;
      return is_right;
    }
};

#endif
