// -----------------------------------------------------------------------------
#ifndef SoundManager_H
#define SoundManager_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Audio.hpp>

using namespace sf;

// -----------------------------------------------------------------------------

struct SoundManager
{

	SoundManager();

	Sound mHit;
	Sound mSplat;
	Sound mShoot;
	Sound mReload;
	Sound mReloadFailed;
	Sound mPowerup;
	Sound mPickup;

private:
	SoundBuffer mHitBuffer;
	SoundBuffer mSplatBuffer;
	SoundBuffer mShootBuffer;
	SoundBuffer mReloadBuffer;
	SoundBuffer mReloadFailedBuffer;
	SoundBuffer mPowerupBuffer;
	SoundBuffer mPickUpBuffer;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !SoundManager_H