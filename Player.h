// -----------------------------------------------------------------------------
#ifndef Player_H
#define Player_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

using namespace sf;

// -----------------------------------------------------------------------------

class Player
{
public:
	Player();
	
	void spawn(IntRect pArena, Vector2f pResolution, int pTileSize);
	void resetPlayerStats();

	bool hit(Time pTimeHit);

	const Time&		getLastHitTime()	const	{ return mLastHit; }
	const FloatRect getPos()			const	{ return mSprite.getGlobalBounds(); }
	const Vector2f& getCenter()			const	{ return mPos; }
	const float		getRotation()		const	{ return mSprite.getRotation(); }
	const Sprite&	getSprite()			const	{ return mSprite; }
	const int&		getHealth()			const	{ return mHealth; }

	void moveLeft()		{ mLeftPressed	= true; }
	void moveRight()	{ mRightPressed = true; }
	void moveUp()		{ mUpPressed	= true; }
	void moveDown()		{ mDownPressed	= true; }
	void stopLeft()		{ mLeftPressed	= false; }
	void stopRight()	{ mRightPressed = false; }
	void stopUp()		{ mUpPressed	= false; }
	void stopDown()		{ mDownPressed	= false; }

	void update(float pElapsedTime, Vector2i pMousePos);
	void upgradeSpeed();
	void upgradeHealth();
	void increaseHealthLevel(int pAmount);


private:
	Vector2f mPos;
	Vector2f mResolution;

	IntRect mArena;

	Sprite mSprite;

	Time mLastHit;

	const float mStartSpeed;
	const float mStartHealth;
	float mSpeed;

	int mTileSize;
	int mHealth;
	int mMaxHealth;
	const int mDamageAmount;

	bool mUpPressed;
	bool mDownPressed;
	bool mLeftPressed;
	bool mRightPressed;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Player_H