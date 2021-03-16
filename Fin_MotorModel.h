#ifndef __FIN_MOTORMODEL__
#define __FIN_MOTORMODEL__

#include "Fin_Math.h"

class MotorModel {
public: 
	MotorModel(float sfriction, float kfriction, float vfriction) {
		static_friction_Nm = sfriction;
		kinetic_friction_Nm = kfriction;
		viscous_friction_prads = vfriction;
	}

	float getStaticFrictionNm(int applied_torque_direction) {
		return -applied_torque_direction * static_friction_Nm;
	}

	float getDynamicFrictionNm(float velocity_rads) {
		int velocity_direction = sgn<float>(velocity_rads);
		float friction = -velocity_direction * (kinetic_friction_Nm + viscous_friction_prads * velocity_rads);
		return friction;
	} 

private:
	float static_friction_Nm = 0;
	float kinetic_friction_Nm = 0;
	float viscous_friction_prads = 0;

	const float ZERO_VELOCITY_DELTA = 0.001;
};


#endif 