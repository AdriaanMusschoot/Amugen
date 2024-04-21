#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Base/Amugen.h"
#include "Singletons/SceneManager.h"
#include "Singletons/InputManager.h"
#include "Base/GameObject.h"
#include <filesystem>
#include "Windows.h"
#include "Xinput.h"
#include <iostream>

namespace fs = std::filesystem;

int main(int, char*[]) 
{
	//thx mat for the console fix
#ifdef WIN32
	if (AllocConsole()) 
	{
		FILE* pEmpty;
		freopen_s(&pEmpty, "CONOUT$", "w", stdout);
		freopen_s(&pEmpty, "CONOUT$", "w", stderr);
	}
#endif
	
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	amu::Amugen engine(data_location, 224 * 3, 288 * 3);
	engine.Run();

    return 0;
}
