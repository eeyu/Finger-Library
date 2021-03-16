#ifndef __FIN_IMPEDANCECONTROLLERINTER__
#define __FIN_IMPEDANCECONTROLLERINTER__

#include "Fin_PIDController.h"
#include "Fin_EncoderInterface.h"

class ImpedanceController {
public:
	ImpedanceController() {
	
	}

	void setup() {
		bindSensorReferences();
	}

// Parameters
	void setDesiredDynamics(float nstiff, float ndamp) {
		stiffness = nstiff;
		damping = ndamp;
	}

// Operation
	void setDesiredPosition(float nposition) {
		desired_position = nposition;
	}


	float stepAndGet() {
		angle_sensor_ref->step();
		measured_position = angle_sensor_ref->getAbsoluteAngleDeg();
		measured_velocity = angle_sensor_ref->getVelocityDeg();

		float control_response = getImpedanceResponse() + getFeedFowardResponse();
		return control_response;
	}

// debugging
	float getMeasuredPosition() {
		return angle_sensor_ref->getAbsoluteAngleDeg();
	}

	// float getPositionError() {
	// 	return torque_error;
	// }

protected:
	RotaryEncoder *angle_sensor_ref;

	virtual void bindSensorReferences() = 0;

	virtual float getFeedFowardResponse() {
		return 0;
	}

	// does not use PID controller - not accurate velocity sensing. trust encoder instead.
	float getImpedanceResponse() {
		float position_error = measured_position - desired_position;
		float control_response = stiffness * -position_error
								 + damping * -measured_velocity;
        return control_response;
	}

	float getPositionError() {
		return getMeasuredPosition() - desired_position;
	}

private:
	float desired_position = 0;
	float stiffness;
	float damping;

	float measured_position = 0;
	float measured_velocity = 0;


};

#endif