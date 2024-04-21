#include "Singletons/Time.h"

void GameTime::Update()
{
	const auto currentTimePoint = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<double>(currentTimePoint - m_PreviousTimePoint).count();
	m_PreviousTimePoint = currentTimePoint;
}

double GameTime::GetDeltaTime() const
{
	return m_DeltaTime;
}
