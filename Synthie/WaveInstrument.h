#pragma once
#include "instrument.h"
#include "WavePlayer.h"
#include "ASDREnvelope.h"
#include <string>
#include <vector>
#include "WaveTable.h"

using namespace std;

class CWaveInstrument :
    public CInstrument
{
public:
    CWaveInstrument(void);
    CWaveInstrument(wstring);
    ~CWaveInstrument(void);

    virtual void Start();
    virtual bool Generate();
    virtual void SetNote(CNote* note);
    void SetAttack(double attack) { m_envelope.SetAttack(attack); }
    void SetRelease(double release) { m_envelope.SetRelease(release); }
    void SetSustain(double sustain) { m_envelope.SetSustain(sustain); }
    void SetDecay(double decay) { m_envelope.SetDecay(decay); }
    void SetDuration(double d) { m_envelope.SetDuration(d); }

    bool Load();

    CWavePlayer* GetPlayer() { return &m_wavePlayer; }

private:
    CWavePlayer m_wavePlayer;
    CASDREnvelope m_envelope;
    wstring m_name;
    vector<short> m_wave;
    CWaveTable m_waveTable;

};