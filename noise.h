#ifndef NOISE_H
#define NOISE_H


using namespace std;

class Noise
{
	public:
		Noise(double _factor=3.0);
		double IntegerNoise();
		double lerp();

	private:
		double m_r, m_s, m_la, m_lb;
		double m_factor; // how much we want to stretch the result
		int m_step, m_seed, m_localStp;

		double interpolation(double w);
};

//--------------------------------------------------------------------

inline Noise::Noise(double _factor)
:m_factor(_factor), m_seed(105+rand()%10000), m_localStp(0)
{
	m_lb=IntegerNoise();
	m_seed++;
}

//--------------------------------------------------------------------

inline double Noise::interpolation(double w)
{
	w=w*(w*(w*(6.0*pow(w,2)-15.0*w + 10.0)));
   return m_la*(1 - w)+m_lb*w;
}

//--------------------------------------------------------------------

#endif
