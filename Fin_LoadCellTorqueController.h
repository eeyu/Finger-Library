#ifndef __FIN_LOADTORQUECONTROL__
#define __FIN_LOADTORQUECONTROL__

#include "Fin_TorqueControllerInterface.h"
#include "Fin_TorqueContactSensorHX711.h"

class HX711TorqueController: public TorqueController {
public:
	HX711TorqueController() {
	}

	void setup(byte DOUT, byte SCK) {
		HX711_sensor.setup(DOUT, SCK);
		TorqueController::setup();
	}

private:
	TorqueContactSensorHX711Nm HX711_sensor;

	void bindSensorReferences() {
		torque_sensor_ref = &HX711_sensor;
		contact_sensor_ref = &HX711_sensor;
	}
};

#endif