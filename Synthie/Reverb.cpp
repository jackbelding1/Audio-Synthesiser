#include "stdafx.h"
#include "Reverb.h"

CReverb::CReverb()
{
}

CReverb::~CReverb()
{
}

void CReverb::SetNote(CNote* note)
{
}

void CReverb::Process(double* inputFrame, double* outputFrame)
{
	for (int i = 0; i < 2; i++)
	{
		outputFrame[i] += inputFrame[i];
	}
}

bool CReverb::Generate()
{
    return false;
}

void CReverb::Start()
{
}
