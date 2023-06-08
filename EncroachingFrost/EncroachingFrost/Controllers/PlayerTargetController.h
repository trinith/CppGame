#pragma once

#include <Entities\IGameEntity.h>
#include <Game\ControllerBase.h>
#include <Models\EntityReferenceList.h>
#include <Models\PlayerModel.h>
#include <Models\PlayerUseInputModel.h>

class PlayerTargetController : public GhettoEngine::ControllerBase
{
public:
	PlayerTargetController(PlayerModel& playerModel, const PlayerUseInputModel& inputModel, const EntityReferenceList<IGameEntity>& entities)
		: _playerModel{ playerModel }
		, _inputModel{ inputModel }
		, _entities{ entities }
	{
	}

protected:
	virtual void OnUpdate(const GhettoEngine::GameTime&) override
	{
		if (_inputModel.worldPosition)
		{
			_playerModel.Target = std::nullopt;

			for (auto&& entityRef : _entities)
			{
				sf::IntRect selectionBounds{ GetSelectionBounds(entityRef.get()) };
				if (selectionBounds.contains(*_inputModel.worldPosition))
				{
					_playerModel.Target = entityRef.get();
					break;
				}
			}
		}
	}

private:
	sf::IntRect GetSelectionBounds(const IGameEntity& entity)
	{
		const EntityBounds& bounds = entity.GetBounds();
		const EntityHitboxes& hitboxes = entity.GetHitboxes();

		sf::FloatRect selectionRect{ bounds.Position, bounds.Size };
		hitboxes.ApplySelectionHitbox(selectionRect);

		return static_cast<sf::IntRect>(selectionRect);
	}

	PlayerModel& _playerModel;
	const PlayerUseInputModel& _inputModel;
	const EntityReferenceList<IGameEntity>& _entities;
};