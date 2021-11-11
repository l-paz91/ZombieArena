// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Zombie.h"

#include "TextureHolder.h"

// -----------------------------------------------------------------------------

Zombie::Zombie(int pMaxSpeed, int pMaxHealth)
	: MAX_SPEED(pMaxSpeed)
	, MAX_HEALTH(pMaxHealth)
	, MAX_VARIANCE(30)
	, OFFSET(101 - MAX_VARIANCE)
	, mPos()
	, mSprite()
	, mSpeed(0.0f)
	, mHealth(0.0f)
	, mAlive(true)
{}

// -----------------------------------------------------------------------------

void Zombie::spawn(float pStartX, float pStartY, int pSeed, const string& pFilename /*= default*/)
{
	Texture& t = TextureHolder::getTexture(pFilename);
	mSprite.setTexture(t);

	mSpeed = (float)MAX_SPEED;
	mHealth = (float)MAX_HEALTH;

	// every zombie is unique. Create a speed modifier
	srand((int)time(0) * pSeed);

	// somewhere between 80 and 100
	float modifier = (float)(rand() % MAX_VARIANCE) + OFFSET;

	// express this as a fraction of 1
	modifier /= 100;

	mSpeed *= modifier;

	mPos.x = pStartX;
	mPos.y = pStartY;

	mSprite.setOrigin(25, 25);
	mSprite.setPosition(mPos);
}

// -----------------------------------------------------------------------------

void Zombie::update(float pElapsedTime, Vector2f pPlayerLoc)
{
	float px = pPlayerLoc.x;
	float py = pPlayerLoc.y;

	// update the zombie position variables
	if (px > mPos.x)
	{
		mPos.x = mPos.x + mSpeed * pElapsedTime;
	}

	if (py > mPos.y)
	{
		mPos.y = mPos.y + mSpeed * pElapsedTime;
	}

	if (px < mPos.x)
	{
		mPos.x = mPos.x - mSpeed * pElapsedTime;
	}

	if (py < mPos.y)
	{
		mPos.y = mPos.y - mSpeed * pElapsedTime;
	}

	// move the sprite
	mSprite.setPosition(mPos);

	// face the sprite in the correct direction
	float angle = (atan2(py - mPos.y, px - mPos.x) * 180.0f) / 3.141f;

	mSprite.setRotation(angle);
}

// -----------------------------------------------------------------------------

// returns true if dead
bool Zombie::hit()
{
	--mHealth;
	if (mHealth <= 0)
	{
		// dead...er
		mAlive = false;
		const string filename = "graphics/blood.png";
		mSprite.setTexture(TextureHolder::getTexture(filename));
		return true;
	}

	// injured but not yet dead
	return false;
}

// -----------------------------------------------------------------------------

ZombieBloater::ZombieBloater()
	: Zombie(40, 5)
{
}

// -----------------------------------------------------------------------------

void ZombieBloater::spawn(float pStartX, float pStartY, int pSeed, const string& pFilename /*= default*/)
{
	const string filename = "graphics/bloater.png";

	Super::spawn(pStartX, pStartY, pSeed, filename);	// now finish off the "generic" part of spawning
}

// -----------------------------------------------------------------------------

ZombieChaser::ZombieChaser()
	: Zombie(80, 1)
{
}

// -----------------------------------------------------------------------------

void ZombieChaser::spawn(float pStartX, float pStartY, int pSeed, const string& pFilename /*= default*/)
{
	const string filename = "graphics/chaser.png";
	
	Super::spawn(pStartX, pStartY, pSeed, filename);	// now finish off the "generic" part of spawning
}

// -----------------------------------------------------------------------------

ZombieCrawler::ZombieCrawler()
	: Zombie(20, 3)
{
}

// -----------------------------------------------------------------------------

void ZombieCrawler::spawn(float pStartX, float pStartY, int pSeed, const string& pFilename /*= default*/)
{
	const string filename = "graphics/crawler.png";
	
	Super::spawn(pStartX, pStartY, pSeed, filename);	// now finish off the "generic" part of spawning
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------