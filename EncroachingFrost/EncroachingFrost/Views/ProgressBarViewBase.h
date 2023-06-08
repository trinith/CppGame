#pragma once

#include <Vector2Utils.h>
#include <Game\ViewBase.h>
#include <SFML\Graphics.hpp>

class ProgressBarViewBase : public GhettoEngine::ViewBase
{
public:
	ProgressBarViewBase(sf::RenderTarget& renderTarget, const sf::Vector2f& position, const sf::Vector2f& size)
		: _renderTarget{ renderTarget }
		, _position{ position }
		, _size{ size }
	{
	}

	virtual float GetFillPercent() const = 0;
	virtual const sf::Color& GetFillColour() const = 0;
	virtual bool IsVisible() const { return true; }

protected:
	virtual void OnDraw(const GhettoEngine::GameTime& gameTime) override
	{
		if (IsVisible())
		{
			// Frame
			_rect.setPosition(_position);
			_rect.setSize(_size);
			_rect.setFillColor(Constants::Colours::Background);
			_rect.setOutlineColor(Constants::Colours::Outline);
			_rect.setOutlineThickness(-Constants::BorderThickness);
			_renderTarget.draw(_rect);

			// Fill
			const sf::Vector2f borderThickness{ Constants::BorderThickness, Constants::BorderThickness };
			_rect.setPosition(_rect.getPosition() + borderThickness);
			_rect.setSize(_rect.getSize() + borderThickness * -2.f);
			_rect.setSize(ScaleVector(_rect.getSize(), sf::Vector2f{ GetFillPercent(), 1.f }));
			_rect.setFillColor(GetFillColour());
			_rect.setOutlineThickness(0);
			_renderTarget.draw(_rect);
		}
	}

private:
	struct Constants
	{
		inline static const float BorderThickness = 1;
		inline static const sf::Vector2f BarOffset{ 2, 2 };
		inline static const sf::Vector2f BarFrameSize{ 150, 6 };

		struct Colours
		{
			inline static const sf::Color Outline{ 0, 0, 0 };
			inline static const sf::Color Background{ 64, 64, 64 };
		};
	};

	sf::RenderTarget& _renderTarget;
	const sf::Vector2f _position;
	const sf::Vector2f _size;

	sf::RectangleShape _rect;
};