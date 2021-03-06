#ifndef __FINHX711__
#define __FINHX711__

#include "Fin_TorqueSensorInterface.h"
#include "Fin_ContactSensorInterface.h"
#include "HX711.h"

class TorqueContactSensorHX711Nm : public TorqueSensor, public ContactSensor {
public:
	TorqueContactSensorHX711Nm() {

	}

	void setup(byte dout, byte pd_sck) {
		torque_sensor_HW.begin(dout, pd_sck);
		torque_sensor_HW.set_scale(KG_SCALE);
	}

	void tare() {
		torque_sensor_HW.tare();
	}

	float getTorqueNm() {
		float kg_reading = torque_sensor_HW.get_units();
		float torque_Nm = kg_reading * GRAVITY * mounting_length_mm / 1000.0;
		return torque_Nm;
	}

	bool isContacting() {
		if (fabs(getTorqueNm()) > CONTACT_THRESHOLD_NM) {
			return true;
		} else {
			return false;
		}
	}

private:
	HX711 torque_sensor_HW;
	float mounting_length_mm = 62.5;

	const int NUM_TARE_READING = 20;
	const int KG_SCALE = 398.f;
	const int GRAVITY = 9.81;

	const int CONTACT_THRESHOLD_NM = 14.f;

	float readRaw() {
		return torque_sensor_HW.read();
	}
};


#endif