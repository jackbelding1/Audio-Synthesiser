#include "StdAfx.h"
#include "WaveInstrumentFactory.h"
#include <cmath>
#include "audio/DirSoundSource.h"
#include <algorithm>
#include "Notes.h"
#include <cstdlib>

using namespace std;

CWaveInstrumentFactory::CWaveInstrumentFactory(void)
{

}

CWaveInstrumentFactory::~CWaveInstrumentFactory(void)
{
}


CWaveInstrument* CWaveInstrumentFactory::CreateInstrument(wstring & instrument_name)
{
    CWaveInstrument* instrument = new CWaveInstrument(instrument_name);

    // set sends
    for (int i = 0; i < NUMEFFECTSCHANNELS; i++)
    {
        instrument->SetSend(i, Send(i));
    }


    instrument->Load();
    instrument->SetAttack(m_attack);
    instrument->SetRelease(m_release);
    instrument->SetSustain(m_sustain);
    instrument->SetDecay(m_decay);
    instrument->SetDuration(m_duration);
    return instrument;
}

bool CWaveInstrumentFactory::LoadFile()
{
    m_wave.clear();

    wstring instrument = L"samples/" + m_instrument + L".wav";
    // convert wstring to const char*
    const wchar_t* input = instrument.c_str();

    // Count required buffer size (plus one for null-terminator).
    size_t size = (wcslen(input) + 1) * sizeof(wchar_t);
    char* buffer = new char[size];

    size_t convertedSize;
    std::wcstombs(buffer, input, size);

    if (!m_waveTable.LoadFile(buffer, &m_wave))
    {
        return false;
    }

    delete buffer;
    return true;
}

void CWaveInstrumentFactory::SetNote(CNote* note)
{
    // up call to set the set note function
    CInstrumentFactory::SetNote(note);

    // Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    note->Node()->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    // Loop over the list of attributes
    for (int i = 0; i < len; i++)
    {
        // Get attribute i
        CComPtr<IXMLDOMNode> attrib;
        attributes->get_item(i, &attrib);

        // Get the name of the attribute
        CComBSTR name;
        attrib->get_nodeName(&name);

        CComVariant value;
        attrib->get_nodeValue(&value);

        if (name == "duration")
        {
            value.ChangeType(VT_R8);
            // SetDuration(value.dblVal); // play the note for the duration in terms of seconds
            m_duration = (value.dblVal * (60 / m_bpm));

        }
        else if (name == "note")
        {
            m_freq = (NoteToFrequency(value.bstrVal));
        }
        else if (name == "atk")
        {
            value.ChangeType(VT_R8);
            m_attack = value.dblVal;
        }
        else if (name == "rls")
        {
            value.ChangeType(VT_R8);
            m_release = value.dblVal;
        }
        else if (name == "sus")
        {
            // sustain
            value.ChangeType(VT_R8);
            m_sustain = value.dblVal;

        }
        else if (name == "decay")
        {
            // decay
            value.ChangeType(VT_R8);
            m_decay = value.dblVal;

        }
    }

}