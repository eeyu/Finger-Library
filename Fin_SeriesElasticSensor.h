#ifndef __FINSEASW__
#define __FINSEASW__

#include "Fin_TorqueSensorInterface.h"
#include "Fin_ContactSensorInterface.h"
#include  "Fin_Parameters.h"

class SeriesElasticSensor : public TorqueSensor {
public:
	SeriesElasticSensor() {

	}

	void setup(byte nread_pin) {
		read_pin = nread_pin;
		pinMode(read_pin, INPUT);
		tare();
	}

	void tare(int times=10) {
		setTareOffset(tare_offset);
	}

	float getTorqueNm() {
		float read = readRaw() - getRawOffset();
		read = applyDeadband(read);

		return convertReadToTorqueNm(read);
	}

	float getRawRead() {
		return readRaw();
	}

	float convertReadToTorqueNm(float read_value) {
		return SPRING_CONSTANT * read_value;
	}



private:
	byte read_pin;

	// const float SPRING_CONSTANT = 1.2; for 0.625", original spring
	const float SPRING_CONSTANT = 3.2; // for 17mm, stronger spring

	float tare_offset = 0.513;
	float deadband_size = 0.02;

	//const float lower_deadband = 0.507;
	//const float upper_deadband = 0.56;
	//const float tare_offset = (lower_deadband+upper_deadband)/2;
	//const float deadband_size = tare_offset - lower_deadband;

	float readRaw() {
		return analogRead(read_pin)/ANALOG_READ_SCALE;
	}

	float applyDeadband(float read) {
		if (fabs(read) < deadband_size) {
			 return 0;
		} else {
			return read;
		}
	}

};


#endif