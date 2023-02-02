#include "stdafx.h"
#include "ASDREnvelope.h"

CASDREnvelope::CASDREnvelope()
{
	m_duration = 1;
	m_attack = 1;
	m_release = 1;
	m_sustain = 1;
	m_decay = 1;
}

CASDREnvelope::~CASDREnvelope()
{
}

void CASDREnvelope::Start()
{
	m_source->SetSampleRate(GetSampleRate());
	m_source->Start();
	m_time = 0;
}

bool CASDREnvelope::Generate()
{
	// Tell the component to generate an audio sample
	m_source->Generate();

	// Read the component's sample and make it our resulting frame.
	if (m_time < m_attack)
	{
		// apply attack
		m_frame[0] = m_source->Frame(0) * m_time / m_attack;
		m_frame[1] = m_source->Frame(1) * m_time / m_attack;
	}
	else if (m_time < m_decay + m_attack)
	{
		// apply decay
		m_frame[0] = m_source->Frame(0) * (m_sustain + (1 - m_sustain *
			((m_decay + m_attack - m_time) / (m_decay + m_attack))));
		m_frame[1] = m_source->Frame(1) * (m_sustain + (1 - m_sustain *
			((m_decay + m_attack - m_time) / (m_decay + m_attack))));
	}
	else if (m_time >= m_duration - m_release)
	{
		// apply release
		m_frame[0] = m_source->Frame(0) * (m_duration - m_time) / m_release;
		m_frame[1] = m_source->Frame(1) * (m_duration - m_time) / m_release;
	}
	else
	{
		// sustain
		m_frame[0] = m_source->Frame(0) * m_sustain;
		m_frame[1] = m_source->Frame(1) * m_sustain;
	}
	// Update time
	m_time += GetSamplePeriod();

	// We return true until the time reaches the duration.
	return m_time < m_duration;
}
