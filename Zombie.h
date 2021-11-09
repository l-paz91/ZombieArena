// -----------------------------------------------------------------------------
#ifndef Zombie_H
#define Zombie_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include "std_lib_facilities.h"

using namespace sf;

// -----------------------------------------------------------------------------

class Zombie
{
public:
	Zombie();
	
	virtual void spawn(float pStartX, float pStartY, int pSeed);

	void update(float pElapsedTime, Vector2f pPlayerLoc);
	bool hit();

	const FloatRect getPos() const { return mSprite.getGlobalBounds(); }
	const Sprite& getSprite() const { return mSprite; }
	const bool isAlive() const { return mAlive; }

protected:
	using Super = Zombie;	// make it more explicit that we're calling the base in derived types

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

	virtual void spawn(float pStartX, float pStartY, int pSeed);

private:
	const float BLOATER_SPEED;
	const float BLOATER_HEALTH;
};

// -----------------------------------------------------------------------------

class ZombieChaser : public Zombie
{
public:
	ZombieChaser();

	virtual void spawn(float pStartX, float pStartY, int pSeed);

private:
	const float CHASER_SPEED;
	const float CHASER_HEALTH;
};

// -----------------------------------------------------------------------------

class ZombieCrawler : public Zombie
{
public:
	ZombieCrawler();

	virtual void spawn(float pStartX, float pStartY, int pSeed);

private:
	const float CRAWLER_SPEED;
	const float CRAWLER_HEALTH;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Zombie_H