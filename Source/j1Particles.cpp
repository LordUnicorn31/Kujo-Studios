#include "p2Log.h"
#include "j1App.h"
#include "j1Particles.h"
#include "j1Textures.h"
#include "j1Window.h"

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
	rotation = 0.0f;
}

Particle::Particle(const Particle& p) :
	anim(p.anim), tex(p.tex), type(p.type), fx(p.fx), position(p.position), speed(p.speed),
	born(p.born), life(p.life), rotation(p.rotation)
{}

Particle::~Particle()
{
	//destry collider
}

bool Particle::Update()
{
	//Update all the particle characteristics depending on the particle type
	return true;
}

j1Particle::j1Particle()
{
	name = "particles";

	for (int i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	shot->anim.PushBack({});
	shot->type = ParticleType::SHOT;

}

j1Particle::~j1Particle()
{
}

bool j1Particle::Start()
{
	LOG("Loading particles");

	shot->tex = App->tex->Load("Resources/particles/shot.png");

	return true;
}

bool j1Particle::Update(float dt)
{
	return true;
}


bool j1Particle::CleanUp()
{
	LOG("Unloading particles");
	App->tex->UnLoad(shot->tex);

	for (int i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}
	return true;
}