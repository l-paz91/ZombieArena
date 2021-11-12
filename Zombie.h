// -----------------------------------------------------------------------------
#ifndef Zombie_H
#define Zombie_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include <string>
using namespace sf;

// -----------------------------------------------------------------------------

class Zombie
{
public:
	Zombie(int pMaxSpeed, int pMaxHealth);
	
	virtual void spawn(float pStartX, float pStartY, int pSeed, const std::string& pFilename = "");

	void update(float pElapsedTime, Vector2f pPlayerLoc);
	bool hit();

	const FloatRect getPos() const { return mSprite.getGlobalBounds(); }
	const Sprite& getSprite() const { return mSprite; }
	const bool isAlive() const { return mAlive; }

protected:
	using Super = Zombie;	// make it more explicit that we're calling the base in derived types

	const int MAX_SPEED;
	const int MAX_HEALTH;
	const int MAX_VARIANCE;
	const int OFFSET;

	Vector2f mPos;
	Sprite mSprite;
	float mSpeed;
	float mHealth;
	bool mAlive;

};

// -----------------------------------------------------------------------------

class ZombieBloater : public Zombie
{
public:
	ZombieBloater();

	virtual void spawn(float pStartX, float pStartY, int pSeed, const std::string& pFilename = "");
};

// -----------------------------------------------------------------------------

class ZombieChaser : public Zombie
{
public:
	ZombieChaser();

	virtual void spawn(float pStartX, float pStartY, int pSeed, const std::string& pFilename = "");
};

// -----------------------------------------------------------------------------

class ZombieCrawler : public Zombie
{
public:
	ZombieCrawler();

	virtual void spawn(float pStartX, float pStartY, int pSeed, const std::string& pFilename = "");
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Zombie_H