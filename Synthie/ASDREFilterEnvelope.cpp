#include "stdafx.h"
#include "ASDREFilterEnvelope.h"
#include <math.h>

using namespace std;

CASDREFilterEnvelope::CASDREFilterEnvelope()
{
	wrloc = 0;
	queueInput.resize(QUEUESIZE);
	queueOutput.resize(QUEUESIZE);
	for (int i = 0; i < QUEUESIZE; i++)
	{
		queueInput[i] = 0;
		queueOutput[i] = 0;
	}
}

CASDREFilterEnvelope::~CASDREFilterEnvelope()
{
}

bool CASDREFilterEnvelope::Generate()
{
	m_source->Generate();

	double audio[2];
	audio[0] = m_source->Frame(0);
	audio[1] = m_source->Frame(1);

	// Keep track of time
	double time = 0;

	wrloc = (wrloc + 2) % QUEUESIZE;
	queueInput[wrloc] = audio[0];
	queueInput[wrloc + 1] = audio[1];

	double audioL = 0;
	double audioR = 0;

	double R = double(1 - m_bw / 2.0);
	double theta = acos((2 * R * cos(2 * 3.14159265359 * m_freq)) / (1 + (R * R)));
	double A = ((1 - (R * R)) * sin(theta)) * 10.0;

	// process the input
	int rdloc = (wrloc + QUEUESIZE) % QUEUESIZE;
	audioL += (queueInput[rdloc++] * A);
	audioR += (queueInput[rdloc] * A);

	// process the output
	// one sample delay
	int delaylength = 1 * 2;
	rdloc = (wrloc + QUEUESIZE - delaylength) % QUEUESIZE;
	audioL += (queueOutput[rdloc++] * 2 * R * cos(theta));
	audioR += (queueOutput[rdloc] * 2 * R * cos(theta));

	// two sample delay 
	delaylength = 2 * 2;
	rdloc = (wrloc + QUEUESIZE - delaylength) % QUEUESIZE;
	audioL += (queueOutput[rdloc++] * (R * R) * -1);
	audioR += (queueOutput[rdloc] * (R * R) * -1);

	// reduce gain to avoid big time clipping
	audio[0] = RangeBound((audioL  * 0.8));
	audio[1] = RangeBound((audioR  * 0.8));

	// write the output to the output buffer
	queueOutput[wrloc] = audioL;
	queueOutput[wrloc + 1] = audioR;

	m_frame[0] = audioL;
	m_frame[1] = audioR;


	// Update time
	m_time += GetSamplePeriod();

	// We return true until the time reaches the duration.
	return m_time < m_duration;
}

void CASDREFilterEnvelope::Start()
{
	m_source->SetSampleRate(GetSampleRate());
	m_source->Start();
	m_time = 0;
}

short CASDREFilterEnvelope::RangeBound(double d)
{
	if (d > 32767)
	{
		return 32767;
	}
	if (d < (32768 * -1))
	{
		return (32768 * -1);
	}
	return short(d);
}
