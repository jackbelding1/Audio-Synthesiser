#pragma once
#include "Instrument.h"


class CEffect :
	public CInstrument
{
public:
	virtual void SetNote(CNote* note) = 0;
	CEffect();
	~CEffect();

	virtual void Process(double*, double*) = 0;

private:

};

