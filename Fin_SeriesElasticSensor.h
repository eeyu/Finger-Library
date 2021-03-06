#ifndef __FINSEASW__
#define __FINSEASW__

#include "Fin_TorqueSensorInterface.h"
#include "Fin_ContactSensorInterface.h"

class SeriesElasticSensor : public TorqueSensor {
public:
	SeriesElasticSensor() {

	}

	void setup(byte nread_pin) {
		read_pin = nread_pin;
		pinMode(read_pin, INPUT);
	}

	float getTorqueNm() {
		float read = readRaw() - getRawOffset();
		return convertReadToTorqueNm(read);
	}

	float readRaw() {
		return analogRead(read_pin)/ANALOG_READ_SCALE;
	}

	float convertReadToTorqueNm(float read_value) {
		return 1 * read_value;
	}

private:
	byte read_pin;

	const float ANALOG_READ_SCALE = 1024.0;
};


#endif