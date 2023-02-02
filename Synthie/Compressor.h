#pragma once
#include "Effect.h"
class CCompressor :
    public CEffect
{
public:
    CCompressor();
    ~CCompressor();

    void SetNote(CNote* note);

    virtual void Process(double*, double*);
    virtual void Start();
    virtual bool Generate();

private:

    double m_threshold;
    double m_ratio;
    double m_time;
    double m_attack;
    double m_release;
    bool m_active;

};

