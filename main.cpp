// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Player.h"
#include "ZombieArena.h"

//---GLOBALS--//
enum class State
{
	ePAUSED, eLEVELING_UP, eGAMEOVER, ePLAYING
};

// -----------------------------------------------------------------------------

int main()
{
	State gameState = State::eGAMEOVER;

	Vector2f resolution((float)VideoMode::getDesktopMode().width, (float)VideoMode::getDesktopMode().height);

	RenderWindow window(VideoMode((int)resolution.x, (int)resolution.y), "Zombie Arena", Style::Default);

	View mainView(FloatRect(0, 0, resolution.x, resolution.y));

	Clock clock;

	Time gameTimeTotal;

	Vector2f mouseWorldPos;
	Vector2i mouseScreenPos;

	Player player;

	IntRect arena;

	VertexArray background;
	Texture tBackground;
	tBackground.loadFromFile("graphics/background_sheet.png");

	// create the arena
	ZombieArena zombieArena;

	while (window.isOpen())
	{
		// ---- Handle input
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				// pause a game while playing
				if (event.key.code == Keyboard::Return && gameState == State::ePLAYING)
				{
					gameState = State::ePAUSED;
				}
				// restart while paused
				else if (event.key.code == Keyboard::Return && gameState == State::ePAUSED)
				{
					gameState = State::ePLAYING;
					// reset clock so there isn't a frame jump
					clock.restart();
				}
				// start a new game while in game over state
				else if (event.key.code == Keyboard::Return && gameState == State::eGAMEOVER)
				{
					gameState = State::eLEVELING_UP;
				}

				if (gameState == State::ePLAYING)
				{

				}
			
			}

		} // end event polling

		// handle player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// handle WASD while playing
		if (gameState == State::ePLAYING)
		{
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}
		} // end WASD handling

		// handle the leveling state
		if (gameState == State::eLEVELING_UP)
		{
			if (event.key.code == Keyboard::Num1)
			{
				gameState = State::ePLAYING;
			}

			if (event.key.code == Keyboard::Num2)
			{
				gameState = State::ePLAYING;
			}

			if (event.key.code == Keyboard::Num3)
			{
				gameState = State::ePLAYING;
			}

			if (event.key.code == Keyboard::Num4)
			{
				gameState = State::ePLAYING;
			}

			if (event.key.code == Keyboard::Num5)
			{
				gameState = State::ePLAYING;
			}

			if (event.key.code == Keyboard::Num6)
			{
				gameState = State::ePLAYING;
			}

			if (gameState == State::ePLAYING)
			{
				// prepare the level
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;

				// pass the vertex array by ref to create background
				int tilesize = zombieArena.createBackground(background, arena);

				//int tilesize = 50;
				player.spawn(arena, resolution, tilesize);

				// reset clock
				clock.restart();
			}
		}
		// end leveling up

		// ---- Update the Frame
		if (gameState == State::ePLAYING)
		{
			Time dt = clock.restart();
			gameTimeTotal += dt;
			float dtAsSec = dt.asSeconds();

			mouseScreenPos = Mouse::getPosition();
			mouseWorldPos = window.mapPixelToCoords(Mouse::getPosition(), mainView);

			// update the player
			player.update(dtAsSec, Mouse::getPosition());
			Vector2f playerPos(player.getCenter());

			mainView.setCenter(player.getCenter());
		} // end updating scene

		// ---- Draw the scene
		if (gameState == State::ePLAYING)
		{
			window.clear();
			window.setView(mainView);
			window.draw(background, &tBackground);
			window.draw(player.getSprite());
		}

		if (gameState == State::eLEVELING_UP)
		{

		}

		if (gameState == State::ePAUSED)
		{

		}

		if (gameState == State::eGAMEOVER)
		{

		}

		window.display();

	} // end game loop

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------