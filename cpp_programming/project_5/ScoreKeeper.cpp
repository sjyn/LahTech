#include "ScoreKeeper.h"

const std::string COSMO_SCORE_PREFIX		= "COSMO = ";
const int  LEN_COSMO_SCORE_PREFIX	= 8;
const std::string BALLOON_SCORE_PREFIX = "BALLOONS = "; 
const int  LEN_BALLOON_SCORE_PREFIX	= 11;
const int  SPACES_FOR_SCORE			= 6;

ScoreKeeper::ScoreKeeper(void)
{
	resetScores();
}

ScoreKeeper::~ScoreKeeper(void)
{
}

bool ScoreKeeper::getDisplayString(std::string &scoreString){
	//TODO calculate the score that goes in the display string here
	int csdiff = LEN_COSMO_SCORE_PREFIX + SPACES_FOR_SCORE;
	std::string scoreAsString=std::to_string(scoreCosmo);
	int lengthOfScoreString=(int)scoreAsString.length();
	csdiff = abs( csdiff - lengthOfScoreString );
	scoreString = COSMO_SCORE_PREFIX + std::to_string(scoreCosmo);
	for (short i = 0; i < csdiff; i++)
	{
		scoreString += " ";
	}
	int balldiff = LEN_BALLOON_SCORE_PREFIX + SPACES_FOR_SCORE;
	int len = (int)scoreString.length();
	for (short i = 0; i < 80 - (balldiff + len); i++)
	{
		scoreString += " ";
	}
	scoreString += BALLOON_SCORE_PREFIX + std::to_string(scoreBalloon);
	return true;
}