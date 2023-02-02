#pragma once
#include "AudioNode.h"
#include <vector>

const int QUEUESIZE = 200000;

class CASDREFilterEnvelope :
	public CAudioNode
{
public:
	CASDREFilterEnvelope();
	~CASDREFilterEnvelope();

	CAudioNode* GetSource() { return m_source; }
	void SetSource(CAudioNode* const& source) { m_source = source; }
	void SetDuration(double d) { m_duration = d; }
	virtual bool Generate() override;
	virtual void Start();
	void SetAttack(double attack) { m_attack = attack; }
	void SetRelease(double release) { m_release = release; }
	void SetFreq(double freq) { m_freq = freq; }
	void SetBW(double bw) { m_bw = bw; };
	short RangeBound(double d);
	void SetTime(double time) { m_time = time; }
private:
	double m_freq;
	double m_bw;
	double m_duration;
	double m_time;
	double m_attack;
	double m_release;
	CAudioNode* m_source;
	std::vector<double> queueInput;
	std::vector<double> queueOutput;

	// Write Location
	int wrloc;

};

