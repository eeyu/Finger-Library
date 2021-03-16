#ifndef __FIN_LOADTORQUECONTROL__
#define __FIN_LOADTORQUECONTROL__

#include "Fin_TorqueControllerInterface.h"
#include "Fin_TorqueContactSensorHX711.h"
#include "Fin_LPFilter.h"

class HX711TorqueController: public TorqueController {
public:
	HX711TorqueController() {
	}

	void setup(byte DOUT, byte SCK) {
		HX711_sensor.setup(DOUT, SCK);
		TorqueController::setup();
	}

	void setContactThreshold(float thresh) {
		HX711_sensor.setContactThreshold(thresh);
	}

	float getMeasuredTorque() {
		float raw_torque = HX711_sensor.getTorqueNm();
		float filtered_torque = filter.stepAndGet(raw_torque);
		return filtered_torque;
	}

private:
	TorqueContactSensorHX711Nm HX711_sensor;

	void bindSensorReferences() {
		torque_sensor_ref = &HX711_sensor;
		contact_sensor_ref = &HX711_sensor;
	}

	LPFilterO2A02 filter;

};

#endif