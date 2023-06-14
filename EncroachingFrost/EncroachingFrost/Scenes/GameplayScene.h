#pragma once

#include <WindowManager.h>
#include <Assets\AssetManager.h>
#include <Game\SceneBase.h>
#include <Input\InputManager.h>

#include <vector>

#include <Entities\PlayerEntity.h>
#include <Entities\FirepitFlameEntity.h>
#include <Entities\TargetDummyEntity.h>

#include <Models\CombatTextItems.h>
#include <Models\EntityReferenceList.h>
#include <Models\PendingAbilityActions.h>
#include <Models\PlayerUseInputModel.h>
#include <Models\RenderCanvas.h>
#include <Models\TileMap.h>

#include <Controllers\CombatTextController.h>
#include <Controllers\FirepitFlameAnimationController.h>
#include <Controllers\FlamePowerController.h>
#include <Controllers\PlayerAbilityCooldownController.h>
#include <Controllers\PlayerAbilityQueueController.h>
#include <Controllers\PlayerHealthController.h>
#include <Controllers\PlayerInputController.h>
#include <Controllers\PlayerMoveAbilityCancelController.h>
#include <Controllers\PlayerMoveController.h>
#include <Controllers\PlayerMoveFinalizeController.h>
#include <Controllers\PlayerSkillActivationController.h>
#include <Controllers\PlayerTargetController.h>
#include <Controllers\PlayerUseInputController.h>
#include <Controllers\PendingAbilityActionsController.h>

#include <Views\CombatTextView.h>
#include <Views\EntityView.h>
#include <Views\EntityShadowView.h>
#include <Views\FirepitFlamePowerView.h>
#include <Views\GenericView.h>
#include <Views\PlayerAbilityCastView.h>
#include <Views\PlayerAbilityInterfaceView.h>
#include <Views\PlayerHealthView.h>
#include <Views\PlayerPowerView.h>
#include <Views\PlayerTargetView.h>
#include <Views\RenderCanvasView.h>
#include <Views\TileMapView.h>

class GameplayScene : public GhettoEngine::SceneBase
{
private:
	struct Constants
	{
		struct Sprites
		{
			inline static const size_t Firepit = 30;
		};
	};

public:
	GameplayScene(WindowManager& windowManager, const InputManager& inputManager, const Assets::AssetManager& assetManager)
		: _windowManager{ windowManager }
		, _inputManager{ inputManager }
		, _assetManager{ assetManager }
		, _canvas{ windowManager, sf::Vector2i{320, 240}, sf::Vector2f{3.0f, 3.0f} }
		, _map{ 20, 15 }
	{
	}

	virtual void OnInitialize() override
	{
		// Get the sprite sheets our views will use.
		// Probably don't need to query this every time... but we're gonna!
		const Assets::AssetManager::SpriteSheets& spriteSheets = _assetManager.GetSpriteSheets();

		OptionalRef<const Assets::SpriteSheet> tileSprites = spriteSheets[Assets::SpriteSheets::Tiles.AssetName];
		ASSERT(tileSprites);

		OptionalRef<const Assets::SpriteSheet> entitySprites = spriteSheets[Assets::SpriteSheets::Entities.AssetName];
		ASSERT(entitySprites);

		// Some initial data... I probably need a way to import this >.<
		_map.Set(
			{
				32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,
				32,	48,	48,	48,	48,	48,	48,	48,	48,	48,	48,	48,	48,	48,	48,	48,	48,	48,	48,	32,
				32,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	32,
				32,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	32,
				32,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	0,	32,
				32,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	32,
				32,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	32,
				32,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	32,
				32,	2,	0,	1,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	32,
				32,	0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	32,
				32,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	32,
				32,	13,	14,	15,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	13,	14,	15,	32,
				32,	29,	30,	31,	1,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	29,	30,	31,	32,
				32,	45,	46,	47,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	45,	46,	47,	32,
				32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,	32,
			}
		);

		ClearControllers();
		ClearViews();
		_entities.clear();

		_player = PlayerEntity{};
		_entities.emplace_back(_player);

		CreateTargetDummies();
		CreateFirepitFlames();

		// Controllers
		{
			RegisterController<PlayerUseInputController>(_playerUseInputModel, _inputManager, _canvas);
			RegisterController<PlayerTargetController>(_player.GetModel(), _playerUseInputModel, _entities);
			RegisterController<PlayerInputController>(_player.GetModel(), _inputManager);
			RegisterController<PlayerMoveAbilityCancelController>(_player.GetModel());
			RegisterController<PlayerMoveController>(_player.GetModel(), _map, *tileSprites);
			RegisterController<PlayerSkillActivationController>(_inputManager, _player);
			RegisterController<PlayerAbilityQueueController>(_player, _pendingActionQueue);
			RegisterController<PlayerAbilityCooldownController>(_player.GetModel());
			RegisterController<PendingAbilityActionsController>(_pendingActionQueue, _combatTextItems);
			RegisterController<PlayerMoveFinalizeController>(_player.GetModel());
			RegisterController<FlamePowerController>(_firepitFlames, _player.GetModel());
			RegisterController<FirepitFlamesAnimationController>(_firepitFlames);
			RegisterController<PlayerHealthController>(_player.GetModel());
			RegisterController<CombatTextController>(_combatTextItems);
		}

		// Views
		{
			RegisterView<GenericView>([&](const GhettoEngine::GameTime&) mutable { _canvas.GetTarget().clear(); });
			// World Space Views
			{
				// Game Views
				RegisterView<TileMapView>(_canvas.GetTarget(), _map, *tileSprites);
				RegisterView<EntityShadowView>(_canvas.GetTarget(), _entities, *entitySprites);
				RegisterView<PlayerTargetView>(_canvas.GetTarget(), _player, *entitySprites);
				RegisterView<EntityView>(_canvas.GetTarget(), _entities, *entitySprites);
				RegisterView<CombatTextView>(_canvas.GetTarget(), _combatTextItems, _assetManager.GetFonts());

				// Hud Views
				RegisterView<FirepitFlamePowerView>(_canvas.GetTarget(), _firepitFlames);
				RegisterView<PlayerHealthView>(_canvas.GetTarget(), _player.GetModel());
				RegisterView<PlayerPowerView>(_canvas.GetTarget(), _player.GetModel());
				RegisterView<PlayerAbilityCastView>(_canvas.GetTarget(), _player.GetModel());
				RegisterView<PlayeAbilityInterfaceView>(_canvas, _player, *entitySprites, _assetManager.GetFonts());
			}
			RegisterView<GenericView>([&](const GhettoEngine::GameTime&) mutable { _canvas.GetTarget().display(); });
			// Screen Space Views
			RegisterView<RenderCanvasView>(_canvas, _windowManager.GetWindow());
		}
	}

	virtual void OnUpdate(const GhettoEngine::GameTime& gameTime) override
	{
		if (_inputManager.GetState().HasAction(Action::Back))
			EndScene();
	}

	virtual void OnDraw(const GhettoEngine::GameTime&) override
	{
	}

private:
	void CreateTargetDummies()
	{
		_targetDummies.clear();

		_targetDummies.emplace_back(sf::Vector2f{ 4.f * 16.f, 5.f * 16.f });
		_targetDummies.emplace_back(sf::Vector2f{ 15.f * 16.f, 5.f * 16.f });
		for (auto&& dummy : _targetDummies)
			_entities.emplace_back(dummy);
	}

	void CreateFirepitFlames()
	{
		_firepitFlames.clear();

		const size_t mapWidth = _map.GetWidth();

		for (size_t i = 0; i < _map.GetNumTiles(); ++i)
		{
			if (_map.Get(i) == Constants::Sprites::Firepit)
			{
				_firepitFlames.emplace_back(sf::Vector2f{ static_cast<float>(i % mapWidth) * 16.f, static_cast<float>(i / mapWidth) * 16.f });
			}
		}

		for (auto&& flame : _firepitFlames)
			_entities.emplace_back(flame);
	}

	WindowManager& _windowManager;
	const InputManager& _inputManager;
	const Assets::AssetManager& _assetManager;

	RenderCanvas _canvas;

	PlayerEntity _player;
	PlayerUseInputModel _playerUseInputModel;
	TileMap _map;
	PendingAbilityActions _pendingActionQueue;
	CombatTextItems _combatTextItems;

	std::vector<TargetDummyEntity> _targetDummies;
	std::vector<FirepitFlameEntity> _firepitFlames;

	EntityReferenceList<IGameEntity> _entities;
};