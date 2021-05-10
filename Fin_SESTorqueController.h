#ifndef __FIN_SESTORQUECONTROL__
#define __FIN_SESTORQUECONTROL__

#include "Fin_TorqueControllerInterface.h"
#include "Fin_SeriesElasticSensor.h"
#include "Fin_LPFilter.h"

class SESTorqueController: public TorqueController {
public:
	SESTorqueController() {
	}

	void setup(byte SES_READ_PIN) {
		series_elastic_sensor.setup(SES_READ_PIN);
		TorqueController::setup();
		shouldOnlyControlWhenContacting(false);
	}

	float getMeasuredTorque() {
		float raw_torque = series_elastic_sensor.getTorqueNm();
		//float filtered_torque = filter.stepAndGet(raw_torque);
		return raw_torque;
	}

private:
	SeriesElasticSensor series_elastic_sensor;

	void bindSensorReferences() {
		torque_sensor_ref = &series_elastic_sensor;
		//contact_sensor_ref = &HX711_sensor;
	}

	//LPFilterO2A02 filter;

};

#endif