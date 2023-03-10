#pragma once
#include <string>
class CNote
{
public:
	CNote();
	virtual ~CNote();
	int Measure() const { return m_measure; }
	double Beat() const { return m_beat; }
	const std::wstring &Instrument() const { return m_instrument; }
	std::wstring &Name()  { return m_name; }
	IXMLDOMNode *Node() { return m_node; }
	void XmlLoad(IXMLDOMNode * xml, std::wstring & instrument, std::wstring & name);
	bool operator<(const CNote &b);
private:
	std::wstring m_instrument;
	std::wstring m_name;
	int m_measure;
	double m_beat;
	CComPtr<IXMLDOMNode> m_node;
};

