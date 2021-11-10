// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Bullet.h"
#include "Pickup.h"
#include "Player.h"
#include "TextureHolder.h"
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
	const string bgFilename = "graphics/background_sheet.png";

	// prepare for a horde of zombies
	int numZombies = 0;
	int numZombiesAlive = 0;

	// prepare bullets @TODO - this should be a weapon class
	vector<Bullet> vBullets(100);
	int currentBullet = 0;
	int bulletsSpare = 24;
	int bulletsInClip = 6;
	int clipSize = 6;
	float fireRate = 1;

	// when was fire button last pressed?
	Time fireButtonLastPressed;

	// hide mouse and pointer and replace with crosshair
	window.setMouseCursorVisible(false);

	Sprite sCrosshair;
	string const chFilename = "graphics/crosshair.png";
	sCrosshair.setTexture(TextureHolder::getTexture(chFilename));
	sCrosshair.setOrigin(25, 25);

	// create a couple of pickups
	Pickup healthPickUp(1);
	Pickup ammoPickUp(2);

	// game info
	int score = 0;
	int hiScore = 0;

	// create the arena
	ZombieArena zombieArena;
	const int ARENA_WIDTH = 1000;
	const int ARENA_HEIGHT = 1000;

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
					// reloading
					if (event.key.code == Keyboard::R)
					{
						if (bulletsSpare >= clipSize)
						{
							// reload
							bulletsInClip = clipSize;
							bulletsSpare -= clipSize;
						}
						else if (bulletsSpare > 0)
						{
							bulletsInClip = bulletsSpare;
							bulletsSpare = 0;
						}
						else
						{
							// ?
						}
					}
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

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (gameTimeTotal.asMilliseconds() - fireButtonLastPressed.asMilliseconds()
					> 1000 / fireRate && bulletsInClip > 0)
				{
					// pass centre of player and cross-hair to shoot function
					vBullets[currentBullet].shoot(
						player.getCenter().x, player.getCenter().y,
						mouseWorldPos.x, mouseWorldPos.y);

					++currentBullet;

					if (currentBullet > 99)
					{
						currentBullet = 0;
					}

					fireButtonLastPressed = gameTimeTotal;
					--bulletsInClip;
				} 

			} // end fire a bullet

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
				arena.width = ARENA_WIDTH;
				arena.height = ARENA_HEIGHT;
				arena.left = 0;
				arena.top = 0;

				// pass the vertex array by ref to create background
				int tilesize = zombieArena.createBackground(background, arena);
		
				player.spawn(arena, resolution, tilesize);

				// create pickups
				healthPickUp.setArena(arena);
				ammoPickUp.setArena(arena);

				// create horde of zombies
				numZombies = 10;
				zombieArena.createHorde(numZombies, arena);
				numZombiesAlive = numZombies;

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

			// set the cross hair to the mouse world location
			sCrosshair.setPosition(mouseWorldPos);

			// update the player
			player.update(dtAsSec, Mouse::getPosition());
			Vector2f playerPos(player.getCenter());

			mainView.setCenter(player.getCenter());

			// loop through each zombie and update them
			for (Zombie* z : zombieArena.mv_Zombies)
			{
				if (z->isAlive())
				{
					z->update(dtAsSec, playerPos);
				}
			}

			// update any bullets
			for (int i = vBullets.size()-1; i >= 0; --i)
			{
				if (vBullets[i].isInFlight())
				{
					vBullets[i].update(dtAsSec);
				}
				
				if(vBullets[i].isOutOfRange())
				{
					// remove from vector so it doesn't clog the game up
					vBullets.erase(vBullets.begin() + i);
				}
			}

			// update pickups
			healthPickUp.update(dtAsSec);
			ammoPickUp.update(dtAsSec);

			// have any zombies been shot?
			for (Bullet& b : vBullets)
			{
				for (Zombie* z : zombieArena.mv_Zombies)
				{
					if (b.isInFlight() && z->isAlive())
					{
						if (b.getPos().intersects(z->getPos()))
						{
							// stop the bullet
							b.stop();

							// register the hit and see if it was a kill
							if (z->hit())
							{
								score += 10;
								if (score >= hiScore)
								{
									hiScore = score;
								}
								--numZombiesAlive;
								// when all zombies are dead 
								if (numZombiesAlive == 0)
								{
									gameState = State::eLEVELING_UP;
								}
							}
						}
					}
				}
			} // end zombie being shot

			// have any zombies touched the player?
			for (Zombie* z : zombieArena.mv_Zombies) 
			{
				if (player.getPos().intersects(z->getPos()) && z->isAlive())
				{
					if (player.hit(gameTimeTotal))
					{
						// more here later
					}

					if (player.getHealth() <= 0)
					{
						gameState = State::eGAMEOVER;
					}
				}
			} // end player touched

			// has player walked over pickup
			if (player.getPos().intersects(healthPickUp.getPos()) && healthPickUp.hasSpawned())
			{
				player.increaseHealthLevel(healthPickUp.pickUp());
			}

			// has player touched ammo pickup
			if (player.getPos().intersects(ammoPickUp.getPos()) && ammoPickUp.hasSpawned())
			{
				bulletsSpare = ammoPickUp.pickUp();
			}

		} // end updating scene

		// ---- Draw the scene
		if (gameState == State::ePLAYING)
		{
			window.clear();
			window.setView(mainView);
			window.draw(background, &TextureHolder::getTexture(bgFilename));

			// draw zombies
			for (const Zombie* z : zombieArena.mv_Zombies)
			{
				window.draw(z->getSprite());
			}

			// draw bullets
			for (const Bullet& b : vBullets)
			{
				window.draw(b.getShape());
			}

			// draw player
			window.draw(player.getSprite());

			// draw the pickups
			if (ammoPickUp.hasSpawned())
			{
				window.draw(ammoPickUp.getSprite());
			}

			if (healthPickUp.hasSpawned())
			{
				window.draw(healthPickUp.getSprite());
			}

			// draw cross hair
			window.draw(sCrosshair);
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