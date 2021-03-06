#ifndef __FIN_MOTORDRIVERSW__
#define __FIN_MOTORDRIVERSW__

#include "Fin_Math.h"

class MotorDriver {
public:
	MotorDriver() {

	}

	void setMaxVoltage(float nvoltage) {
        max_voltage = nvoltage;
    }

    virtual void stop() = 0;

    void sendVoltageCommand(float voltage) {
    	voltage = fbound(voltage, -max_voltage, max_voltage);

      	if (!directionIsConsistentWithVoltage(voltage)) {
    		switchDirection();
      	}

      	// Serial.print(voltage); Serial.print(" ");
       //  Serial.print(direction); Serial.print(" ");

        writeVoltage(voltage);
    }

    float getMaxVoltage() {
    	return max_voltage;
    }

protected:
	virtual void writeVoltage(float voltage)  = 0;
	virtual void switchToDirection1() = 0;
	virtual void switchToDirection2() = 0;

	void switchDirection() {
      	stop();
    	if (direction == direction1) {
    		switchToDirection2();
    		direction = direction2;
    	} else {
    		switchToDirection1();
    		direction = direction1;
    	}
    }

	float max_voltage;

private:
	const int direction1 = 1;
	const int direction2 = -1;

	int direction = direction1;

    bool directionIsConsistentWithVoltage(float voltage) {
        return voltage * direction > 0;
    }
};

#endif

