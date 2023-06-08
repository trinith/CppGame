#include "ProjectGame.h"
#include "WindowManager.h"

#include <iostream>

int main()
{
    sf::RenderWindow window{ sf::VideoMode{1280, 720}, "Some Title", sf::Style::Titlebar | sf::Style::Close };
    WindowManager windowManager{ window };

    ProjectGame game{ windowManager };
    game.Run();

    return 0;
}