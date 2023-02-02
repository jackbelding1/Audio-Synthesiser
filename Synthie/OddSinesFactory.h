
#include "OddSinesInstrument.h"
#pragma once


class COddSinesFactory
{
public:
	COddSinesInstrument* CreateInstrument();
	COddSinesFactory();
	~COddSinesFactory();

	void SetNote(CNote* note);

private:
	double m_amps[4];

};

