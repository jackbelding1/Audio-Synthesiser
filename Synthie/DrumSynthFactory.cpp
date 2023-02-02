#include "stdafx.h"
#include "DrumSynthFactory.h"
#include "Notes.h"


void CDrumSynthFactory::SetNote(CNote* note)
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
            m_envelope.SetDuration(value.dblVal * (NUM_SECS_IN_MINUTE / m_bpm));

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
        else if (name == "f_atk")
        {
            value.ChangeType(VT_R8);
            m_fAttack = value.dblVal;
        }
        else if (name == "f_rls")
        {
            value.ChangeType(VT_R8);
            m_fRelease = value.dblVal;

        }
        else if (name == "freq")
        {
            // set filter freq
            value.ChangeType(VT_R8);
            m_Filterfreq = value.dblVal;
        }
        else if (name == "bw")
        {
            // set bandwidth
            value.ChangeType(VT_R8);
            m_bw = value.dblVal;
        }

    }
    
    
}

CDrumSynthFactory::CDrumSynthFactory()
{
    m_bw = 0.01;
    m_Filterfreq = 0.001;
    m_fAttack = 0.05;
    m_fRelease = 0.05;
}

CDrumSynthFactory::~CDrumSynthFactory()
{
}

CDrumSynth* CDrumSynthFactory::CreateInstrument()
{
    CDrumSynth* instrument = new CDrumSynth(m_bpm, m_freq, m_envelope.GetDuration());
    instrument->SetAttack(m_attack);
    instrument->SetRelease(m_release);
    instrument->SetSustain(m_sustain);
    instrument->SetDecay(m_decay);
    instrument->SetTime(0.0);
    instrument->SetBW(m_bw);
    instrument->SetFilterAttack(m_fAttack);
    instrument->SetFilterRelease(m_fRelease);
    instrument->SetFilterFreq(m_Filterfreq);

    // set sends
    for (int i = 0; i < NUMEFFECTSCHANNELS; i++)
    {
        instrument->SetSend(i, Send(i));
    }

    return instrument;
}
