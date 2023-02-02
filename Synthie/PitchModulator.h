#pragma once
#include "AudioNode.h"
#include "SineWave.h"
class CPitchModulator :
	public CAudioNode
{
public:
	CPitchModulator();
	~CPitchModulator();

	virtual void Start();

	void SetDuration(double d) { m_duration = d; }
	void SetSine(CSineWave* wave) { m_sine = wave; }
	bool Generate();
	void SetFreq(double freq) { m_baseFreq = freq; }

private:
	double m_duration;
	CSineWave* m_sine;
	double m_time;
	double m_baseFreq;
};

