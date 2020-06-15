#include "p2Log.h"
#include "Application.h"
#include "Particles.h"
#include "Textures.h"
#include "Window.h"
#include "Render.h"

Particles::Particles()
{
	name = "particles";

}

Particles::~Particles()
{
}

bool Particles::Start()
{
	LOG("Loading particles");

	graphics = App->tex->Load("Resources/gui/particle.png");
	shot.anim.PushBack({ 144,64,11,18 });
	shot.anim.PushBack({ 160,61,11,18 });
	shot.anim.PushBack({ 178,58,11,18 });
	shot.anim.speed = 1.0f;
	shot.anim.loop = false;

	smoke.anim.PushBack({ 0,0,255,255 });
	smoke.anim.PushBack({ 0,0,255,255 });

	return true;
}

bool Particles::Update(float dt)
{
	for (int i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update(dt) == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else
		{
			if (p->type == ParticleType::SHOT && p->delay <=0) 
			{
				if (p->angle == 0 || p->angle == 360)
				{
					p->position.y -= p->speed *dt;
				}
				else if (p->angle == 45)
				{
					p->position.y -= (p->speed *0.5f) * dt;
					p->position.x += (p->speed * 0.5f) * dt;
				}
				else if (p->angle == 90)
				{
					p->position.x += p->speed * dt;
				}
				else if (p->angle == 135)
				{
					p->position.y += (p->speed * 0.5f) * dt;
					p->position.x += (p->speed * 0.5f) * dt;
				}
				else if (p->angle == 180)
				{
					p->position.y += p->speed * dt;
				}
				else if (p->angle == 225)
				{
					p->position.y += (p->speed * 0.5f) * dt;
					p->position.x -= (p->speed * 0.5f) * dt;
				}
				else if (p->angle == 270)
				{
					p->position.x -= p->speed * dt;
				}
				else if (p->angle == 315)
				{
					p->position.y -= (p->speed * 0.5f) * dt;
					p->position.x -= (p->speed * 0.5f) * dt;
				}

				App->render->DrawQuad({ p->position.x, p->position.y, (int)p->size, (int)p->size }, p->initialColor.r, p->initialColor.g, p->initialColor.b, p->initialColor.a, true, true);
				
				if (p->fxPlayed == false)
				{
					p->fxPlayed = true;
					// Play particle fx here
				}
				if (p->collider != nullptr)
				{
					p->collider->SetPos(p->position.x, p->position.y);
				}
			}
			else if (p->type == ParticleType::SMOKE)
			{
				App->render->Blit(graphics, p->rect.x, p->rect.y, &p->anim.GetCurrentFrame(dt));
				if (p->fxPlayed == false)
				{
					p->fxPlayed = true;
					// Play particle fx here
				}
			}
		}
	
	}
	return true;
}



bool Particles::CleanUp()
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

void Particles::AddParticle(const Particle& particle, int x, int y, float size, float delay, COLLIDER_TYPE colliderType, ParticleType type, double angle, float life, int damage, float speed)
{

	for (int i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == NULL)
		{
			Particle* p = new Particle(particle);

			switch (type)
			{
			case ParticleType::NONE:	
				p->type = type;
				break;
			case ParticleType::SHOT:
				p->delay = delay;
				p->life = life + delay;
				p->size = size;
				p->position.x = x;
				p->position.y = y;
				p->rect.x = (int)p->position.x;
				p->rect.y = (int)p->position.y;
				p->rect.w =  p->size;
				p->rect.h =  p->size;
				p->initialColor = { 255,255,0,255 };
				p->finalColor = { 0,255,255,255 };
				p->type = type;
				p->angle = angle;
				p->speed = speed;
				p->damage = damage;
				if (colliderType != COLLIDER_TYPE::COLLIDER_NONE)
				{
					p->collider = App->collisions->AddCollider(p->rect, colliderType, this);
				}
				break;

			case ParticleType::SMOKE:
				p->anim = smoke.anim;
				p->type = type;
				break;
			}

			active[i] = p;
			break;
		}
	}
}

Particle::Particle()
{
	tex = nullptr;
	type = ParticleType::NONE;
	speed = 0.0f;
	angle = 0.0f;
	life = 0.0f;
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
	 this->angle = p.angle;
	 this->initialColor = p.initialColor;
	 this->finalColor = p.finalColor;
	 this->fx = p.fx;
	 this->fxPlayed = p.fxPlayed;
	 this->damage = p.damage;
}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->toDelete = true;
}

bool Particle::Update(float dt)
{
	//Update all the particle characteristics depending on the particle type
	bool ret = true;
	life -= dt;
	if (delay >= 0)
		delay -= dt;
	if (life <= 0)
	{
			ret = false;
	}
	else if (anim.Finished())
		ret = false;

	return ret;
}