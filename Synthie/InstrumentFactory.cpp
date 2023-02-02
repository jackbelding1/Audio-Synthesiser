#include "stdafx.h"
#include "InstrumentFactory.h"

void CInstrumentFactory::SetNote(CNote* note)
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

        if (name == "s0")
        {
            value.ChangeType(VT_R8);
            m_sends[0] = value.dblVal;
        }
        else if (name == "s1")
        {
            value.ChangeType(VT_R8);
            m_sends[1] = value.dblVal;
        }
    }
}

CInstrumentFactory::CInstrumentFactory()
{
    m_sends[0] = 1.0;
	for (int i = 1; i < NUMEFFECTSCHANNELS; i++)
	{
		m_sends[i] = 0.0;
	}
}

CInstrumentFactory::~CInstrumentFactory()
{
}
