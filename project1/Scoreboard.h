/**
 * \file Scoreboard.h
 *
 * \author Team Zuse
 *
 * header file for the scoreboard class which tracks and displays the score
 */

#pragma once
#include "TextObject.h"
class CScreen;

/// Class to track and display the score
class CScoreboard : public CTextObject
{
public:
	/// default constructor (disabled)
	CScoreboard() = delete;

	/// copy constructor (disabled)
	CScoreboard(const CScoreboard&) = delete;

	/// constructor
	/// \param screen the screen we are playing on
	CScoreboard(CScreen* screen);

	/// draws the scoreboard to the graphics passed as a parameter
	/// \param graphics
	void Draw(Gdiplus::Graphics* graphics) override;

	/// adds to the amount correct displayed by the scoreboard
	/// \param  amount amount that the score increments by, defaults to 1 for now.
	void AddCorrect(int amount = 1) { mCorrect += amount; }

	/// adds to the amount incorrect displayed by the scoreboard
	/// \param  amount amount that the value increments by, defaults to 1 for now.
	void AddIncorrect(int amount = 1) { mIncorrect += amount; }

	/// adds to the amount missed displayed by the scoreboard
	/// \param  amount amount that the value increments by, defaults to 1 for now.
	void AddMissed(int amount = 1) { mMissed += amount; }

	/// gets number of correct items hit for testing
	/// \return num correct
	int GetCorrect() { return mCorrect; }

	/// gets number of incorrect items hit for testing
	/// \return num incorrect
	int GetIncorrect() { return mIncorrect; }

	/// gets number of missed items hit for testing
	/// \return num missed
	int GetMissed() { return mMissed; }

	/// Rotate function for pause
	/// \param point Vector of mouse location
	void RotateImage(CPoint point) { SetAngle(0); };

private:
	/// Amount correct
	int mCorrect;
	/// Amount incorrect
	int mIncorrect;
	/// Amount missed
	int mMissed;
};

