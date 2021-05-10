#ifndef __FIN_IMPEDANCECONTROLLERINTER__
#define __FIN_IMPEDANCECONTROLLERINTER__

#include "Fin_PIDController.h"
#include "Fin_TorqueSensorInterface.h"

// Impedance: F = kx + bv
// Admittance: x = F/k - b/k v

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
		measured_torque = torque_sensor_ref->getAbsoluteAngleDeg();
		measured_velocity = angle_sensor_ref->getVelocityDeg();

		float control_response = getImpedanceResponse(measured_torque, measured_velocity);
		return control_response;
	}

// debugging
	float getMeasuredTorque() {
		return torque_sensor_ref->getTorqueNm();
	}

protected:
	TorqueSensor *torque_sensor_ref;
	Encoder *angle_sensor_ref;

	virtual void bindSensorReferences() = 0;

	virtual float getFeedFowardTorque() {
		return 0;
	}

	// does not use PID controller - not accurate velocity sensing. trust encoder instead.
	float getImpedanceResponse(float measured_torque, float measured_velocity) {
		float position_error = measured_position - desired_position;

		float control_response = -torque_error / stiffness - -measured_velocity * damping / stiffness;
        return control_response;
	}

private:
	float desired_position = 0;
	float stiffness;
	float damping;

	float measured_position = 0;
	float measured_velocity = 0;


};

#endif