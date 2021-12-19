#include "BackupDbTimer.h"
#include <wx/filename.h>
#include <wx/datetime.h>
#include "../Settings.h"

BackupDbTimer::BackupDbTimer(long timeElapsed, int intervalMsec, long maxTimerInterval) : wxTimer(), m_interval{intervalMsec}
{
	StartOnce(m_interval - (timeElapsed % m_interval));
	m_hCount = ((timeElapsed % maxTimerInterval) / m_interval);
	m_hCountDest = maxTimerInterval / m_interval;
}
BackupDbTimer::~BackupDbTimer()
{
}

void BackupDbTimer::Notify()
{

	wxCopyFile(wxGetCwd() + "/passport_data.db", wxGetCwd() + "/Backup/data_backup-10min.db", 1);
	m_hCount++;
	if (m_hCount >= m_hCountDest)
	{
		wxCopyFile(wxGetCwd() + "/passport_data.db", wxGetCwd() + "/Backup/databackup-2hrs.db", 1);
		m_hCount = 0;
	}
		

	Start(m_interval, true);
}