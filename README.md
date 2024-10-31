# Custom 2D game engine
Amugen is a custom 2D game engine, that I have developed in C++. This project really widened my perspective on game development and gave me a deeper understanding and appreciation for what goes on behind the scenes of bigger game engines.

## Details

The backbone of any engine are the entities for your game, in Amugen I use the game object component system for its simplicity and ease of use (inspired by the unit prefab concept).
Every game object needs components, which can be attached to game objects upon creation through a templated method like so
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
The engine uses a scene graph to determine positions and uses a game object component system. The rendering, input and audio is all handled by SDL. To handle the mathematics and positions behind the scene graph I am using GLM.

Most dependecies for rendering are nicely put away in RAII wrappers. The command pattern is used to provide an easy way for the user to handle input. Audio, provided through a service locator, is managed on a seperate thread to not uphold the main threads update loop.

Through the component system the user has access to the update loop and can define their own unique behaviour. Some pre-defined components include RenderComponent, TextComponent, TransformComponent, CollisionComponent. The collision system uses a simple distance check and triggers the appropriate methods. To decouple as much as possible but still allow the components to communicate with one another, the Subject-Observer relationship is used.
All of the used patterns are applied from the book "Game Programming Patterns" by Bob Nystrom.

The engine is set up using CMake and can be deployed as a github submodule.

Troughout the project I followed the C++ Core Guidelines and coding standards. Next to that I applied guidelines from the book "Beautiful C++" by J. Guy Davidson / Kate Gregory. It was a great guide and learner throughout the project.

