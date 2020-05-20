#include "p2Log.h"
#include "App.h"
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

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks()/1000 >= p->born)
		{
			if (p->type == ParticleType::SHOT) 
			{
				if (p->angle == 0 || p->angle == 360)
				{
					p->position.y -= 100 * dt;
				}
				else if (p->angle == 45)
				{
					p->position.y -= 50 * dt;
					p->position.x += 50 * dt;
				}
				else if (p->angle == 90)
				{
					p->position.x += 100 * dt;
				}
				else if (p->angle == 135)
				{
					p->position.y += 50 * dt;
					p->position.x += 50 * dt;
				}
				else if (p->angle == 180)
				{
					p->position.y += 100 * dt;
				}
				else if (p->angle == 225)
				{
					p->position.y += 50 * dt;
					p->position.x -= 50 * dt;
				}
				else if (p->angle == 270)
				{
					p->position.x -= 100 * dt;
				}
				else if (p->angle == 315)
				{
					p->position.y -= 50 * dt;
					p->position.x -= 50 * dt;
				}

				App->render->Blit(graphics, (int)p->position.x, (int)p->position.y, &p->anim.GetCurrentFrame(dt), true, App->render->renderer, 3, 1, p->angle);
				//LOG("life %u", p->life);
				if (p->fx_played == false)
				{
					p->fx_played = true;
					// Play particle fx here
				}
				if (p->collider != nullptr)
				{
					p->collider->SetPos(p->position.x - App->render->camera.x, p->position.y);
				}
			}
			else if (p->type == ParticleType::SMOKE)
			{
				App->render->Blit(graphics, p->rect.x, p->rect.y, &p->anim.GetCurrentFrame(dt));
				if (p->fx_played == false)
				{
					p->fx_played = true;
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

void Particles::AddParticle(const Particle& particle, int x, int y, uint delay, COLLIDER_TYPE colliderType, ParticleType type, double angle, uint life)
{

	for (int i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			switch (type)
			{
			case ParticleType::NONE:	
				p->type = type;
				break;
			case ParticleType::SHOT:
				p->born = SDL_GetTicks()/1000 + delay;
				p->anim = shot.anim;
				p->size = 1;
				p->position.x = x;
				p->position.y = y;
				p->rect.x = (int)p->position.x;
				p->rect.y = (int)p->position.y;
				p->rect.w = 10 * p->size;
				p->rect.h = 10 * p->size;
				p->initialColor = { 255,255,0,255 };
				p->finalColor = { 0,255,255,255 };
				p->type = type;
				p->angle = angle;
				p->life = life;
				if (colliderType != COLLIDER_TYPE::COLLIDER_NONE)
				{
					p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(App->GetDT()), colliderType, this);
				}
				break;

			case ParticleType::SMOKE:
				p->born = SDL_GetTicks()/1000 + delay;
				p->anim = smoke.anim;
				p->type = type;
				break;
			}

			active[i] = p;
			LOG("particles %d", i);
			break;
		}
	}
}

Particle::Particle()
{
	tex = nullptr;
	type = ParticleType::NONE;
	speed.SetToZero();
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
	 this->born = p.born;
	 this->life = p.life;
	 this->angle = p.angle;
	 this->initialColor = p.initialColor;
	 this->finalColor = p.finalColor;
	 this->fx = p.fx;
	 this->fx_played = p.fx_played;
}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	//Update all the particle characteristics depending on the particle type
	bool ret = true;


	if (life > 0 && type == ParticleType::SHOT)
	{
		if ((SDL_GetTicks()/1000 - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;
	

	return ret;
}