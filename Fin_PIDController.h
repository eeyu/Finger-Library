#ifndef __FIN_PID__
#define __FIN_PID__

#include "Fin_Timer.h"
#include "Fin_Math.h"

struct PIDGains {
	PIDGains(float nkp, float nki, float nkd) {
		kp = nkp;
		ki = nki;
		kd = nkd;
	}
	
	float kp;
	float ki;
	float kd;
};

class PIDController {
public:
	PIDController() {
		dt_timer.reset();
		dt_timer.usePrecision();
	}

	void bindErrorReference(float *nerror_ref) {
		error_ref = nerror_ref;
	}

	void setPIDGains(float nkp, float nki, float nkd) {
		kp = nkp;
		ki = nki;
		kd = nkd;
	}

	void setPIDGains(PIDGains gains) {
		setPIDGains(gains.kp, gains.ki, gains.kd);
	}

	void setMaxIntegrator(float nmax_integrator) {
		max_integrator = nmax_integrator;
	}

	float stepAndGet() {
		float error = *error_ref;
		float dt = dt_timer.dtSec();
		dt_timer.reset();

		float derror = (error - prev_error)/dt;
		prev_error = error;

		error_integrator += error * dt;
		error_integrator = fbound(error_integrator, -max_integrator, max_integrator);

		float control = kp * error +
						ki * error_integrator +
						kd * derror;
		return control;
	}

private:
	Timer dt_timer;

	float kp = 0;
	float ki = 0;
	float kd = 0;
	float max_integrator = 0;

	float *error_ref;
	float prev_error;
	float error_integrator;
};

#endif