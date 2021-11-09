// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Zombie.h"

#include "TextureHolder.h"

// -----------------------------------------------------------------------------

Zombie::Zombie()
	: MAX_VARIANCE(30)
	, OFFSET(101 - MAX_VARIANCE)
	, mPos()
	, mSprite()
	, mSpeed(0.0f)
	, mHealth(0.0f)
	, mAlive(true)
{}

// -----------------------------------------------------------------------------

void Zombie::spawn(float pStartX, float pStartY, int pSeed)
{
	// every zombie is unique. Create a speed modifier
	srand((int)time(0) * pSeed);

	// somewhere between 80 and 100
	float modifier = (rand() % MAX_VARIANCE) + OFFSET;

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
	: BLOATER_SPEED(40)
	, BLOATER_HEALTH(5)
{
}

// -----------------------------------------------------------------------------

void ZombieBloater::spawn(float pStartX, float pStartY, int pSeed)
{
	const string filename = "graphics/bloater.png";
	mSprite = Sprite(TextureHolder::getTexture(filename));

	mSpeed = BLOATER_SPEED;
	mHealth = BLOATER_HEALTH;

	Super::spawn(pStartX, pStartY, pSeed);	// now finish off the "generic" part of spawning
}

// -----------------------------------------------------------------------------

ZombieChaser::ZombieChaser()
	: CHASER_SPEED(80)
	, CHASER_HEALTH(1)
{
}

// -----------------------------------------------------------------------------

void ZombieChaser::spawn(float pStartX, float pStartY, int pSeed)
{
	const string filename = "graphics/chaser.png";
	mSprite = Sprite(TextureHolder::getTexture(filename));

	mSpeed = CHASER_SPEED;
	mHealth = CHASER_HEALTH;

	Super::spawn(pStartX, pStartY, pSeed);	// now finish off the "generic" part of spawning
}

// -----------------------------------------------------------------------------

ZombieCrawler::ZombieCrawler()
	: CRAWLER_SPEED(20)
	, CRAWLER_HEALTH(3)
{
}

// -----------------------------------------------------------------------------

void ZombieCrawler::spawn(float pStartX, float pStartY, int pSeed)
{
	const string filename = "graphics/crawler.png";
	mSprite = Sprite(TextureHolder::getTexture(filename));

	mSpeed = CRAWLER_SPEED;
	mHealth = CRAWLER_HEALTH;

	Super::spawn(pStartX, pStartY, pSeed);	// now finish off the "generic" part of spawning
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------