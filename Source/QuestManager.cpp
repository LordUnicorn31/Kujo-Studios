#include "QuestManager.h"
#include "p2Log.h"
#include "EASTL/vector.h"
#include "Gui.h"
#include "GameScene.h"
#include "Fonts.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Ai.h"
#include "Building.h"

Quest::Quest(int id, bool trigger, int requisites, UiElement* text, UiElement* requisitesIni, UiElement* requisitesFinal)
{
	this->id = id;
	this->trigger = trigger;
	this->requisites = requisites;
	this->requisitesIni = requisitesIni;
	this->requisitesFinal = requisitesFinal;
	this->text = text;
	this->completed = false;
}

QuestManager::QuestManager()
{

}

QuestManager::~QuestManager()
{
	for (eastl::vector <Quest*>::iterator it = quests.begin(); it != quests.end(); it++)
	{
		quests.erase(it);
	}
}

bool QuestManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Quests");
	bool ret = true;
	return ret;
}

bool QuestManager::Start()
{

	return true;
}

bool QuestManager::Update(float dt)
{
	if (App->scene->IsEneabled() == true && quests.data() == nullptr)	{

		CreateQuests();
	}
	
	if (App->scene->IsEneabled() == true) {
		CheckQuests();
	}

	return true;
}

bool QuestManager::CleanUp()
{
	return true;
}

void QuestManager::CreateQuests()
{
	Quest* quest00 = new Quest(0, false, 0, App->gui->AddText(10, 40, "Recruit a Builder", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, App->scene->questPanel), 
		App->gui->AddText(180, 40, std::to_string(0).c_str(), App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, App->scene->questPanel), 
		App->gui->AddText(195, 40, "/1", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, App->scene->questPanel));

	Quest* quest01 = new Quest(1, false, 0, App->gui->AddText(10, 60, "Build a Mine", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, App->scene->questPanel), 
		App->gui->AddText(180, 60, std::to_string(0).c_str(), App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, App->scene->questPanel),
		App->gui->AddText(195, 60, "/1", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, App->scene->questPanel));

	Quest* quest02 = new Quest(2, false, 0, App->gui->AddText(10, 80, "Build a Barrack", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, App->scene->questPanel), 
		App->gui->AddText(180, 80, std::to_string(0).c_str(), App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, App->scene->questPanel),
		App->gui->AddText(195, 80, "/1", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, App->scene->questPanel));

	Quest* quest03 = new Quest(3, false, 0, App->gui->AddText(10, 100, "Recruit all Units", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, App->scene->questPanel),
		App->gui->AddText(180, 100, std::to_string(0).c_str(), App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, App->scene->questPanel),
		App->gui->AddText(195, 100, "/3", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, App->scene->questPanel));

	quests.push_back(quest00);
	quests.push_back(quest01);
	quests.push_back(quest02);
	quests.push_back(quest03);
}

void QuestManager::CheckQuests()
{
	
	for (eastl::vector<Quest*>::iterator it = quests.begin(); it != quests.end(); ++it)
	{
		int questsId = (*it)->id;

		switch (questsId)
		{
		case 0:
			eastl::list<Entity*>::const_iterator iter;
			for (iter = App->entity->GetEntities().begin(); iter != App->entity->GetEntities().end(); ++iter) {
				if ((*iter)->etype != EntityType::TypeAi)
					continue;
				if(((Ai*)(*iter))->Atype == AiType::Collector && !((Ai*)(*iter))->Building)
				{
					(*it)->completed = true;
					App->gui->RemoveUiElement((*it)->requisitesIni);
					(*it)->requisites = 1;
					(*it)->requisitesIni = App->gui->AddText(185, 40, std::to_string((*it)->requisites).c_str(), App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, App->scene->questPanel);
					quests.erase(it);
				}
			}
			break;

		/*case 1:
			if () {
				(*it)->completed = true;
			}
			break;

		case 2:
			if () {
				(*it)->completed = true;
			}
			break;

		case 3:
			if () {
				(*it)->completed = true;
			}
			break;*/
		}
	}
}