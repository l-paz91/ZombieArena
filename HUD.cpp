// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "HUD.h"

#include "TextureHolder.h"

// -----------------------------------------------------------------------------

Hud::Hud(float pResX, float pResY)
	: msGameOver()
	, mHudView(FloatRect(0, 0, pResX, pResY))
	, msAmmoIcon()
	, mFont()
	, mDebugFont()
	, mPausedText()
	, mGameOverText()
	, mLevelUpText()
	, mAmmoText()
	, mScoreText()
	, mHiScoreText()
	, mZombiesLeftText()
	, mWaveNumberText()
	, mDebugText()
	, mHealthBar()
{
	const string hudFilename = "graphics/background.png";
	msGameOver.setTexture(TextureHolder::getTexture(hudFilename));
	msGameOver.setPosition(0, 0);

	const string ammoFilename = "graphics/ammo_pickup.png";
	msAmmoIcon.setTexture(TextureHolder::getTexture(ammoFilename));
	msAmmoIcon.setPosition(20, 980);

	mFont.loadFromFile("fonts/Stranger back in the Night.ttf");
	mDebugFont.loadFromFile("fonts/javatext.ttf");

	setUpText(mPausedText, mFont, 155, 400, 400, "Press Enter \nto continue");
	setUpText(mGameOverText, mFont, 80, 150, 250, "Press Enter to play");

	stringstream ss;
	ss  << "1 - Increased rate of fire"
		<< "\n2 - Increased clip size (next reload)"
		<< "\n3 - Increased max health"
		<< "\n4 - Increase run speed"
		<< "\n5 - Health pickups spawn more frequently with better healing"
		<< "\n6 - Ammo pickups spawn more frequently with better more bullets";
	setUpText(mLevelUpText, mFont, 80, 150, 250, ss.str());
	ss.str("");

	setUpText(mAmmoText, mFont, 55, 20, 0);
	setUpText(mScoreText, mFont, 55, 20, 80);
	setUpText(mHiScoreText, mFont, 55, 1400, 0, "Hi-Score: 0");
	setUpText(mZombiesLeftText, mFont, 55, 1500, 980, "Zombies: 100");
	setUpText(mWaveNumberText, mFont, 55, 1250, 980, "Wave: 0");
	setUpText(mDebugText, mDebugFont, 25, 20, 220);

	mHealthBar.setFillColor(Color::Red);
	mHealthBar.setPosition(450, 980);
}

// -----------------------------------------------------------------------------

void Hud::updateHUD(RenderWindow& pWindow)
{
	pWindow.setView(mHudView);

	pWindow.draw(msAmmoIcon);
	pWindow.draw(mAmmoText);
	pWindow.draw(mScoreText);
	pWindow.draw(mHiScoreText);
	pWindow.draw(mHealthBar);
	pWindow.draw(mWaveNumberText);
	pWindow.draw(mZombiesLeftText);
}

// -----------------------------------------------------------------------------

void Hud::updateAmmoText(int pBulletsInClip, int pBulletsSpare)
{
	stringstream ss;
	ss << pBulletsInClip << "/" << pBulletsSpare;
	mAmmoText.setString(ss.str());
}

// -----------------------------------------------------------------------------

void Hud::updateScoreText(int pScore)
{
	stringstream ss;
	ss << "Score: " << pScore;
	mScoreText.setString(ss.str());
}

// -----------------------------------------------------------------------------

void Hud::updateHiScoreText(int pHiScore)
{
	stringstream ss;
	ss << "Hi-Score: " << pHiScore;
	mHiScoreText.setString(ss.str());
}

// -----------------------------------------------------------------------------

void Hud::updateWaveText(int pWave)
{
	stringstream ss;
	ss << "Wave: " << pWave;
	mWaveNumberText.setString(ss.str());
}

// -----------------------------------------------------------------------------

void Hud::updateZombiesLeftText(int pZombiesLeft)
{
	stringstream ss;
	ss << "Zombies: " << pZombiesLeft;
	mZombiesLeftText.setString(ss.str());
}

// -----------------------------------------------------------------------------

void Hud::setUpText(
	  Text& pText
	, const Font& pFont
	, int pCharSize
	, float pX
	, float pY
	, const string& pString /*= ""*/
	, const Color& pColour /*= Color::White*/)
{
	pText.setFont(pFont);
	pText.setCharacterSize(pCharSize);
	pText.setFillColor(pColour);
	pText.setPosition(pX, pY);
	pText.setString(pString);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


