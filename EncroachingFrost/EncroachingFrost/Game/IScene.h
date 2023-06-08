#pragma once

#include "IController.h"
#include "IView.h"

#include <optional>

namespace GhettoEngine
{

	class IScene : public IController, public IView
	{
	public:
		virtual ~IScene() = default;

		virtual void Initialize() = 0;
		virtual void Uninitialize() = 0;
		virtual bool IsComplete() const = 0;
		virtual void EndScene() = 0;
		virtual std::optional<std::reference_wrapper<IScene>> GetNextScene() const = 0;
		virtual void SetNextScene(std::optional<std::reference_wrapper<IScene>> nextScene) = 0;
	};

}