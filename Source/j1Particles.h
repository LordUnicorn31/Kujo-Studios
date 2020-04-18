#ifndef __j1PARTICLES_H__
#define __j1PARTICLES_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
//#include "j1Collision.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
//struct Collider;
//enum COLLIDER_TYPE;

enum class ParticleType 
{
	NONE,
	SHOT

};

struct Particle
{
	Animation anim;
	//Collider* collider = nullptr;
	SDL_Texture* tex = nullptr;
	ParticleType type;
	uint fx = 0;
	fPoint position;
	fPoint speed;
	uint born = 0;
	uint life = 0;
	float rotation;
	bool fx_played = false;


	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class j1Particle : public j1Module
{
public:
	j1Particle();
	~j1Particle();

	bool Start();
	bool Update(float dt);
	bool CleanUp();
	//void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y,  uint delay = 0);

	Particle* active[MAX_ACTIVE_PARTICLES];

private:


public:

	Particle* shot;
};

#endif // __j1PARTICLES_H__