#ifndef TIMER_H
#define TIMER_H
#include <Windows.h>
class Timer
{
	static __int64 m_prevFrame;
	static __int64 m_currentFrame;
	static __int64 m_freq;
	static float m_deltatime;
public :
	static void Update();
	static float GetDeltaTime();

};
#endif