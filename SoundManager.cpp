// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "SoundManager.h"

// -----------------------------------------------------------------------------

SoundManager::SoundManager()
{
	mHitBuffer.loadFromFile("sounds/hit.wav");
	mSplatBuffer.loadFromFile("sounds/splat.wav");
	mShootBuffer.loadFromFile("sounds/shoot.wav");
	mReloadBuffer.loadFromFile("sounds/reload.wav");
	mReloadFailedBuffer.loadFromFile("sounds/reload_failed.wav");
	mPowerupBuffer.loadFromFile("sounds/powerup.wav");
	mPickUpBuffer.loadFromFile("sounds/pickup.wav");

	mHit.setBuffer(mHitBuffer);
	mSplat.setBuffer(mSplatBuffer);
	mShoot.setBuffer(mShootBuffer);
	mReload.setBuffer(mReloadBuffer);
	mReloadFailed.setBuffer(mReloadFailedBuffer);
	mPowerup.setBuffer(mPowerupBuffer);
	mPickup.setBuffer(mPickUpBuffer);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


