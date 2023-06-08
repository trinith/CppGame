#pragma once

#include <Vector2Utils.h>
#include <Entities\FirepitFlameEntity.h>
#include <Game\ControllerBase.h>
#include <Models\PlayerModel.h>
#include <vector>

// GT_TODO:Break this controller up.
/* NOTES:
	
	NOT A PRIORITY, but this controller currently has a lot of responsibilities and this probably should be addressed.

	Currently this controller is responsible for:
		* Determining if the player is close to a flame.
		* If the player is close, transfering power from a flame to the player.
		* If the player is far, recharging the flame and passively draining the player.
	
	This could probably get broken up into several other controllers...
		* PlayerFlameProximityController - Sets a flag on both the flame and the player to indicate they are recharging
		  or draining.
		* PlayerPowerController - If the recharge flag is set, rechage power otherwise passively drain it.
		* FirepitFlamePowerController - If the recharge flag is set, rechage power, otherwise drain it.
*/

class FlamePowerController : public GhettoEngine::ControllerBase
{
public:
	FlamePowerController(std::vector<FirepitFlameEntity>& flames, PlayerModel& playerModel)
		: _flames{ flames }
		, _playerModel{ playerModel }
	{
	}

protected:
	virtual void OnUpdate(const GhettoEngine::GameTime& gameTime) override
	{
		sf::FloatRect playerBounds{ _playerModel.Bounds.Position, _playerModel.Bounds.Size };
		_playerModel.Hitboxes.ApplyGroundHitbox(playerBounds);
		const sf::Vector2f playerCentre{
			playerBounds.left + playerBounds.width / 2.f,
			playerBounds.top + playerBounds.height / 2.f
		};

		const float powerDelta = FirepitFlameModel::Constants::PowerDrain * gameTime.ElapsedSeconds.count();

		bool playerIsCharging = false;
		for (auto&& flameEntity : _flames)
		{
			FirepitFlameModel& flame = flameEntity.GetModel();

			sf::FloatRect flameBounds{ flame.Bounds.Position, flame.Bounds.Size };
			flame.Hitboxes.ApplyGroundHitbox(flameBounds);
			const sf::Vector2f flameCentre
			{
				flameBounds.left + flameBounds.width / 2.f,
				flameBounds.top + flameBounds.height / 2.f
			};

			const float distSquared = VectorLengthSquared(flameCentre - playerCentre);
			const bool playerIsClose = distSquared <= FirepitFlameModel::Constants::ChargeDistance * FirepitFlameModel::Constants::ChargeDistance;
			const bool flameHasPower = flame.Stats.Power && flame.Stats.Power.value() > 0;
			if (playerIsClose && flameHasPower)
			{
				// Transfer power from the flame to the player.
				flame.Stats.ModifyPower(-powerDelta);
				_playerModel.Stats.ModifyPower(powerDelta);
				playerIsCharging = true;
			}
			else if (!playerIsClose)
			{
				// Regenerate power on the flame.
				flame.Stats.ModifyPower(powerDelta);
			}
		}

		if (!playerIsCharging)
			_playerModel.Stats.ModifyPower(-PlayerModel::Constants::PassivePowerDrain * gameTime.ElapsedSeconds.count());
	}

private:
	std::vector<FirepitFlameEntity>& _flames;
	PlayerModel& _playerModel;
};