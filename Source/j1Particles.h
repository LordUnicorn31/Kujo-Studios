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
	SHOT,
	SMOKE

};

struct Particle
{
	Animation anim;					//Particle animation
	SDL_Rect rect;					//Particle rectangle
	SDL_Texture* tex;				//Particle texture
	ParticleType type;				//Particle type
	fPoint speed;					//Particle speed
	float size;						//Particle size
	uint born;
	uint life;  					//Particle life
	float rotation;					//Particle rotation
	SDL_Color initialColor;			//Particle color inicial
	SDL_Color finalColor;			//Particle color final
	uint fx = 0;					//Particle fx
	bool fx_played = false;			//Particle fx active

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

	void AddParticle(const Particle& particle, int x, int y,  uint delay = 0, ParticleType type = ParticleType::NONE);

	
	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
private:


public:

	Particle smoke;
	Particle shot;
};

#endif // __j1PARTICLES_H__