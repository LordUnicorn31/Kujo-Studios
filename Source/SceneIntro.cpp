#include "p2Defs.h"
#include "p2Log.h"
#include "Application.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "SceneLogo.h"
#include "SceneIntro.h"
#include "SceneTitle.h"
#include "Input.h"
#include "Map.h"
#include "Minimap.h"
#include "Transitions.h"
#include "Gui.h"
#include "Fonts.h"
#include "Audio.h"
#include "Particles.h"

SceneIntro::SceneIntro() : Module()
{
	name = "sceneIntro";
}

// Destructor
SceneIntro::~SceneIntro()
{
}


// Called before render is available
bool SceneIntro::Awake(pugi::xml_node& config)
{
	LOG("Loading Intro Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool SceneIntro::Start()
{
	rect = { 0,0,App->win->width, App->win->height };

	s = 0;

	img1 = App->tex->Load("Resources/intro/intro_scene1.png");
	img2 = App->tex->Load("Resources/intro/intro_scene2.png");
	img3 = App->tex->Load("Resources/intro/intro_scene3.png");

	return true;
}

// Called each loop iteration
bool SceneIntro::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneIntro::Update(float dt)
{
	
	bool ret = true;

	int w = App->win->GetWidth();
	int h = App->win->GetHeight();

	//App->render->DrawQuad(rect, 150, 150, 150, (Uint8)s);

	if (s >= 350)
	{
		App->render->Blit(img1, 0, 0, NULL, true, App->render->renderer, 1.0f);
		if (s >= 900)
		{
			App->render->Blit(img2, 0, 0, NULL, true, App->render->renderer, 1.0f);
			if (s >= 1500)
			{
				App->render->Blit(img3, 0, 0, NULL, true, App->render->renderer, 1.0f);
			}
		} 
	}
	

	if (App->input->GetKey(SDL_SCANCODE_SPACE))
	{
		if (s>255)
		{
			App->transition->FadeToBlack(App->sceneIntro, App->sceneTitle, 2.0f);
		}
		else
		{
			s = 255;
		}
	}

	s++;

	if (s == 2047)
	{
		s--;
		App->transition->FadeToBlack(App->sceneIntro, App->sceneTitle, 2.0f);
	}

	return ret;
}

// Called each loop iteration
bool SceneIntro::PostUpdate()
{
	bool ret = true;
	
	return ret;
}


// Called before quitting
bool SceneIntro::CleanUp()
{
	LOG("Freeing scene");
	App->tex->UnLoad(img3);
	App->tex->UnLoad(img2);
	App->tex->UnLoad(img1);
	img1 = nullptr;
	img2 = nullptr;
	img3 = nullptr;
	return true;
}

void SceneIntro::Init()
{
	enabled = true;

	active = true;
}
