#include "stdafx.h"
#include "PitchModulator.h"

CPitchModulator::CPitchModulator()
{
}

CPitchModulator::~CPitchModulator()
{
}

void CPitchModulator::Start()
{
	m_time = 0;
}

bool CPitchModulator::Generate()
{
	if (m_time < m_duration* 0.25)
	{
		m_sine->SetFreq(m_baseFreq * 1.5);
	}
	else
	{
		if (m_baseFreq * (m_duration - m_time) / m_time > 40.0)
		{
			m_sine->SetFreq(m_baseFreq * ((m_duration - m_time) / m_time));

		}
		else
		{
			m_sine->SetFreq(40.0);
		}


	}
	// Update time
	m_time += GetSamplePeriod();

	// We return true until the time reaches the duration.
	return m_time < m_duration;
}
