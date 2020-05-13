#include "p2Log.h"
#include "j1App.h"
#include "j1Particles.h"
#include "j1Textures.h"
#include "j1Window.h"
#include "j1Render.h"

j1Particle::j1Particle()
{
	name = "particles";

}

j1Particle::~j1Particle()
{
}

bool j1Particle::Start()
{
	LOG("Loading particles");

	graphics = App->tex->Load("Resources/particles/Shot.png");
	shot.anim.PushBack({ 0,0,500,500 });
	shot.anim.PushBack({ 0,0,500,500 });
	shot.anim.PushBack({ 0,0,500,500 });
	shot.anim.loop = 1;
	shot.type = ParticleType::SHOT;
	shot.life = 1000;

	return true;
}

bool j1Particle::Update(float dt)
{
	for (int i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else 
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame(dt)));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}
	return true;
}


bool j1Particle::CleanUp()
{
	LOG("Unloading particles");
	App->tex->UnLoad(graphics);

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

void j1Particle::AddParticle(const Particle& particle, int x, int y, Uint32 delay, ParticleType type)
{

	for (int i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = delay;
			LOG("Delay %d", p->born);
			p->position.x = x;
			p->position.y = y;
			p->type = type;
			active[i] = p;
			break;
		}
	}
}

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
	bool ret = true;

	switch (type)
	{
	case ParticleType::NONE:
		ret = false;
		break;

	case ParticleType::SHOT:
		life -= 5;
		LOG("Life %d", life);
		position.x += 10;

		if (life > 0)
		{
			if ( born > life)
				ret = false;
			LOG("Born %d", born);

		}
		else if (anim.Finished())
		{
			ret = false;
		}

	}

	return ret;
}