// -----------------------------------------------------------------------------
#ifndef Bullet_H
#define Bullet_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

using namespace sf;

// -----------------------------------------------------------------------------

class Bullet
{
public:
	Bullet();
	
	void stop();
	void shoot(float pStartX, float pStartY, float pTargetX, float pTargetY);
	void update(float pElapsedTime);

	const FloatRect getPos() const { return mShape.getGlobalBounds(); }
	const RectangleShape& getShape() const { return mShape; }
	const bool isInFlight() const { return mInFlight; }
	const bool isOutOfRange() const { return mOutOfRange; }

private:
	Vector2f mPos;
	RectangleShape mShape;

	float mSpeed;
	float mDistanceX;
	float mDistanceY;
	float mMaxX, mMinX, mMaxY, mMinY;

	bool mInFlight, mOutOfRange;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Bullet_H