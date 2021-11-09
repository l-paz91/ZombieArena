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
	int createBackground(VertexArray& pVA, IntRect pArena);
	void createHorde(int pNumZombies, IntRect pArena);

	vector<Zombie> mv_Zombies;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !ZombieArena_H