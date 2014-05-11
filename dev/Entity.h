#ifndef ENTITY_H
#define	ENTITY_H
#include <string>

#include <SDL/SDL.h>

using namespace std;

struct Sides{
    SDL_Surface * Left;
    SDL_Surface * Right;
};


class Entity
{
public:
    float x, y;
    float xVel, yVel;
    Entity();
    string Name;
    void move(Entity Ent, Uint32 deltaTicks);
    Sides Tile;
    int JumpSpeed;
    bool onGround;
    void Jump();
};

#endif	/* ENTITY_H */

