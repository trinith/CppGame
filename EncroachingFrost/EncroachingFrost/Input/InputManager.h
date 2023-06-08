#pragma once

#include <WindowManager.h>

#include <Game\ControllerBase.h>
#include <SFML\Window\Keyboard.hpp>

#include <vector>
#include <unordered_map>

#pragma warning(push)
#pragma warning(disable: 26812)

enum class Action : size_t
{
	Back = 0,
	Left,
	Right,
	Up,
	Down,

	PrimaryUse,

	SkillSlot1,
	SkillSlot2,
	SkillSlot3,
	SkillSlot4,
	SkillSlot5,
};

struct InputState
{
	std::vector<Action> Actions;

	bool HasAction(Action action) const
	{
		return std::find(Actions.begin(), Actions.end(), action) != Actions.end();
	}

	bool HasAnyAction(std::initializer_list<Action> actions) const
	{
		for (Action action : actions)
		{
			if (HasAction(action))
				return true;
		}

		return false;
	}
};

class InputManager : public GhettoEngine::ControllerBase
{
public:
	InputManager(const WindowManager& windowManager)
		: _windowManager{ windowManager }
	{
		SetInputBindings();
	}

	const sf::Vector2i& GetMousePosition() const { return _mousePos; }
	const InputState& GetState() const { return _state; }

protected:
	virtual void OnUpdate(const GhettoEngine::GameTime& gameTime) override
	{
		_state.Actions.clear();

		if (!_windowManager.HasFocus())
			return;

		// Check for keyboard actions
		for (auto [key, action] : _keyMappings)
		{
			if (sf::Keyboard::isKeyPressed(key))
				_state.Actions.emplace_back(action);
		}

		// Check for mouse actions.
		for (auto [button, action] : _mouseMappings)
		{
			if (sf::Mouse::isButtonPressed(button))
				_state.Actions.emplace_back(action);
		}

		_mousePos = sf::Mouse::getPosition(_windowManager.GetWindow());
	}

private:
	void SetInputBindings()
	{
		_keyMappings.emplace(sf::Keyboard::Key::Escape, Action::Back);
		_keyMappings.emplace(sf::Keyboard::Key::A, Action::Left);
		_keyMappings.emplace(sf::Keyboard::Key::D, Action::Right);
		_keyMappings.emplace(sf::Keyboard::Key::W, Action::Up);
		_keyMappings.emplace(sf::Keyboard::Key::S, Action::Down);

		_keyMappings.emplace(sf::Keyboard::Key::Num1, Action::SkillSlot1);
		_keyMappings.emplace(sf::Keyboard::Key::Num2, Action::SkillSlot2);
		_keyMappings.emplace(sf::Keyboard::Key::Num3, Action::SkillSlot3);
		_keyMappings.emplace(sf::Keyboard::Key::Num4, Action::SkillSlot4);
		_keyMappings.emplace(sf::Keyboard::Key::Num5, Action::SkillSlot5);

		_mouseMappings.emplace(sf::Mouse::Button::Left, Action::PrimaryUse);
	}

	std::unordered_map<sf::Keyboard::Key, Action> _keyMappings;
	std::unordered_map<sf::Mouse::Button, Action> _mouseMappings;

	InputState _state;
	const WindowManager& _windowManager;
	sf::Vector2i _mousePos;
};

#pragma warning(pop)