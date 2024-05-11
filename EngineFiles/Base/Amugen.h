#ifndef AMU_AMUGEN_H
#define AMU_AMUGEN_H

#include <string>
#include <functional>
#include <filesystem>

struct SDL_Window;

namespace amu
{

	class Amugen final
	{
	public:
		explicit Amugen(const std::filesystem::path& dataPath, int width, int height);
		~Amugen();
		void Run();
		void RunOneFrame();

		Amugen(const Amugen& other) = delete;
		Amugen(Amugen&& other) = delete;
		Amugen& operator=(const Amugen& other) = delete;
		Amugen& operator=(Amugen&& other) = delete;
	private:
		SDL_Window* m_WindowPtr{};
		bool m_ShouldQuit{};
	};
}

#endif //AMU_AMUGEN_H