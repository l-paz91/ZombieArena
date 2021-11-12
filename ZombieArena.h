// -----------------------------------------------------------------------------
#ifndef ZombieArena_H
#define ZombieArena_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include "Zombie.h"

#include "std_lib_facilities.h"
// -----------------------------------------------------------------------------

using namespace sf;

struct ZombieArena
{
	~ZombieArena()
	{
		// clean up vector
		if (!mv_Zombies.empty())
		{
			for (uint32_t i = 0; i < mv_Zombies.size(); ++i)
			{
				delete mv_Zombies[i];
				mv_Zombies[i] = nullptr;
			}
		}
	}
	 
	int createBackground(VertexArray& pVA, IntRect pArena);
	void createHorde(int pNumZombies, IntRect pArena);

	void loadHiScoreFromFile(int& pHiScore);
	void writeHiScoreToFile(int pHiScore);

	Vector<Zombie*> mv_Zombies;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !ZombieArena_H