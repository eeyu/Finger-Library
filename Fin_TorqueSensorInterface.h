#ifndef __FINTORQUESW__
#define __FINTORQUESW__

class TorqueSensor {
public:
	TorqueSensor() {

	}

	void tare(int times=10) {
		long sum = 0;
		for (byte i = 0; i < times; i++) {
			sum += readRaw();
			delay(0);
		}
		float average = sum/times;
		raw_offset = average;
		is_tared = true;
	}

	bool isTared() {
		return is_tared;
	}

	virtual float getTorqueNm() = 0;

protected:
	virtual float readRaw() = 0;

	float getRawOffset() {
		return raw_offset;
	}

private:
	float raw_offset = 0;

	bool is_tared = false;
};


#endif