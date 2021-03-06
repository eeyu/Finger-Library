#ifndef __FIN_MOTORDRIVERSW__
#define __FIN_MOTORDRIVERSW__

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

      	if (voltage * direction < 0) {
    		switchDirection();
      	}

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
    	if (direction == Direction1) {
    		switchToDirection2();
    		direction = Direction2;
    	} else {
    		switchToDirection1();
    		direction = Direction1;
    	}
    }

	float max_voltage;

private:
	enum Direction{Direction1, Direction2};

    Direction direction; // THe direction the motor is moving in
};

#endif

