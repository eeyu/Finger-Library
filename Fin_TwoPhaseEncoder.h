#ifndef __ABENCODER__
#define __ABENCODER__

#include "Seg_RotaryEncoder.h"
#include <arduino.h>

/* This is a 2-phase incremental encoder. To ensure the positing is accurate, an interrupt routine
 * is called every time the encoder ticks (on pin A). 
 *
 * The interrupt routine must be nonmember or static member function with no parameters and void output.
 * Thus, in order to use the encoder, either 
 *
 * a) The contents of ABPhaseEncoder and RotaryEncoder must be copied out as global variables in an 
 *    Arduino sketch, where updateStep() is the interrupt call. Note that cur_step must be declared 
 *    volatile (see "EncoderInterrupt.ino"). Or...
 *
 * b) UpdateStep() must be placed in a wrapper, and the calling object must be a global pointer
 *    to a global ABPhaseEncoder, the pointer being initialized in setup(). Note that the encoder
 *    itself must be declared volatile (See "EncoderClassInterrupt.ino). Or... UPDATE 7/10/2020: class doesn't need to be volatile. just the variable.
 *
 * c) The encoder keeps a pointer to a global, updating count. Or...
 *
 * d) UpdateStep() and the relevant variables must be declared static. Or...
 *
 * e) Some other method I haven't thought of.
 *
 * Option a) is byfar the cleanest in implementation but requires more global variables to be kept on the sketch. 
 * Option b) is messier but hides most of the implementation in the headers. Option c) has not yet been explored.
 */


class ABPhaseEncoder : public RotaryEncoder {
  int pinA; // Must be an interrupt pin
  int pinB;

  void (*ISR)();
public:
    ABPhaseEncoder() : RotaryEncoder() {}

    ABPhaseEncoder(int nA, int nB, int steps_per_rev, bool cont_rotation=true) : RotaryEncoder(steps_per_rev, cont_rotation) {
      pinA = nA;
      pinB = nB;
      pinMode(pinB, INPUT);
      pinMode(pinA, INPUT_PULLUP);
    }

    // Reset all parameter values
    void initialize(int nA, int nB, int nsteps_per_rev, bool cont_rotation=true) {
      RotaryEncoder::initialize(nsteps_per_rev, cont_rotation);
      pinA = nA;
      pinB = nB;
      pinMode(pinB, INPUT);
      pinMode(pinA, INPUT_PULLUP);
      if (ISR) {
        attachInterrupt(digitalPinToInterrupt(pinA), ISR, CHANGE);
      }

    }

    void attachISR(void (*updateCount)()) {
      if (pinA) {
        attachInterrupt(digitalPinToInterrupt(pinA), updateCount, CHANGE);
      } else {
        ISR = updateCount;
      }
    }

    void updateStep() {
      if (pinsAreSamePhase()) {
        step--;
        dt = -dt_timer.dt();
      } else {
        step++;
        dt = dt_timer.dt();
      }
      dt_timer.reset();
    }

    bool pinsAreSamePhase() {
        return digitalRead(pinB) == digitalRead(pinA);
    }

    void updateEncoder() {
        encoder_ptr1->updateStep();
    }
};

#endif