#pragma once
#include "Note.h"
#define NUMEFFECTSCHANNELS				3

class CInstrumentFactory
{
public:
	virtual void SetNote(CNote* note);

	CInstrumentFactory();
	~CInstrumentFactory();

	double Send(int i) { return m_sends[i]; }


private:
	double m_sends[NUMEFFECTSCHANNELS];

};

