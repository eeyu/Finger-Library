#ifndef __FINCONTACTSW__
#define __FINCONTACTSW__

class ContactSensor {
public:
	ContactSensor() {

	}

	void tare(int times=10) {
		Serial.println("taring contact sensor");
		long sum = 0;
		for (byte i = 0; i < times; i++) {
			sum += readRaw();
			delay(0);
		}
		float average = sum/times;
		raw_offset = average;
	}

	virtual bool isContacting() = 0;



protected:
	virtual float readRaw() = 0;

	float getRawOffset() {
		return raw_offset;
	}

private:
	float raw_offset = 0;

};


#endif