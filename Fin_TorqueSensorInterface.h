#ifndef __FINTORQUESW__
#define __FINTORQUESW__

class TorqueSensor {
public:
	TorqueSensor() {

	}

	virtual void tare(int times=10) = 0;

	bool isTared() {
		return is_tared;
	}

	void setTared() {
		is_tared = true;
	}

	virtual float getTorqueNm() = 0;

protected:
	virtual float readRaw() = 0;

	float getRawOffset() {
		return raw_offset;
	}

	void setTareOffset(float offset) {
		raw_offset = offset;
		setTared();
	}

private:
	float raw_offset = 0;

	bool is_tared = false;
};


#endif