#pragma once

#include "GameTime.h"
#include "IController.h"
#include "IScene.h"
#include "IView.h"

#include <atomic>
#include <thread>
#include <vector>

namespace GhettoEngine
{

	class GameBase : public IController, public IView
	{
	public:
		bool GetIsRunning() const { return m_isRunning; }
		void SetIsRunning(bool value) { m_isRunning = value; }

		float GetFixedUpdateRate() const { return m_fixedUpdateRate; }
		void SetFixedUpdateRate(float updatesPerSecond) { m_fixedUpdateRate = updatesPerSecond; }

		void Run()
		{
			using Clock = std::chrono::high_resolution_clock;

			std::chrono::duration<float> accumulatedTime{ 0.0f };

			m_isRunning = true;

			OnGameStart();

			auto start = Clock::now();

			while (m_isRunning)
			{
				auto now = Clock::now();
				std::chrono::duration<float> elapsed = now - start;
				accumulatedTime += elapsed;

				std::chrono::duration<float> fixedUpdateDuration{ m_fixedUpdateRate };
				GameTime fixedUpdateGameTime{ fixedUpdateDuration };

				while (m_isRunning && accumulatedTime > fixedUpdateDuration)
				{
					FixedUpdate(fixedUpdateGameTime);
					accumulatedTime -= fixedUpdateDuration;
				}

				const GameTime gameTime{ elapsed };
				Update(gameTime);
				PreDraw(gameTime);
				Draw(gameTime);

				start = now;

				// Force a 1ms sleep so we don't pin the processor. Might be a better way to do this...
				std::this_thread::sleep_for(std::chrono::milliseconds{ 1 });
			}

			OnGameEnd();
		}

		virtual void FixedUpdate(const GameTime& gameTime) final
		{
			OnFixedUpdate(gameTime);
		}

		virtual void Update(const GameTime& gameTime) final
		{
			OnUpdate(gameTime);
		}

		virtual void PreDraw(const GameTime& gameTime) final
		{
			OnPreDraw(gameTime);
		}

		virtual void Draw(const GameTime& gameTime) final
		{
			OnDraw(gameTime);
		}
	protected:

		virtual void OnGameStart() {}
		virtual void OnGameEnd() {}

		virtual void OnFixedUpdate(const GameTime& gameTime) { }
		virtual void OnUpdate(const GameTime& gameTime) { }
		virtual void OnPreDraw(const GameTime& gameTime) { }
		virtual void OnDraw(const GameTime& gameTime) { }

	private:
		std::atomic<bool> m_isRunning = false;
		float m_fixedUpdateRate = 1.0f / 60.0f;
	};

}