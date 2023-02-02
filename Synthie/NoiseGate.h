#pragma once
#include "Effect.h"

class CNoiseGate :
    public CEffect
{
public:
    CNoiseGate();
    ~CNoiseGate();

    virtual void SetNote(CNote*);
    virtual void Start();
    virtual void Process(double*, double*);
    virtual bool Generate();
    bool isOpen() { return m_open; }
private:

    double m_threshold;
    double m_release;
    double m_attack;
    double m_range;
    bool m_open;
    double m_time;
};

