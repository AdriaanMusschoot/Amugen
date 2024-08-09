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
		explicit Amugen(std::filesystem::path const& dataPath, std::string_view const& windowName, int width, int height);
		~Amugen();
		void Run();
		void RunOneFrame();

		Amugen(Amugen const&) = delete;
		Amugen(Amugen&&) = delete;
		Amugen& operator=(Amugen const&) = delete;
		Amugen& operator=(Amugen&&) = delete;
	private:
		SDL_Window* m_WindowPtr{};
		bool m_ShouldQuit{};
	};
}

#endif //AMU_AMUGEN_H