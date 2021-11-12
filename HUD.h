// -----------------------------------------------------------------------------
#ifndef HUD_H
#define HUD_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include <string>

using namespace sf;

// -----------------------------------------------------------------------------

struct Hud
{
	Hud(float pResX, float pResY);

	// for home/game over screen
	Sprite msGameOver;

	// create a view for the hud
	View mHudView;

	// create a sprite for the ammo icon
	Sprite msAmmoIcon;
	
	// load the font
	Font mFont;
	Font mDebugFont;

	// text
	Text mPausedText;
	Text mGameOverText;
	Text mLevelUpText;
	Text mAmmoText;
	Text mScoreText;
	Text mHiScoreText;
	Text mZombiesLeftText;
	Text mWaveNumberText;
	Text mDebugText;

	// Health Bar
	RectangleShape mHealthBar;

	// update functions
	void updateHUD(RenderWindow& pWindow);
	void updateAmmoText(int pBulletsInClip, int pBulletsSpare);
	void updateScoreText(int pScore);
	void updateHiScoreText(int pHiScore);
	void updateWaveText(int pWave);
	void updateZombiesLeftText(int pZombiesLeft);

private:
	void setUpText(Text& pText, const Font& pFont, int pCharSize, float pX,
		float pY, const std::string& pString = "", const Color& pColour = Color::White);
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !HUD_H