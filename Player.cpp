// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Player.h"

// -----------------------------------------------------------------------------

Player::Player()
	: mStartSpeed(200)
	, mStartHealth(100)
	, mSpeed(mStartSpeed)
	, mTileSize(50)
	, mHealth((int)mStartHealth)
	, mMaxHealth((int)mStartHealth)
	, mDamageAmount(10)
	, mUpPressed(false)
	, mDownPressed(false)
	, mLeftPressed(false)
	, mRightPressed(false)
{
	mTexture.loadFromFile("graphics/player.png");
	mSprite.setTexture(mTexture);
	mSprite.setOrigin(25, 25);
}

// -----------------------------------------------------------------------------

void Player::spawn(IntRect pArena, Vector2f pResolution, int pTileSize)
{
	// place player in the middle of the arena
	mPos.x = (float)pArena.width / 2;
	mPos.y = (float)pArena.height / 2;

	mArena = pArena;

	mTileSize = pTileSize;

	mResolution = pResolution;
}

// -----------------------------------------------------------------------------

void Player::resetPlayerStats()
{
	mSpeed = mStartSpeed;
	mHealth = (int)mStartHealth;
	mMaxHealth = (int)mStartHealth;
}

// -----------------------------------------------------------------------------

bool Player::hit(Time pTimeHit)
{
	if (pTimeHit.asMilliseconds() - mLastHit.asMilliseconds() > 200)
	{
		mLastHit = pTimeHit;
		mHealth -= mDamageAmount;
		return true;
	}
	else
	{
		return false;
	}
}

// -----------------------------------------------------------------------------

void Player::update(float pElapsedTime, Vector2i pMousePos)
{
	if (mUpPressed)
	{
		mPos.y -= mSpeed * pElapsedTime;
	}

	if (mDownPressed)
	{
		mPos.y += mSpeed * pElapsedTime;
	}

	if (mRightPressed)
	{
		mPos.x += mSpeed * pElapsedTime;
	}

	if (mLeftPressed)
	{
		mPos.x -= mSpeed * pElapsedTime;
	}

	mSprite.setPosition(mPos);

	if (mPos.x > (mArena.width - mTileSize))
	{
		mPos.x = (float)(mArena.width - mTileSize);
	}

	if (mPos.x < mArena.left + mTileSize)
	{
		mPos.x = (float)(mArena.left + mTileSize);
	}

	if (mPos.y > mArena.height - mTileSize)
	{
		mPos.y = (float)(mArena.height - mTileSize);
	}

	if (mPos.y < mArena.top + mTileSize)
	{
		mPos.y = (float)(mArena.top + mTileSize);
	}

	// calculate the angle the player is facing
	float angle = (atan2(pMousePos.y - mResolution.y / 2.0f,
		pMousePos.x - mResolution.x / 2.0f) * 180.0f) / 3.141f;

	mSprite.setRotation(angle);
}

// -----------------------------------------------------------------------------

void Player::upgradeSpeed()
{
	// 20% speed upgrade
	mSpeed += (mStartSpeed * 0.2f);
}

// -----------------------------------------------------------------------------

void Player::upgradeHealth()
{
	// 20% max health upgrade
	mMaxHealth += (int)(mStartHealth * 0.2f);
}

// -----------------------------------------------------------------------------

void Player::increaseHealthLevel(int pAmount)
{
	mHealth += pAmount;

	// but not beyond maximum
	if (mHealth > mMaxHealth)
	{
		mHealth = mMaxHealth;
	}
}

// -----------------------------------------------------------------------------




// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

