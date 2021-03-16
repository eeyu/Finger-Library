#ifndef __FIN_SENSORWFILTER__
#define __FIN_SENSORWFILTER__

template <typename T>
class SensorWithFilter {
public:
	SensorWithFilter() {}

	T getFilteredRead() {
		return filter_ref->stepAndGet(getRawRead());
	}

	void setFilter(Filter<T> *nfilter) {
		filter_ref = nfilter;
	}

protected:
	virtual getRawRead() = 0;

private:
	Filter<T> *filter;

};



#endif