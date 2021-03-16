#ifndef __FINHX711__
#define __FINHX711__

#include "Fin_TorqueSensorInterface.h"
#include "Fin_ContactSensorInterface.h"
#include "HX711.h"
#include "Fin_Math.h"

class TorqueContactSensorHX711Nm : public TorqueSensor, public ContactSensor {
public:
	TorqueContactSensorHX711Nm() {

	}

	void setup(byte dout, byte pd_sck) {
		torque_sensor_HW.begin(dout, pd_sck);
		torque_sensor_HW.set_scale(KG_SCALE);
	}

	void tare(int times=10) {
		torque_sensor_HW.tare(times);
		setTared();
	}

// parameters
	void setContactThreshold(float thresh) {
		contact_threshold_Nm = thresh;
	}

	void setLeverArmMM(float narm) {
		mounting_length_mm = narm;
	}

// usage
	float getTorqueNm() {
		float kg_reading = torque_sensor_HW.get_units();
		float torque_Nm = kg_reading * GRAVITY * mounting_length_mm / 1000.0;
		last_reading = torque_Nm;
		return torque_Nm;
	}

	bool isContacting() {
		float torque_reading = last_reading;
		if (fixedAbs(torque_reading) > contact_threshold_Nm) {
			return true;
		} else {
			return false;
		}
	}


private:
	HX711 torque_sensor_HW;
	float mounting_length_mm = 80;

	const int NUM_TARE_READING = 20;
	const int KG_SCALE = 398.f;
	const int GRAVITY = 9.81;

	const float DEFAULT_CONTACT_THRESH_NM = 10.f;
	float contact_threshold_Nm = DEFAULT_CONTACT_THRESH_NM;

	float last_reading = 0;

	float getLastReading() {
		return last_reading;
	}

	float readRaw() {
		return torque_sensor_HW.read();
	}


};


#endif