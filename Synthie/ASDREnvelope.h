#pragma once
#include "AudioNode.h"
class CASDREnvelope : public CAudioNode
{
public:
	CASDREnvelope();
	~CASDREnvelope();

	double GetTime() { return m_time; }
	CAudioNode* GetSource() { return m_source; }
	void SetSource(CAudioNode* const& source) { m_source = source; }
	void SetDuration(double d) { m_duration = d; }
	virtual void Start();
	virtual bool Generate();
	void SetAttack(double attack) { m_attack = attack; }
	void SetRelease(double release) { m_release = release; }
	void SetDecay(double release) { m_decay = release; }
	void SetSustain(double release) { m_sustain = release; }

	double GetDuration() { return m_duration; }

private:
	double m_decay;
	double m_sustain;
	double m_duration;
	double m_time;
	double m_attack;
	double m_release;
	CAudioNode* m_source;
};

