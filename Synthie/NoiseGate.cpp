#include "stdafx.h"
#include "NoiseGate.h"

CNoiseGate::CNoiseGate()
{
	m_threshold = -3;
	m_attack = 0.5;
	m_release = 0.5;
	m_range = 1.0;
    m_open = true;
}

CNoiseGate::~CNoiseGate()
{
}

void CNoiseGate::SetNote(CNote* note)
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

        if (name == "thresh")
        {
            value.ChangeType(VT_R8);
            m_threshold = value.dblVal;
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
        else if (name == "range")
        {
            value.ChangeType(VT_R8);
            m_range = value.dblVal;
        }
    }

}

void CNoiseGate::Start()
{
    m_time = 0.0;
}

void CNoiseGate::Process(double* inputFrame, double* outputFrame)
{
	for (int i = 0; i < 2; i++)
	{
        double dB;
        int neg = inputFrame[i] < 0 ? -1 : 1;
        dB = 20 * log10(inputFrame[i] * neg);


        if (dB < m_threshold)
        {
            if (m_open)
            {
                // close the gate
                m_open = false;
                // start the timer for attack
                m_time = 0.0;
                // write this frame to output
                outputFrame[i] += inputFrame[i];
            }
            else
            {
                // gate is closed
                if (m_time < m_attack)
                {
                    // we are in the attack phase
                    outputFrame[i] += inputFrame[i] * (1 - ((1 - m_range) * (m_time / m_attack)));
                    // advance the timer
                    m_time += GetSamplePeriod();
                }
                else
                {
                    // apply the range and write to output
                    outputFrame[i] += inputFrame[i] * m_range;
                }
            }
            /*outputFrame[i] += inputFrame[i] * m_range;*/
        }
        else
        {
            // decibels are exceeding the threshold
            if (m_open)
            {
                if (m_time > 0)
                {
                    // we are in the release period
                    outputFrame[i] += inputFrame[i] * (m_range +
                        ((1 - m_range) * ((m_release - m_time) / m_release)));
                    // subtract from the timer
                    m_time -= GetSamplePeriod();
                }
                else
                {
                    // write the input to the output
                    outputFrame[i] += inputFrame[i];
                }
            }
            else
            {
                // open the gate
                m_open = true;
                // start the timer for release 
                m_time = m_release;
                // apply the range and write to output
                outputFrame[i] += inputFrame[i] * m_range;
            }
        }
	}
}

bool CNoiseGate::Generate()
{
	return false;
}
