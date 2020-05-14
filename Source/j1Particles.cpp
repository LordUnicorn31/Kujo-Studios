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
			App->render->DrawQuad(p->rect,p->initialColor.r,p->initialColor.g,p->initialColor.b,p->initialColor.a,true);
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
			switch (type)
			{
			case ParticleType::NONE:
				break;
			case ParticleType::SHOT:
				Particle* p = new Particle(particle);
				p->anim = shot.anim;
				p->size = 1;
				p->rect.x = x;
				p->rect.y = y;
				p->rect.w = 10 * p->size;
				p->rect.h = 10 * p->size;
				p->initialColor = { 255,255,0,255 };
				p->finalColor = { 0,255,255,255 };
				p->type = type;
				active[i] = p;
				break;
			}
		}
	}
}

Particle::Particle()
{
	tex = nullptr;
	type = ParticleType::NONE;
	speed.SetToZero();
	rotation = 0.0f;
}

Particle::Particle(const Particle& p) 
{
	 this->anim = p.anim;
	 this->rect = p.rect;
	 this->tex = p.tex;
	 this->type = p.type;
	 this->speed = p.speed;
	 this->size = p.size;
	 this->life = p.life;
	 this->rotation = p.rotation;
	 this->initialColor = p.initialColor;
	 this->finalColor = p.finalColor;
	 this->fx = p.fx;
	 this->fx_played = p.fx_played;
}

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
		rect.x++;
		if (life < 0) {
			ret = false;
		}
	}

	return ret;
}