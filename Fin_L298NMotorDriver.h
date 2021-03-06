#ifndef __FIN_L298NDRIVERSW__
#define __FIN_L298NDRIVERSW__

#include "Fin_DCMotorDriverInterface.h"
#include "Fin_Math.h"

class L298NMotorDriver : public MotorDriver {
public:
	L298NMotorDriver() {
	}

    void setup(byte nENA, byte nDIR1, byte nDIR2) {
        ENA = nENA;
        DIR1 = nDIR1;
        DIR2 = nDIR2;

        pinMode(ENA, OUTPUT);
        pinMode(DIR1, OUTPUT);
        pinMode(DIR2, OUTPUT);
    }

    void stop() {
        analogWrite(ENA, 0);
    }

private:
    const float ANALOG_WRITE_MAXIMUM = 256.0;

    int ENA;
    int DIR1;
    int DIR2;

    void switchToDirection1() {
        digitalWrite(DIR1, LOW);
        digitalWrite(DIR2, HIGH);
    }

    void switchToDirection2() {
        digitalWrite(DIR1, HIGH);
        digitalWrite(DIR2, LOW);
    }

    void writeVoltage(float voltage) {
        analogWrite(ENA, (int)(fabs(voltage)/getMaxVoltage() * ANALOG_WRITE_MAXIMUM));
    }
};

#endif