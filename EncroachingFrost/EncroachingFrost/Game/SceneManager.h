#pragma once

#include "Assert.h"
#include "IScene.h"
#include "ControllerBase.h"
#include "ViewBase.h"
#include "OptionalRef.h"

#include <memory>
#include <unordered_map>

namespace GhettoEngine
{

	class SceneManager : public ControllerBase, public ViewBase
	{
	public:
		using SceneId = std::string;

		template <typename TScene, typename... TArgs>
		void RegisterScene(const SceneId& id, TArgs&&... args)
		{
			ASSERT_MSG(_scenes.find(id) == _scenes.end(), "Scene already registered.");

			std::unique_ptr<TScene> newScene = std::make_unique<TScene>(std::forward<TArgs>(args)...);
			auto emplaceResult = _scenes.emplace(id, std::move(newScene));

			ASSERT(emplaceResult.second);
		}

		void SetCurrentScene(const SceneId& id)
		{
			auto findResult = _scenes.find(id);
			ASSERT(findResult != _scenes.end());

			SetNextScene(*findResult->second);
		}

		OptionalRef<IScene> GetScene(const SceneId& id) const
		{
			auto findResult = _scenes.find(id);
			if (findResult == _scenes.end())
				return std::nullopt;

			IScene& scene = *findResult->second;
			return scene;
		}

		OptionalRef<IScene> GetCurrentScene() const
		{
			return _currentScene;
		}

		virtual void OnFixedUpdate(const GameTime& gameTime) override
		{
			if (_currentScene)
				_currentScene->get().FixedUpdate(gameTime);
		}

		virtual void OnUpdate(const GameTime& gameTime) override
		{
			if (!_currentScene)
				return;

			IScene& currentScene = _currentScene->get();
			currentScene.Update(gameTime);

			if (currentScene.IsComplete())
				SetNextScene(currentScene.GetNextScene());
		}

		virtual void OnPreDraw(const GameTime& gameTime) override
		{
			if (_currentScene)
				_currentScene->get().PreDraw(gameTime);
		}

		virtual void OnDraw(const GameTime& gameTime) override
		{
			if (_currentScene)
				_currentScene->get().Draw(gameTime);
		}

	private:
		void SetNextScene(OptionalRef<IScene> nextScene)
		{
			if (_currentScene)
				_currentScene->get().Uninitialize();

			_currentScene = nextScene;

			if (_currentScene)
				_currentScene->get().Initialize();
		}

		std::unordered_map<SceneId, std::unique_ptr<IScene>> _scenes;
		OptionalRef<IScene> _currentScene;
	};

}