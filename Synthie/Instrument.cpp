#include "stdafx.h"
#include "Instrument.h"


CInstrument::CInstrument()
{
	m_sends[0] = 1.0;
}

// Constructor to set the beats per minute
CInstrument::CInstrument(double bpm)
{
	m_bpm = bpm;
}

CInstrument::~CInstrument()
{
}
