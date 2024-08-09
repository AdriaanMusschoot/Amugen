#ifndef AMU_GAME_TIME_H
#define AMU_GAME_TIME_H

#include <chrono>
#include "Singleton.h"

namespace amu
{

	class GameTime final : public Singleton<GameTime>
	{
	public:
		virtual ~GameTime() = default;

		GameTime(GameTime const&) = delete;
		GameTime(GameTime&&) = delete;
		GameTime& operator=(GameTime const&) = delete;
		GameTime& operator=(GameTime&&) = delete;

		void Update();
	
		double GetDeltaTime() const;
	private:
		friend class Singleton<GameTime>;
		explicit GameTime() = default;
		std::chrono::high_resolution_clock::time_point m_PreviousTimePoint;
	
		double m_DeltaTime = 0;
	};

}

#endif //AMU_GAME_TIME_H