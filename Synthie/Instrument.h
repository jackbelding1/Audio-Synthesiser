#pragma once
#include "AudioNode.h"
#include "Note.h"

#define NUMEFFECTSCHANNELS				3


class CInstrument :
	public CAudioNode
{
public:
	CInstrument();
	CInstrument(double);
	virtual ~CInstrument();
	virtual void SetNote(CNote *note) = 0;

	double Send(int i) { return m_sends[i]; }
	void SetSend(int i, double send) { m_sends[i] = send; }

private:
	double m_sends[NUMEFFECTSCHANNELS];
};

