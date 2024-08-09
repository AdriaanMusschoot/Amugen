#include <stdexcept>
#include <sstream>
#include <iostream>

#if WIN32
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#endif

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Amugen.h"
#include <thread>
#include "GameTime.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"

void LogSDLVersion(const std::string_view& message, const SDL_version& v)
{
#if WIN32
	std::cout << message << (int)v.major << "." << (int)v.minor << "." << (int)v.patch << "\n";
#endif
}

// Why bother with this? Because sometimes students have a different SDL version installed on their pc.
// That is not a problem unless for some reason the dll's from this project are not copied next to the exe.
// These entries in the debug output help to identify that issue.
void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	LogSDLVersion("We compiled against SDL version ", version);

	SDL_GetVersion(&version);
	LogSDLVersion("We linked against SDL version ", version);

	SDL_IMAGE_VERSION(&version);
	LogSDLVersion("We compiled against SDL_image version ", version);

	version = *IMG_Linked_Version();
	LogSDLVersion("We linked against SDL_image version ", version);

	SDL_TTF_VERSION(&version)
	LogSDLVersion("We compiled against SDL_ttf version ", version);

	version = *TTF_Linked_Version();
	LogSDLVersion("We linked against SDL_ttf version ", version);

	SDL_MIXER_VERSION(&version)
	LogSDLVersion("We compiled against SDL_mixer version ", version);

	version = *Mix_Linked_Version();
	LogSDLVersion("We linked against SDL_mixer version ", version);
}

amu::Amugen::Amugen(const std::filesystem::path &dataPath, std::string_view const& windowName, int width, int height)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	
	m_WindowPtr = SDL_CreateWindow(
		windowName.data(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL
	);

	if (m_WindowPtr == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_WindowPtr);
	ResourceManager::GetInstance().Init(dataPath);

	std::unique_ptr sdlLoggingSoundSystemUPtr{ std::make_unique<amu::LogSoundSystem>(std::make_unique<amu::SDLSoundSystem>()) };
	amu::ServiceLocator::GetInstance().RegisterSoundSystem(std::move(sdlLoggingSoundSystemUPtr));
}

amu::Amugen::~Amugen()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_WindowPtr);
	m_WindowPtr = nullptr;
	SDL_Quit();
}

void amu::Amugen::Run()
{
	ServiceLocator::GetInstance().GetSoundSystem()->SignalStart();

	while (not m_ShouldQuit)
	{
		RunOneFrame();
	}

	ServiceLocator::GetInstance().GetSoundSystem()->SignalEnd();
}

void amu::Amugen::RunOneFrame()
{
	GameTime::GetInstance().Update();

	SceneManager::GetInstance().Collision();

	m_ShouldQuit = !InputManager::GetInstance().ProcessInput();

	SceneManager::GetInstance().Update();

	Renderer::GetInstance().Render();
}