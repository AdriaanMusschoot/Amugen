#ifndef AMU_GAME_TIME_H
#define AMU_GAME_TIME_H

#include <chrono>
#include "Singleton.h"

namespace pacman
{

	class GameTime final : public Singleton<GameTime>
	{
	public:
		void Update();
	
		double GetDeltaTime() const;
	private:
		friend class Singleton<GameTime>;
		GameTime() = default;
		std::chrono::high_resolution_clock::time_point m_PreviousTimePoint;
	
		double m_DeltaTime = 0;
	};

}

#endif //AMU_GAME_TIME_H