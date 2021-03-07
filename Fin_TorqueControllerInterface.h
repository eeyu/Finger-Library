#ifndef __FIN_TORQUECONTROLLERINTER__
#define __FIN_TORQUECONTROLLERINTER__

#include "Fin_PIDController.h"
#include "Fin_TorqueSensorInterface.h"
#include "Fin_ContactSensorInterface.h"

class TorqueController {
public:
	TorqueController() {
	
	}

	void setup() {
		bindSensorReferences();
		torque_sensor_ref->tare();
		if (contact_sensor_ref && (!torque_sensor_ref->isTared())) {
			contact_sensor_ref->tare();
		}
		controller.bindErrorReference(&torque_error);
	}
// Parameters
	void setParameters(PIDGains gains, float max_PID_integrator, float nmax_response) {
		controller.setPIDGains(gains);
		controller.setMaxIntegrator(max_PID_integrator);
		max_response = nmax_response;
	}

	void shouldOnlyControlWhenContacting(bool should) {
		control_only_when_contacting = should;
	}
// Operation
	void setDesiredTorque(float ndesired_torque) {
		desired_torque = ndesired_torque;
	}

	float stepAndGet() {
		// issue: should PID integrator be updated when control is bypassed?
		float measured_torque = torque_sensor_ref->getTorqueNm();
		torque_error = desired_torque - measured_torque;
		float control_response = controller.stepAndGet();

		if (control_only_when_contacting && !contact_sensor_ref->isContacting()) {
			return NO_CONTACT_RESPONSE;
		} else {
			return fbound(control_response, -max_response, max_response);
		}
	}

	float getMeasuredTorque() {
		return torque_sensor_ref->getTorqueNm();
	}

	float getTorqueError() {
		return torque_error;
	}



protected:
	virtual void bindSensorReferences() = 0;
	TorqueSensor *torque_sensor_ref;
	ContactSensor *contact_sensor_ref;

private:
	float desired_torque = 0;

	float torque_error;

	PIDController controller;
	float max_response;
	bool control_only_when_contacting = false;

	const float NO_CONTACT_RESPONSE = 0;
};

#endif