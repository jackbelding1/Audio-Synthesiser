#pragma once
#include "WaveInstrument.h"
#include "InstrumentFactory.h"
#include "WaveTable.h"
#include <vector>
#include <string>

using namespace std;

class CWaveInstrumentFactory : public CInstrumentFactory
{
public:
    CWaveInstrumentFactory(void);
    ~CWaveInstrumentFactory(void);

    void SetNote(CNote* note) override;
    CWaveInstrument* CreateInstrument(wstring &);
    void SetBPM(double bpm) { m_bpm = bpm; }
    bool LoadFile();

    void SetInstrument(wstring instrument) { m_instrument = instrument; }

private:
    vector<short> m_wave;
    CWaveTable m_waveTable;
    wstring m_instrument;
    double m_bpm;
    double m_duration;
    double m_freq;
    double m_decay;
    double m_sustain;
    double m_time;
    double m_attack;
    double m_release;
};