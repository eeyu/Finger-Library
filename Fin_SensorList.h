#ifndef __SENSORLIST__
#define __SENSORLIST__

#include "Fin_Sensor.h"

class SensorList {
	List<Sensor *> sensor_list;

	SensorList() {

	}

	void add(Sensor *s) {

	}

	void remove(int i) {

	}

	void stepAll() {
		for (int i = 0; i < sensor_list.size(); i++) {
			Sensor *s = sensor_list.get(i);
			s->step();
		}
	}
}

#endif