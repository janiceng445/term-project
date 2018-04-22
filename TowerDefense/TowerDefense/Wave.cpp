#include "Wave.h"

Wave::Wave()
{
	round = 0;
	num_Skelly = 0;
	num_Rhino = 0;
	num_Lancer = 0;
	num_Demon = 0;
	num_Gunner = 0;
	num_Boss = 0;
}
Wave::Wave(int roundNumber, int s, int r, int l, int d, int g, int b)
{
	round = roundNumber;
	num_Skelly = s;
	num_Rhino = r;
	num_Lancer = l;
	num_Demon = d;
	num_Gunner = g;
	num_Boss = b;
	totalMobs = s + r + l + d + g + b;
}
// Get round number
int Wave::getRoundNumber()
{
	return round;
}
// Deduct # of mobs
void Wave::deductMob()
{
	totalMobs--;
}
// Get # of mobs
int Wave::getNumMobs()
{
	return totalMobs;
}
Wave::~Wave()
{
}
