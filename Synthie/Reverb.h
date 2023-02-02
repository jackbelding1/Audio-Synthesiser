#pragma once
#include "Effect.h"
class CReverb :
    public CEffect
{
public:
    CReverb();
    ~CReverb();

    virtual void SetNote(CNote* note);

    virtual void Process(double*, double*);
    virtual bool Generate();
    virtual void Start();


private:
    double m_time;

};

