#include "Timing.h"

Timing::Timing()
{
	m_fpsCount = 0;
	m_fpsLast = 0;
	m_deltaTime = 0;
	m_currentTime = SDL_GetTicks();
	m_lastTime = m_currentTime;
	m_fpsStart = m_currentTime;
}

void Timing::Tick()
{
	m_currentTime = SDL_GetTicks();
	m_deltaTime = (float)(m_currentTime - m_lastTime) / 1000.0f;
	if (m_fpsStart + 1000 <= m_currentTime)
	{
		m_fpsLast = m_fpsCount;
		m_fpsCount = 0;
		m_fpsStart = m_currentTime;
	}
	else
	{
		m_fpsCount++;
	}
	m_lastTime = m_currentTime;
}

void Timing::Reset()
{
	m_fpsCount = 0;  // Reset the FPS count as well
	m_fpsLast = 0;   // Optionally reset last FPS as well
	m_deltaTime = 0; // Reset delta time
	m_currentTime = 0; // Explicitly reset current time to 0
	m_lastTime = SDL_GetTicks(); // Reset last time to the current tick
	m_fpsStart = SDL_GetTicks(); // Reset FPS start time
}