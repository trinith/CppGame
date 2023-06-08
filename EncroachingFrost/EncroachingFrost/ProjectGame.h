#pragma once

#include "WindowManager.h"

#include <Assets\AssetLoader.h>
#include <Assets\AssetManager.h>
#include <Game\GameBase.h>
#include <Game\SceneManager.h>
#include <Input\InputManager.h>
#include <Models\AbilityIconMap.h>
#include <Scenes\GameplayScene.h>

class ProjectGame : public GhettoEngine::GameBase
{
public:
	struct Constants
	{
		struct Scenes
		{
			inline static const GhettoEngine::SceneManager::SceneId Gameplay = "GameplayScene";
		};
	};

public:
	ProjectGame(WindowManager& windowManager)
		: _windowManager{ windowManager }
		, _inputManager{ windowManager }
		, _sceneManager{}
		, _assetManager{}
	{
	}

	virtual void OnGameStart() override
	{
		Assets::AssetLoader::LoadTextures(_assetManager);
		Assets::AssetLoader::LoadSpriteSheets(_assetManager);
		Assets::AssetLoader::LoadFonts(_assetManager);

		AbilityIconMap::Initialize();

		_sceneManager.RegisterScene<GameplayScene>(
			Constants::Scenes::Gameplay,
			_windowManager,
			_inputManager,
			_assetManager
		);

		_sceneManager.SetCurrentScene(Constants::Scenes::Gameplay);
	}

	virtual void OnFixedUpdate(const GhettoEngine::GameTime& gameTime) override
	{
		_sceneManager.FixedUpdate(gameTime);
	}

	virtual void OnUpdate(const GhettoEngine::GameTime& gameTime) override
	{
		_inputManager.Update(gameTime);
		_windowManager.Update(gameTime);

		_sceneManager.Update(gameTime);

		if (!_sceneManager.GetCurrentScene())
			CloseGame();

		if (!_windowManager.IsOpen())
			this->SetIsRunning(false);
	}

	virtual void OnPreDraw(const GhettoEngine::GameTime& gameTime) override
	{
		_sceneManager.PreDraw(gameTime);
	}

	virtual void OnDraw(const GhettoEngine::GameTime& gameTime) override
	{
		_sceneManager.Draw(gameTime);
	}

private:
	void CloseGame()
	{
		_windowManager.Close();
		this->SetIsRunning(false);
	}

	WindowManager& _windowManager;
	
	InputManager _inputManager;
	GhettoEngine::SceneManager _sceneManager;
	Assets::AssetManager _assetManager;
};