// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Bullet.h"

// -----------------------------------------------------------------------------

Bullet::Bullet()
	: mPos()
	, mShape()
	, mSpeed(1000.0f)
	, mDistanceX()
	, mDistanceY()
	, mMaxX()
	, mMinX()
	, mMaxY()
	, mMinY()
	, mInFlight(false)
	, mOutOfRange(false)
{
	mShape.setSize(Vector2f(2, 2));
}

// -----------------------------------------------------------------------------

void Bullet::stop()
{
	mInFlight = false;
	mOutOfRange = true;
}

// -----------------------------------------------------------------------------

void Bullet::shoot(float pStartX, float pStartY, float pTargetX, float pTargetY)
{
	// keep track of the bullet
	mInFlight = true;
	mPos.x = pStartX;
	mPos.y = pStartY;

	// calculate the gradient of the flight path
	float gradient = (pStartX - pTargetX) / (pStartY - pTargetY);

	// any gradient less than 1 needs to be negative
	if (gradient < 0)
	{
		gradient *= -1;
	}

	// calculate the ratio between x and y
	float ratioXY = mSpeed / (1 + gradient);

	// set the speed horizontally and vertically
	mDistanceY = ratioXY;
	mDistanceX = ratioXY * gradient;

	// point bullet in the right direction
	if (pTargetX < pStartX)
	{
		mDistanceX *= -1;
	}

	if (pTargetY < pStartY)
	{
		mDistanceY *= -1;
	}

	// set a max range of 1000 pixels
	float range = 1000;
	mMinX = pStartX - range;
	mMaxX = pStartX + range;
	mMinY = pStartY - range;
	mMaxY = pStartY + range;

	// position the bullet ready to be drawn
	mShape.setPosition(mPos);
}

// -----------------------------------------------------------------------------

void Bullet::update(float pElapsedTime)
{
	mPos.x += mDistanceX * pElapsedTime;
	mPos.y += mDistanceY * pElapsedTime;

	// move the bullet
	mShape.setPosition(mPos);

	// has bullet gone out of range?
	if (mPos.x < mMinX || mPos.x > mMaxX
		|| mPos.y < mMinY || mPos.y > mMaxY)
	{
		mInFlight = false;
		mOutOfRange = true;
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


