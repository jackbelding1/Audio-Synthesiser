#include "stdafx.h"
#include "WaveTable.h"
#include <cmath>
#include "audio/DirSoundSource.h"

bool CWaveTable::LoadFile(const char* filename, vector<short>* destination)
{

    CDirSoundSource m_file;
    if (!m_file.Open(filename))
    {
        CString msg = L"Unable to open audio file: ";
        msg += filename;
        AfxMessageBox(msg);
        return false;
    }

    for (int i = 0; i < m_file.NumSampleFrames(); i++)
    {
        short frame[2];
        m_file.ReadFrame(frame);
        destination->push_back(frame[0]);
    }

    m_file.Close();
    return true;
}
