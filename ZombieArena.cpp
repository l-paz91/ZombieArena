// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "ZombieArena.h"

// -----------------------------------------------------------------------------

int ZombieArena::createBackground(VertexArray& pVA, IntRect pArena)
{
	const int TILE_SIZE = 50;
	const int TILE_TYPE = 3;
	const int VERTS_IN_QUAD = 4;
	int worldWidth = pArena.width / TILE_SIZE;
	int worldHeight = pArena.height / TILE_SIZE;

	pVA.setPrimitiveType(Quads);
	pVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

	int currentVertex = 0;

	for (int w = 0; w < worldWidth; ++w)
	{
		for (int h = 0; h < worldHeight; ++h)
		{
			// position each vertex in the current quad
			pVA[currentVertex].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			pVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
			pVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
			pVA[currentVertex + 3].position = Vector2f((w * TILE_SIZE), (h * TILE_SIZE) + TILE_SIZE);

			// define the position in the texture for current quad
			// either grass, stone, bush or wall
			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1)
			{
				// use the wall texture
				pVA[currentVertex].texCoords = Vector2f(0, 0 + TILE_TYPE * TILE_SIZE);
				pVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, TILE_TYPE * TILE_SIZE);
				pVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPE * TILE_SIZE);
				pVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + TILE_TYPE * TILE_SIZE);
			}
			else
			{
				// use a random floor texture
				srand((int)time(0) + h * w - h);

				int mORG = (rand() % TILE_TYPE);
				int verticalOffset = mORG * TILE_SIZE;
				pVA[currentVertex].texCoords = Vector2f(0, verticalOffset);
				pVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, verticalOffset);
				pVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				pVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
			}

			//position ready for next four vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return TILE_SIZE;
}

// -----------------------------------------------------------------------------

void ZombieArena::createHorde(int pNumZombies, IntRect pArena)
{

}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

