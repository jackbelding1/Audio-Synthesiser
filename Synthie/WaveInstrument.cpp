#include "StdAfx.h"
#include "WaveInstrument.h"

CWaveInstrument::CWaveInstrument(void)
{
}

CWaveInstrument::CWaveInstrument(wstring name)
{
    m_name = name;
}

CWaveInstrument::~CWaveInstrument(void)
{
}


void CWaveInstrument::Start()
{
    m_envelope.SetSource(&m_wavePlayer);
    m_envelope.SetSampleRate(m_sampleRate);
    m_envelope.Start();
}


void CWaveInstrument::SetNote(CNote* note)
{
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


    }
}

bool CWaveInstrument::Load()
{
    m_wave.clear();

    wstring instrument = L"samples/" + m_name + L".wav";
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

    m_wavePlayer.SetSamples(&m_wave[0], (int)m_wave.size());

    delete buffer;
    return true;
}


bool CWaveInstrument::Generate()
{
    bool valid = m_envelope.Generate();

    m_frame[0] = m_envelope.Frame(0);
    m_frame[1] = m_frame[0];



    return valid;
}