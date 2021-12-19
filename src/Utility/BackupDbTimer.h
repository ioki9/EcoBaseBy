#include <wx/timer.h>
#include <cstdint>
class BackupDbTimer : public wxTimer
{
public:
	BackupDbTimer(long timeElapsed = 0, int intervalMsec = 300000, long maxTimerInterval = 7200000);
	~BackupDbTimer();
protected:
	virtual void Notify() wxOVERRIDE;
	int m_interval{};
	uint_fast8_t m_hCount{ 0 };
	unsigned int m_hCountDest{ };
};