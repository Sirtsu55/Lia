#include "Utils/ScopedTimer.h"
#include "Logger.h"

ScopedTimer::ScopedTimer(const char* Name, bool logtoconsole)
	:m_StartTime(std::chrono::steady_clock::now()), m_TimerName(Name), LogToConsole(logtoconsole)
{
}


ScopedTimer::~ScopedTimer()
{
	std::chrono::steady_clock::time_point EndTime = std::chrono::steady_clock::now();
	if (LogToConsole)
	{
		std::chrono::duration<double, std::milli> Duration = (EndTime - m_StartTime);

		Log::GetCoreLogger()->info("[TIMER]  [{0}][{1}:MS]", m_TimerName, Duration.count());
	}
	long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch().count();
	long long end = std::chrono::time_point_cast<std::chrono::microseconds>(EndTime).time_since_epoch().count();


	TimerWriter::WriteToFile(m_TimerName, std::this_thread::get_id(), start, end);
}



