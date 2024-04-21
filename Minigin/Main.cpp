#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Base/Minigin.h"
#include "Singletons/SceneManager.h"
#include "Singletons/InputManager.h"
#include "Base/GameObject.h"
#include "Commands/MoveCommand.h"
#include "Commands/DamageCommand.h"
#include "Commands/ScoreCommand.h"
#include "Parameters.h"
#include <filesystem>

#include "Components/FPSComponent.h"
#include "Components/TextComponent.h"
#include "Components/TextureComponent.h"
#include "Components/HealthComponent.h"
#include "Components/DisplayComponent.h"
#include "Windows.h"
#include "Xinput.h"
#include <iostream>
namespace fs = std::filesystem;

// Defining our achievements
enum EAchievements
{
	ACH_WIN_ONE_GAME = 0,
	ACH_WIN_100_GAMES = 1,
	ACH_TRAVEL_FAR_ACCUM = 2,
	ACH_TRAVEL_FAR_SINGLE = 3,
};

void load()
{
	auto& scene = amu::SceneManager::GetInstance().CreateScene("Programming 4 Assignment");

	//////////////////////////////////////////
	///////////////BACKGROUND + FPS
	//////////////////////////////////////////
	
	std::unique_ptr backgroundUPtr{ std::make_unique<amu::GameObject>() };
	backgroundUPtr->AddComponent<amu::TransformComponent>(backgroundUPtr.get(), glm::vec2{0, 0});
	backgroundUPtr->AddComponent<amu::RenderComponent>(backgroundUPtr.get(), "background.tga");
	
	std::unique_ptr daeLogoUPtr{ std::make_unique<amu::GameObject>() };
	daeLogoUPtr->AddComponent<amu::TransformComponent>(daeLogoUPtr.get(), glm::vec2{amu::WINDOW_WIDTH / 2 - 103, amu::WINDOW_HEIGHT / 2 - 24 });
	daeLogoUPtr->AddComponent<amu::RenderComponent>(daeLogoUPtr.get(), "logo.tga");
 	daeLogoUPtr->SetParent(backgroundUPtr.get(), false);

	std::unique_ptr titleUPtr{ std::make_unique<amu::GameObject>() };
	titleUPtr->AddComponent<amu::TransformComponent>(titleUPtr.get(), glm::vec2{ 80, 20 });
	titleUPtr->AddComponent<amu::TextComponent>(titleUPtr.get(), "Programming 4 Assignment", "Lingua.otf", 36);
 	titleUPtr->SetParent(backgroundUPtr.get(), false);
	
	std::unique_ptr fpsCounterUPtr{ std::make_unique<amu::GameObject>() };
	fpsCounterUPtr->AddComponent<amu::TransformComponent>(fpsCounterUPtr.get(), glm::vec2{ 0, 0 });
	fpsCounterUPtr->AddComponent<amu::TextComponent>(fpsCounterUPtr.get(), "60", "Lingua.otf", 36);
	fpsCounterUPtr->AddComponent<amu::FPSComponent>(fpsCounterUPtr.get());
 	fpsCounterUPtr->SetParent(backgroundUPtr.get(), false);

	scene.Add(std::move(backgroundUPtr));
	scene.Add(std::move(daeLogoUPtr));
	scene.Add(std::move(titleUPtr));
	scene.Add(std::move(fpsCounterUPtr));


	//////////////////////////////////////////
	///////////////UI COMPONENTS PACMAN
	//////////////////////////////////////////

	std::unique_ptr livesDisplayPacmanUPtr{ std::make_unique<amu::GameObject>() };
	livesDisplayPacmanUPtr->AddComponent<amu::TransformComponent>(livesDisplayPacmanUPtr.get(), glm::vec2{ 0, 50 });
	livesDisplayPacmanUPtr->AddComponent<amu::DisplayComponent>(livesDisplayPacmanUPtr.get(), "Lives: ");

	std::unique_ptr scoreDisplayPacmanUPtr{ std::make_unique<amu::GameObject>() };
	scoreDisplayPacmanUPtr->AddComponent<amu::TransformComponent>(scoreDisplayPacmanUPtr.get(), glm::vec2{ 0, 70 });
	scoreDisplayPacmanUPtr->AddComponent<amu::DisplayComponent>(scoreDisplayPacmanUPtr.get(), "Score: ");

	//////////////////////////////////////////
	///////////////PACMAN
	//////////////////////////////////////////

	std::unique_ptr pacmanUPtr{ std::make_unique<amu::GameObject>() };
	pacmanUPtr->AddComponent<amu::TransformComponent>(pacmanUPtr.get(), glm::vec2{amu::WINDOW_WIDTH / 2 - 4, amu::WINDOW_HEIGHT / 2 - 4 });
	pacmanUPtr->AddComponent<amu::RenderComponent>(pacmanUPtr.get(), "PacMan.png");
	pacmanUPtr->AddComponent<amu::HealthComponent>(pacmanUPtr.get(), 3, 3);
	pacmanUPtr->AddComponent<amu::ScoreComponent>(pacmanUPtr.get(), 0);
	pacmanUPtr->GetComponent<amu::HealthComponent>()->AddObserver(livesDisplayPacmanUPtr->GetComponent<amu::DisplayComponent>());
	pacmanUPtr->GetComponent<amu::ScoreComponent>()->AddObserver(scoreDisplayPacmanUPtr->GetComponent<amu::DisplayComponent>());

	scene.Add(std::move(livesDisplayPacmanUPtr));
	scene.Add(std::move(scoreDisplayPacmanUPtr));

	//////////////////////////////////////////
	///////////////UI COMPONENTS BLUE GHOSTS
	//////////////////////////////////////////

	std::unique_ptr livesDisplayBlueGhostUPtr{ std::make_unique<amu::GameObject>() };
	livesDisplayBlueGhostUPtr->AddComponent<amu::TransformComponent>(livesDisplayBlueGhostUPtr.get(), glm::vec2{ 0, 90 });
	livesDisplayBlueGhostUPtr->AddComponent<amu::DisplayComponent>(livesDisplayBlueGhostUPtr.get(), "Lives: ");

	std::unique_ptr scoreDisplayBlueGhostUPtr{ std::make_unique<amu::GameObject>() };
	scoreDisplayBlueGhostUPtr->AddComponent<amu::TransformComponent>(scoreDisplayBlueGhostUPtr.get(), glm::vec2{ 0, 110 });
	scoreDisplayBlueGhostUPtr->AddComponent<amu::DisplayComponent>(scoreDisplayBlueGhostUPtr.get(), "Score: ");

	//////////////////////////////////////////
	///////////////BLUE GHOST
	//////////////////////////////////////////

	std::unique_ptr blueGhostUPtr{ std::make_unique<amu::GameObject>() };
	blueGhostUPtr->AddComponent<amu::TransformComponent>(blueGhostUPtr.get(), glm::vec2{amu::WINDOW_WIDTH / 2 - 4, amu::WINDOW_HEIGHT / 2 - 4 });
	blueGhostUPtr->AddComponent<amu::RenderComponent>(blueGhostUPtr.get(), "BlueGhost.png");
	blueGhostUPtr->AddComponent<amu::HealthComponent>(blueGhostUPtr.get(), 3, 3);
	blueGhostUPtr->AddComponent<amu::ScoreComponent>(blueGhostUPtr.get(), 0);
	blueGhostUPtr->GetComponent<amu::HealthComponent>()->AddObserver(livesDisplayBlueGhostUPtr->GetComponent<amu::DisplayComponent>());
	blueGhostUPtr->GetComponent<amu::ScoreComponent>()->AddObserver(scoreDisplayBlueGhostUPtr->GetComponent<amu::DisplayComponent>());

	scene.Add(std::move(livesDisplayBlueGhostUPtr));
	scene.Add(std::move(scoreDisplayBlueGhostUPtr));

	/////////////////////////////
	/////////Add commmands
	/////////////////////////////

	glm::vec2 right{ 1, 0  };
	glm::vec2 left{ -right };
	glm::vec2 up{ 0, -1 };
	glm::vec2 down{ -up };

	double speedPacman{ 50 };
	double speedBlueGhost{ speedPacman * 2 };
	amu::InputManager::GetInstance().AddCommandController(
		0, 
		XINPUT_GAMEPAD_DPAD_RIGHT,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveCommand>(pacmanUPtr.get(), right, speedPacman));

	amu::InputManager::GetInstance().AddCommandController(
		0,
		XINPUT_GAMEPAD_DPAD_LEFT,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveCommand>(pacmanUPtr.get(), left, speedPacman));

	amu::InputManager::GetInstance().AddCommandController(
		0,
		XINPUT_GAMEPAD_DPAD_UP,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveCommand>(pacmanUPtr.get(), up, speedPacman));

	amu::InputManager::GetInstance().AddCommandController(
		0,
		XINPUT_GAMEPAD_DPAD_DOWN,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveCommand>(pacmanUPtr.get(), down, speedPacman));

	amu::InputManager::GetInstance().AddCommandController(
		0,
		XINPUT_GAMEPAD_A,
		amu::InputManager::InputState::Released,
		std::make_unique<amu::DamageCommand>(pacmanUPtr.get(), 3));

	amu::InputManager::GetInstance().AddCommandController(
		0,
		XINPUT_GAMEPAD_B,
		amu::InputManager::InputState::Released,
		std::make_unique<amu::ScoreCommand>(pacmanUPtr.get(), 10));

	amu::InputManager::GetInstance().AddCommandKeyboard(
		SDLK_d,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveCommand>(blueGhostUPtr.get(), right, speedBlueGhost));

	amu::InputManager::GetInstance().AddCommandKeyboard(
		SDLK_a,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveCommand>(blueGhostUPtr.get(), left, speedBlueGhost));

	amu::InputManager::GetInstance().AddCommandKeyboard(
		SDLK_w,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveCommand>(blueGhostUPtr.get(), up, speedBlueGhost));

	amu::InputManager::GetInstance().AddCommandKeyboard(
		SDLK_s,
		amu::InputManager::InputState::Held,
		std::make_unique<amu::MoveCommand>(blueGhostUPtr.get(), down, speedBlueGhost));

	amu::InputManager::GetInstance().AddCommandKeyboard(
		SDLK_k,
		amu::InputManager::InputState::Released,
		std::make_unique<amu::DamageCommand>(blueGhostUPtr.get(), 3));

	amu::InputManager::GetInstance().AddCommandKeyboard(
		SDLK_i,
		amu::InputManager::InputState::Released,
		std::make_unique<amu::ScoreCommand>(blueGhostUPtr.get(), 10));

	scene.Add(std::move(pacmanUPtr));
	scene.Add(std::move(blueGhostUPtr));

	std::unique_ptr controllerExplainedUPtr{ std::make_unique<amu::GameObject>() };
	controllerExplainedUPtr->AddComponent<amu::TransformComponent>(controllerExplainedUPtr.get(), glm::vec2{ 0 , 170 });
	controllerExplainedUPtr->AddComponent<amu::TextComponent>(controllerExplainedUPtr.get(), "Use the D-Pad to move Pacman, A to lose a life, B to increase score", "Lingua.otf", 20);

	std::unique_ptr keyboardExplainedUPtr{ std::make_unique<amu::GameObject>() };
	keyboardExplainedUPtr->AddComponent<amu::TransformComponent>(keyboardExplainedUPtr.get(), glm::vec2{ 0, 190 });
	keyboardExplainedUPtr->AddComponent<amu::TextComponent>(keyboardExplainedUPtr.get(), "Use WASD to move Bluey, K to lose a life, I to increase score", "Lingua.otf", 20);

	scene.Add(std::move(controllerExplainedUPtr));
	scene.Add(std::move(keyboardExplainedUPtr));
}

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

	amu::Minigin engine(data_location);
	engine.Run(load);

    return 0;
}
