#ifndef __PARTICLES_H__
#define __PARTICLES_H__

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "Collisions.h"

#define MAX_ACTIVE_PARTICLES 300

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

enum class ParticleType 
{
	NONE,
	SHOT,
	SMOKE

};

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;					//Particle animation
	SDL_Rect rect;					//Particle rectangle
	SDL_Texture* tex;				//Particle texture
	ParticleType type;				//Particle type
	float speed;					//Particle speed
	float size;						//Particle size
	uint born;
	uint life;  					//Particle life
	double angle;					//Particle angle
	fPoint position;					//Particle position
	SDL_Color initialColor;			//Particle color inicial
	SDL_Color finalColor;			//Particle color final
	uint fx = 0;					//Particle fx
	bool fxPlayed = false;			//Particle fx active
	int damage;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class Particles : public Module
{
public:
	Particles();
	~Particles();

	bool Start();
	bool Update(float dt);
	bool CleanUp();
	//void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, float size, uint delay = 0, COLLIDER_TYPE colliderType = COLLIDER_TYPE::COLLIDER_NONE, ParticleType type = ParticleType::NONE, double angle = 0.0f, uint life = 0, int damage = 0, float speed = 0);

	
	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
private:


public:

	Particle smoke;
	Particle shot;
};

#endif // __PARTICLES_H__