#pragma once
#include "InstrumentFactory.h"
#include "Note.h"
#include "ASDREnvelope.h"
#include "DrumSynth.h"

const double NUM_SECS_IN_MINUTE = 60.0;


class CDrumSynthFactory :
	public CInstrumentFactory
{
public:
	void SetNote(CNote* note) override;
	CDrumSynthFactory();
	~CDrumSynthFactory();
	void SetBPM(double bpm) { m_bpm = bpm; }
	CDrumSynth* CreateInstrument();

private:

	CASDREnvelope m_envelope;
	double m_bpm;
	double m_freq;
	double m_decay;
	double m_sustain;
	double m_duration;
	double m_time;
	double m_attack;
	double m_release;
	double m_fAttack;
	double m_fRelease;
	double m_Filterfreq;
	double m_bw;
};

