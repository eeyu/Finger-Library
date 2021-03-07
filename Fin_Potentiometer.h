#ifndef __FIN_POTENT__
#define __FIN_POTENT__

#include "Fin_Parameters.h"

class Potentiometer {
public:
	Potentiometer() {

	}

    void setup(byte nread_pin) {
        read_pin = nread_pin;

        pinMode(read_pin, INPUT);
    }

    float getReadingNormalized() {
        int read = analogRead(read_pin);
        float normalized_read = read / ANALOG_READ_SCALE;
        return normalized_read;
    }

private:
	byte read_pin;
};

#endif

