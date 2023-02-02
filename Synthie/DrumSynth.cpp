#include "stdafx.h"
#include "DrumSynth.h"

CDrumSynth::CDrumSynth()
{

}

CDrumSynth::CDrumSynth(double bpm, double freq, double duration)
{
	m_duration = duration;
	m_envelope.SetDuration(duration);
	m_pitchmod.SetDuration(duration);
	//m_filterEnvelope.SetDuration(duration);
	m_pitchmod.SetFreq(freq);
	m_bpm = bpm;
}

CDrumSynth::~CDrumSynth()
{
}

void CDrumSynth::SetNote(CNote* note)
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

        if (name == "duration")
        {
            value.ChangeType(VT_R8);
            SetDuration(value.dblVal);
            m_envelope.SetDuration(value.dblVal * (NUM_SECS_IN_MINUTE / m_bpm));
            m_filterEnvelope.SetDuration(value.dblVal * (NUM_SECS_IN_MINUTE / m_bpm));

        }
    }

}


void CDrumSynth::Start()
{
    m_time = 0.0;
	m_pitchmod.Start();
	m_pitchmod.SetSine(&m_sinewave);
	m_filterEnvelope.SetSource(/*&m_sinewave*/&m_envelope);
	m_envelope.SetSource(/*&m_filterEnvelope*/&m_sinewave);
	m_envelope.SetSampleRate(GetSampleRate());
	m_envelope.Start();
}

bool CDrumSynth::Generate()
{
	m_pitchmod.Generate();

	// Tell the component to generate an audio 
	//bool valid = m_envelope.Generate();
	bool valid = m_filterEnvelope.Generate();
	// Read the component's sample and make it our resulting frame.
	m_frame[0] = m_envelope.Frame(0);
	m_frame[1] = m_envelope.Frame(1);

	// Update time
	m_time += GetSamplePeriod();

	// We return true until the time reaches the duration returned by the AR object.
	return valid;
}
