#include "stdafx.h"
#include "Compressor.h"
#include <math.h>

CCompressor::CCompressor()
{
    m_threshold = 5.0;
    m_ratio = 1.0;
    m_attack = 0.5;
    m_release = 0.5;
    m_active = false;
}

CCompressor::~CCompressor()
{
}

void CCompressor::SetNote(CNote* note)
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
        else if (name == "ratio")
        {
            value.ChangeType(VT_R8);
            m_ratio = value.dblVal;
        }
    }
}

double dB_over = 0.0;
void CCompressor::Process(double* inputFrame, double* outputFrame)
{

    for (int i = 0; i < 2; i++)
    {
        double dB;
        int neg = inputFrame[i] < 0 ? -1 : 1;
        dB = 20 * log10(inputFrame[i] * neg);
        double newdB;
        double newSig;

        if (dB < m_threshold)
        {
            if (m_active)
            {
                // close the gate
                m_active = false;
                // start the timer for release
                m_time = m_release;
                // write this frame to output

                newdB = dB - (dB_over * m_ratio);
                newSig = pow(10, (newdB / 20)) * neg;
                outputFrame[i] += newSig;
            }
            else
            {
                // gate is closed
                if (m_time > 0)
                {
                    // we are in the release phase
                    //outputFrame[i] += inputFrame[i] * (1 - ((1 - m_ratio) * (m_time / m_attack)));
                    // advance the timer


                    newdB = dB - (dB_over * m_ratio);
                    newSig = pow(10, (newdB / 20)) * neg;
                    outputFrame[i] += newSig;

                    //newdB = m_threshold + (dB * ((m_ratio +
                    //    ((1 - m_ratio) * ((m_release - m_time) / m_release)))));
                    //newSig = neg * pow(10, (newdB / 20));
                    //outputFrame[i] += newSig;

                    //outputFrame[i] += inputFrame[i] * (m_ratio +
                    //    ((1 - m_ratio) * ((m_release - m_time) / m_release)));
                    m_time -= GetSamplePeriod();
                }
                else
                {
                    // write to output
                    outputFrame[i] += inputFrame[i];
                }
            }
            /*outputFrame[i] += inputFrame[i] * m_range;*/
        }
        else
        {
            // decibels are exceeding the threshold
            dB_over = dB - m_threshold;

            if (m_active)
            {
                if (m_time < m_attack)
                {
                    // we are in the attack period
                    newdB = (dB_over * m_ratio) + m_threshold;
                    newSig = pow(10, (newdB / 20)) * neg;
                    outputFrame[i] += newSig;
                    //outputFrame[i] += inputFrame[i] * (1 - ((1 - m_ratio) * (m_time / m_attack)));

                    // advance the timer
                    m_time += GetSamplePeriod();
                }
                else
                {
                    newdB = (dB_over * m_ratio) + m_threshold;
                    newSig = pow(10, (newdB / 20)) * neg;
                    outputFrame[i] += newSig;
                    // write the input to the output
                    //outputFrame[i] += inputFrame[i] * m_ratio;
                }
            }
            else
            {
                // open the gate
                m_active = true;
                // start the timer for release 
                m_time = 0.0;
                // write to output
                outputFrame[i] += inputFrame[i];
            }
        }
    }
}

void CCompressor::Start()
{
    m_time = 0.0;
}

bool CCompressor::Generate()
{
    return false;
}
