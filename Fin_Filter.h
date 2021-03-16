#ifndef __FIN_FILTER__
#define __FIN_FILTER__

template <typename T>
class Filter {
public:
	Filter() {};

	virtual T stepAndGet(T newRawRead) = 0;
};

#endif