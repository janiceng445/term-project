#include "Wave.h"

Wave::Wave()
{
	round = 0;
	num_Skelly = 0;
	num_Rhino = 0;
	num_Lancer = 0;
	num_Demon = 0;
}
Wave::Wave(int roundNumber, int s, int r, int l, int d)
{
	round = roundNumber;
	num_Skelly = s;
	num_Rhino = r;
	num_Lancer = l;
	num_Demon = d;
	totalMobs = s + r + l + d;
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
