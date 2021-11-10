// -----------------------------------------------------------------------------
#ifndef Pickup_H
#define Pickup_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include "std_lib_facilities.h"

using namespace sf;

// -----------------------------------------------------------------------------

class Pickup
{
public:
	Pickup(int pType);
	
	void setArena(const IntRect& pArena);
	void spawn();
	void update(float pElapsedTime);
	void upgrade();

	int  pickUp();
	
	const bool hasSpawned() const { return mSpawned; }
	const FloatRect getPos() const { return mSprite.getGlobalBounds(); }
	const Sprite getSprite() const { return mSprite; }

private:
	const int START_HEALTH;
	const int START_AMMO;
	const int START_WAIT_TIME;
	const int START_SECONDS_TO_LIVE;

	Sprite mSprite;
	IntRect mArena;

	int mType;
	int mValue;

	float mSecondsSinceSpawn;
	float mSecondsSinceDespawn;
	float mSecondsToLive;
	float mSecondsToWait;

	bool mSpawned;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Pickup_H