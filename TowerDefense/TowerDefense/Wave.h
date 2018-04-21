#pragma once
#include <iostream>
class Wave
{
private:
	int round;
	int num_Skelly;
	int num_Rhino;
	int num_Lancer;
	int num_Demon;
	int num_Gunner;
	int totalMobs;

public:
	Wave();
	Wave(int roundNumber, int s, int r, int l, int d, int g);

	// Get round number
	int getRoundNumber();
	// Deduct # of mobs
	void deductMob();
	// Get # of mobs
	int getNumMobs();
	~Wave();
};

