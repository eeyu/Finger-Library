#ifndef __FIN_LPFILTER__
#define __FIN_LPFILTER__

//Low pass bessel filter order=2 alpha1=0.02 
class  LPFilterO2A02
{
	public:
		LPFilterO2A02()
		{
			v[0]=0.0;
			v[1]=0.0;
			v[2]=0.0;
		}
	private:
		float v[3];
	public:
		float stepAndGet(float x) //class II 
		{
			v[0] = v[1];
			v[1] = v[2];
			v[2] = (5.593440209108096160e-3 * x)
				 + (-0.75788377219702429688 * v[0])
				 + (1.73551001136059190877 * v[1]);
			return 
				 (v[0] + v[2])
				+2 * v[1];
		}
};

//Low pass bessel filter order=2 alpha1=0.05 
class  LPFilterO2A05
{
	public:
		LPFilterO2A05()
		{
			v[0]=0.0;
			v[1]=0.0;
			v[2]=0.0;
		}
	private:
		float v[3];
	public:
		float stepAndGet(float x) //class II 
		{
			v[0] = v[1];
			v[1] = v[2];
			v[2] = (2.921062558939069298e-2 * x)
				 + (-0.49774398476624526211 * v[0])
				 + (1.38090148240868249019 * v[1]);
			return 
				 (v[0] + v[2])
				+2 * v[1];
		}
};

#endif
