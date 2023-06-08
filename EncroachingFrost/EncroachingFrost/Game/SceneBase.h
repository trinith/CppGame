#pragma once

#include "IScene.h"

#include <memory>
#include <vector>

namespace GhettoEngine
{

	class SceneBase : public IScene
	{
	public:
		virtual void Initialize() override
		{
			m_sceneComplete = false;

			OnInitialize();
		}

		virtual void Uninitialize() override
		{
			OnUninitialize();
		}

		virtual void FixedUpdate(const GameTime& gameTime) final
		{
			OnFixedUpdate(gameTime);

			for (auto&& controller : _controllers)
				controller->FixedUpdate(gameTime);
		}

		virtual void Update(const GameTime& gameTime) final
		{
			OnUpdate(gameTime);

			for (auto&& controller : _controllers)
				controller->Update(gameTime);
		}

		virtual void PreDraw(const GameTime& gameTime) final
		{
			for (auto&& view : _views)
				view->PreDraw(gameTime);

			OnPreDraw(gameTime);
		}

		virtual void Draw(const GameTime& gameTime) final
		{
			for (auto&& view : _views)
				view->Draw(gameTime);

			OnDraw(gameTime);
		}

		virtual bool IsComplete() const override final
		{
			return m_sceneComplete;
		}

		virtual void EndScene() override final
		{
			m_sceneComplete = true;
		}

		virtual std::optional<std::reference_wrapper<IScene>> GetNextScene() const override final
		{
			return _nextScene;
		}

		virtual void SetNextScene(std::optional<std::reference_wrapper<IScene>> nextScene) override final
		{
			_nextScene = nextScene;
		}

	protected:
		void ClearControllers()
		{
			_controllers.clear();
		}

		template <typename TController, typename... TArgs>
		void RegisterController(TArgs&&... args)
		{
			_controllers.emplace_back(std::make_unique<TController>(std::forward<TArgs>(args)...));
		}

		void ClearViews()
		{
			_views.clear();
		}

		template <typename TView, typename... TArgs>
		void RegisterView(TArgs&&... args)
		{
			_views.emplace_back(std::make_unique<TView>(std::forward<TArgs>(args)...));
		}

		virtual void OnInitialize() { }
		virtual void OnUninitialize() { }

		virtual void OnFixedUpdate(const GameTime& gameTime) { }
		virtual void OnUpdate(const GameTime& gameTime) { }

		virtual void OnPreDraw(const GameTime& gameTime) { }
		virtual void OnDraw(const GameTime& gameTime) { }

	private:
		bool m_sceneComplete = false;
		std::optional<std::reference_wrapper<IScene>> _nextScene;

		std::vector<std::unique_ptr<IController>> _controllers;
		std::vector<std::unique_ptr<IView>> _views;
	};

}