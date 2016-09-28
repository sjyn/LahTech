#pragma once
#include <string>

class ScoreKeeper
{
public:
	ScoreKeeper(void);
	~ScoreKeeper(void);

	//pass in a string and put cosmos score at begginning and Balloons at end
	//WILL NOT ALTER LENGTH OF STRING (fails if string not long enough)
	bool getDisplayString(std::string &scoreString);

	//typically its 1 at a time
	inline  void incScoreBalloon(int i){scoreBalloon+=i;};
	inline  void incScoreCosmo(int i){scoreCosmo+=i;};
	inline  void resetScores(){scoreBalloon=0;scoreCosmo=0;};

private:
	//scores
	int scoreBalloon;
	int scoreCosmo;
};
