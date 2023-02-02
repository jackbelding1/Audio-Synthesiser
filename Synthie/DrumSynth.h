#pragma once
#include "Instrument.h"
#include "SineWave.h"
#include "AR.h"
#include "ASDREnvelope.h"
#include "Note.h"
#include "PitchModulator.h"
#include "ASDREFilterEnvelope.h"

class CDrumSynth :
	public CInstrument
{
public:

	CDrumSynth();
	CDrumSynth(double, double, double);
	~CDrumSynth();

	void SetNote(CNote* note);
	const double NUM_SECS_IN_MINUTE = 60.0;
	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f) { m_sinewave.SetFreq(f); }
	void SetAmplitude(double a) { m_sinewave.SetAmplitude(a); }
	void SetDuration(double d) { m_duration = d; }

	CASDREnvelope GetEnvelope() { return m_envelope; }
	CPitchModulator GetPitchMod() { return m_pitchmod; }
	CASDREFilterEnvelope GetFilterEnvelope() { return m_filterEnvelope; }

	void SetAttack(double attack) { m_envelope.SetAttack(attack); }
	void SetRelease(double release) { m_envelope.SetRelease(release); }
	void SetSustain(double sustain) { m_envelope.SetSustain(sustain); }
	void SetDecay(double decay) { m_envelope.SetDecay(decay); }

	void SetFilterFreq(double freq) { m_filterEnvelope.SetFreq(freq); }
	void SetBW(double bw) { m_filterEnvelope.SetBW(bw); }
	void SetFilterAttack(double attack) { m_filterEnvelope.SetAttack(attack); }
	void SetFilterRelease(double release) { m_filterEnvelope.SetRelease(release); }
	void SetTime(double time) { m_filterEnvelope.SetTime(time); }

private:
	CSineWave   m_sinewave;
	CASDREnvelope m_envelope;
	CPitchModulator m_pitchmod;
	CASDREFilterEnvelope m_filterEnvelope;
	double m_duration;
	double m_time;
};

