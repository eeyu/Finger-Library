#ifndef __FIN_TEIMPEDANCECONTROL__
#define __FIN_TEIMPEDANCECONTROL__

#include "Fin_ImpedanceControllerInterface.h"
#include "Fin_TeensyEncoder.h"
#include "Fin_Parameters.h"
#include "Fin_MotorModel.h"

class TEImpedanceController : public ImpedanceController {
public:
	TEImpedanceController(byte pin1, byte pin2) : encoder_hw{pin1, pin2} {
		encoder_hw.setup(STEPS_PER_REV);
	}

private:
	void bindSensorReferences() {
		angle_sensor_ref = &encoder_hw;
	}

	float getFeedFowardResponse() {
		float friction;
		if (motorIsStalled()) {
			int desired_torque_direction = getDesiredTorqueDirection();
			friction = motor_model.getStaticFrictionNm(desired_torque_direction); // this isnt fully correct...static friction acts opposite of conbo of motor applied and external force
		} else {
			friction = 0;
		}
		return -friction;
	}

	bool motorIsStalled() {
		float velocity_deg = encoder_hw.getVelocityDeg();
		return (fabs(velocity_deg) < VELOCITY_ZERO_DELTA_DEG);
	}

	int getDesiredTorqueDirection() {
		float position_error = getPositionError();
		// float desired_torque = getImpedanceResponse();
		// if (fabs(desired_torque) < CONSIDER_STATIC_FRICTION_TORQUE_THRESHOLD) {
		// 	return 0;
		// } else {
			return sgn<float>(position_error);
		// }
		
	}

	TeensyEncoder encoder_hw;

	const float MOTOR_S_FRICTION_NM = 0;//30;
	MotorModel motor_model{MOTOR_S_FRICTION_NM, 0, 0};

	const float VELOCITY_ZERO_DELTA_DEG = 0.001;
	const int STEPS_PER_REV = ENCODER_STEPS_PER_REV;

	const float CONSIDER_STATIC_FRICTION_TORQUE_THRESHOLD = 20;
};


#endif
