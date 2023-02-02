#pragma once
#include <vector>
#include <string>

using namespace std;

class CWaveTable
{
private:

public:
	bool LoadFile(const char* filename, vector<short>* destination);

};

