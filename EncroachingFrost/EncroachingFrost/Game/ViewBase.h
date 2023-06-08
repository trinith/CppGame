#pragma once

#include <Game\IView.h>

namespace GhettoEngine
{
	class ViewBase : public IView
	{
	public:
		virtual void PreDraw(const GameTime& gameTime) final
		{
			OnPreDraw(gameTime);
		}

		virtual void Draw(const GameTime& gameTime) final
		{
			OnDraw(gameTime);
		}

	protected:
		virtual void OnPreDraw(const GameTime& gameTime) { }
		virtual void OnDraw(const GameTime& gameTime) { }
	};
}