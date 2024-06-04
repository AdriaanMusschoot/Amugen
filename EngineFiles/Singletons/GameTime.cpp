#include "GameTime.h"

void amu::GameTime::Update()
{
	const auto currentTimePoint = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<double>(currentTimePoint - m_PreviousTimePoint).count();
	m_PreviousTimePoint = currentTimePoint;

	if (m_DeltaTime >= 0.016)
	{
		m_DeltaTime = 0.016;
	}
}

double amu::GameTime::GetDeltaTime() const
{
	return m_DeltaTime;
}
