#pragma once
#ifndef SCORE_H
#define SCORE_H

class Score {
private:
	int total = 0;
	int highScore = 0;

public:
	Score();
	int getTotal();
	int getHighScore();
	void add(int amount);
	void subtract(int amount);
	void setTotal(int amount);
};

#endif
