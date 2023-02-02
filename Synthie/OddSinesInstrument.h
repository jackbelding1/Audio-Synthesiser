#pragma once
#include "instrument.h"
#include "AR.h"
#include "OddSines.h"

class COddSinesInstrument :
    public CInstrument
{
public:
    COddSinesInstrument(void);
    ~COddSinesInstrument(void);

    virtual void Start();
    virtual bool Generate();
    virtual void SetNote(CNote* note);
    void SetAmplitude(int i, double d) { m_sines.SetAmplitude(i, d); }
    void SetDuration(double d) { m_ar.SetDuration(d); }
    void SetFreq(double f) { m_sines.SetFreq(f); }
private:
    CAR         m_ar;
    double  m_time;
    COddSines   m_sines;
};