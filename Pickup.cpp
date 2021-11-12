// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Pickup.h"

#include "TextureHolder.h"

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

Pickup::Pickup(int pType)
	: START_HEALTH(50)
	, START_AMMO(12)
	, START_WAIT_TIME(10)
	, START_SECONDS_TO_LIVE(5)
	, mSprite()
	, mArena()
	, mType(pType)
	, mValue()
	, mSecondsSinceSpawn()
	, mSecondsSinceDespawn()
	, mSecondsToLive((float)START_SECONDS_TO_LIVE)
	, mSecondsToWait((float)START_WAIT_TIME)
	, mSpawned(false)
{
	switch (mType)
	{
	case 1:
	{	
		const string filename = "graphics/health_pickup.png";
		mSprite.setTexture(TextureHolder::getTexture(filename));
		mValue = START_HEALTH;
		break;
	}
	case 2:
	{
		const string filename = "graphics/ammo_pickup.png";
		mSprite.setTexture(TextureHolder::getTexture(filename));
		mValue = START_AMMO;
		break;
	}
	default:
		cout << "How did we get here?";
		break;
	}

	mSprite.setOrigin(25, 25);
}

// -----------------------------------------------------------------------------

void Pickup::setArena(const IntRect& pArena)
{
	mArena.left = pArena.left + 50;
	mArena.width = pArena.width - 50;
	mArena.top = pArena.top + 50;
	mArena.height = pArena.height - 50;

	spawn();
}

void Pickup::spawn()
{
	srand((int)time(0) / mType);
	int x = (int)(rand() % mArena.width);

	srand((int)time(0) * mType);
	int y = (int)(rand() % mArena.height);

	mSecondsSinceSpawn = 0;
	mSpawned = true;
	mSprite.setPosition((float)x, (float)y);
}

// -----------------------------------------------------------------------------

void Pickup::update(float pElapsedTime)
{
	if (mSpawned)
	{
		mSecondsSinceSpawn += pElapsedTime;
	}
	else
	{
		mSecondsSinceDespawn += pElapsedTime;
	}

	// do we need to hide a pickup
	if (mSecondsSinceSpawn > mSecondsToLive && mSpawned)
	{
		// remove the pickup and put it somewhere else
		mSpawned = false;
		mSecondsSinceDespawn = 0;
	}

	// do we need to spawn a pickup
	if (mSecondsSinceDespawn > mSecondsToWait && !mSpawned)
	{
		// spawn the pickup and reset the timer
		spawn();
	}
}

// -----------------------------------------------------------------------------

void Pickup::upgrade()
{
	if (mType == 1)
	{
		mValue += (int)(START_HEALTH * 0.5f);
	}
	else
	{
		mValue += (int)(START_AMMO * 0.5f);
	}

	// make them frequent and last longer
	mSecondsToLive += (START_SECONDS_TO_LIVE / 10);
	mSecondsToWait -= (START_WAIT_TIME / 10);
}

// -----------------------------------------------------------------------------

int Pickup::pickUp()
{
	mSpawned = false;
	mSecondsSinceDespawn = 0;
	return mValue;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


