// -----------------------------------------------------------------------------
#ifndef ZombieArena_H
#define ZombieArena_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <SFML/Graphics.hpp>

#include "Zombie.h"

// -----------------------------------------------------------------------------

using namespace sf;

struct ZombieArena
{
	~ZombieArena()
	{
		// clean up vector
		if (!mv_Zombies.empty())
		{
			for (uint32 i = 0; i < mv_Zombies.size(); ++i)
			{
				delete mv_Zombies[i];
				mv_Zombies[i] = nullptr;
			}
		}
	}
	 
	int createBackground(VertexArray& pVA, IntRect pArena);
	void createHorde(int pNumZombies, IntRect pArena);

	vector<Zombie*> mv_Zombies;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !ZombieArena_H