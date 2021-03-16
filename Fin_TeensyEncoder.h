#ifndef __ABENCODER__
#define __ABENCODER__

#include "Fin_EncoderInterface.h"
#include "Encoder.h"
#include <Fin_Timer.h>

class TeensyEncoder : public RotaryEncoder {

public:
    TeensyEncoder(byte pin1, byte pin2) : encoder_HW{pin1, pin2} {}

    void setup(int steps_per_rev) {
        RotaryEncoder::setup(steps_per_rev);
    }

private:
    Encoder encoder_HW;

    int getRawStep() {
        return encoder_HW.read();
    }
};

#endif