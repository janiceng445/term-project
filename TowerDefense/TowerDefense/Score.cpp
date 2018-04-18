#include "Score.h"

Score::Score() {}

int Score::getTotal() {
	return total;
}

int Score::getHighScore() {
	return highScore;
}

void Score::add(int amount) {
	total += amount;
}

void Score::subtract(int amount) {
	total += amount;
}

void Score::setTotal(int amount) {
	total = amount;
}
