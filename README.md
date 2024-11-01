# Custom 2D game engine
Amugen is a custom 2D game engine, that I have developed in C++. This project really widened my perspective on game development and gave me a deeper understanding and appreciation for what goes on behind the scenes of bigger game engines.

## Details
All the utilities provided by the engine are in the namespace amu, to allow the user to seperate the game from the engine.

To start of the user needs to fill in its detail for main. My implementation for pacman looked like the following.
```cpp
#include "SceneManager.h"
#include "LoadFunctions.h"
#include "Configuration.h"

namespace fs = std::filesystem;

int main(int, char*[]) 
{
	fs::path data_location = "./Resources/";
	if(!fs::exists(data_location))
		data_location = "../Resources/";

	amu::Amugen engine(data_location, pacman::config::WINDOW_WIDTH, pacman::config::WINDOW_HEIGHT);

	amu::SceneManager::GetInstance().CreateScene(pacman::tags::MAIN_SCENE, pacman::LoadMainScene);
	amu::SceneManager::GetInstance().CreateScene(pacman::tags::MENU_SCENE, pacman::LoadMenuScene);
	amu::SceneManager::GetInstance().CreateScene(pacman::tags::HIGHSCORE_SCENE, pacman::LoadHighscoreScene);

	amu::SceneManager::GetInstance().SetCurrentScene(pacman::tags::MENU_SCENE);

	engine.Run();

    return 0;
}
```
There is one scene current that references one from a vector, this way only one scene is updated and rendered at the time. 
This allows me to easily switch between existing scene without loading a whole new scene everytime.
The user has to create at least one scene and provide a method that takes in the scene as an argument to add game objects to.
```cpp
void amu::SceneManager::CreateScene(std::string_view const& name, std::function<void(Scene*)> const& loadScene)
{
	std::unique_ptr sceneUPtr = std::make_unique<Scene>(name);
	loadScene(sceneUPtr.get());
	m_ScenesUPtrVec.emplace_back(std::move(sceneUPtr));
}
```

The backbone of any game engine is the entities for your game, in Amugen I use the game object component system for its simplicity and ease of use (inspired by the unit prefab concept).
Every game object needs components, the user can create their own version of these game objects by inheriting from amu::Component, which can be attached to game objects upon creation through a templated method like so
```cpp
template <typename T, typename... Args>
T* AddComponent(Args&&... args)
{
	if (not ComponentAdded<T>())
	{
		m_ComponentUPtrVec.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
		return dynamic_cast<T*>(m_ComponentUPtrVec[std::ssize(m_ComponentUPtrVec) - 1].get());
	}
	return nullptr;
}
```
Here I don't allow for multiple components to be added. If it is really the case that you needed the same component twice, you can make use of the engine's scene graph and parent a second object (containing that double component) to the first one. To handle the mathematics and positions behind the scene graph the engine uses GLM. 
Once you have hooked up all the logic to the game object you'll have to hand it of to one of the scenes. This should be done in the method provided to create the scene like so.
```cpp
amu::SceneManager::GetInstance().CreateScene(pacman::tags::MAIN_SCENE, pacman::LoadMainScene);

void LoadMainScene(amu::Scene* scenePtr)
{
	std::unique_ptr fpsCounterUPtr{ std::make_unique<amu::GameObject>() };
	fpsCounterUPtr->AddComponent<amu::TransformComponent>(fpsCounterUPtr.get(), glm::vec2{ 50 , 50 });
	fpsCounterUPtr->AddComponent<amu::TextComponent>(fpsCounterUPtr.get(), "60", resources::font::LINGUA, 36);
	fpsCounterUPtr->AddComponent<FPSComponent>(fpsCounterUPtr.get());

	scenePtr->Add(std::move(fpsCounterUPtr));
}
```

The rendering, input and audio are all handled by SDL. All of these dependencies are nicely put away into RAII wrappers. Here is an example of the sound effect:
```cpp
#ifndef AMU_SOUND_WRAPPER_H
#define AMU_SOUND_WRAPPER_H
#include <string>
struct Mix_Chunk;
namespace amu
{
	class SoundEffect final
	{
	public:
		explicit SoundEffect(std::string_view const& fullPath);
		~SoundEffect();

		SoundEffect(SoundEffect const&) = delete;
		SoundEffect(SoundEffect&&) = delete;
		SoundEffect& operator= (SoundEffect const&) = delete;
		SoundEffect& operator= (SoundEffect&&) = delete;

		void PlaySoundEffect(int volume, int loops);
		void StopSoundEffect();
	private:
		std::string const m_FilePath{};
		Mix_Chunk* m_SoundEffectPtr{};
		int m_Channel{};
	};
}
#endif
```
The command pattern is used to provide an easy way for the user to handle input. You need to add a command like so. 
```cpp
std::unique_ptr downCommandKeyUPtr{ std::make_unique<MovePacmanCommand>(pacmanUPtr.get(), config::VEC_DOWN) };
inputManager.AddCommandKeyboard(SDL_SCANCODE_S, InpMan::InputState::Pressed, std::move(downCommandKeyUPtr));
```
There is a pure virtual method to override for the user to implement some logic to a binding. A basic game object command is also present to let the user apply it directly on a game object.  
```cpp
#ifndef AMU_COMMANDS_H
#define AMU_COMMANDS_H

namespace amu
{
	//is only interface (no ctor or rule of 5)
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

}

#endif //AMU_COMMANDS_H
```



Audio, provided through a service locator, is managed on a seperate thread to not uphold the main threads update loop.

Through the component system the user has access to the update loop and can define their own unique behaviour. Some pre-defined components include RenderComponent, TextComponent, TransformComponent, CollisionComponent. By inheriting from any of these or the base component the user can create any behaviour. 

The collision system uses a simple distance check and triggers the appropriate methods. 

To decouple as much as possible but still allow the components to communicate with one another, the Subject-Observer relationship is used.

```cpp
#ifndef AMU_IOBSERVER_H
#define AMU_IOBSERVER_H
namespace amu
{
	class Subject;
	class IObserver
	{
	public:
		virtual ~IObserver() = default;

		using Event = int;
		virtual void OnNotify(Event eventType, Subject* subjectPtr) = 0;
		virtual void NotifyDestruction() {};
	private:
	};
}
#endif //AMU_IOBSERVER_H
```
All of the used patterns are applied from the book "Game Programming Patterns" by Bob Nystrom.

The engine is set up using CMake and can be deployed as a github submodule.
For an example of how the engine can be used check out: https://github.com/AdriaanMusschoot/Pacman. 

Troughout the project I followed the C++ Core Guidelines and coding standards. Next to that I applied guidelines from the book "Beautiful C++" by J. Guy Davidson / Kate Gregory. It was a great guide and learner throughout the creation of this engine.

