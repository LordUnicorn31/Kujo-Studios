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
#include "Audio.h"

Quest::Quest(int id, bool trigger, int requisites, UiElement* text, UiElement* requisitesIni, UiElement* requisitesFinal)
{
	this->id = id;
	this->trigger = trigger;
	this->requisites = requisites;
	this->requisitesIni = requisitesIni;
	this->requisitesFinal = requisitesFinal;
	this->text = text;
}

QuestManager::QuestManager()
{
	tutorialCompleted = false;
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
	questFx = App->audio->LoadFx("Resources/audio/fx/quest.wav");
	tutorialCompleteFx = App->audio->LoadFx("Resources/audio/fx/tutorialComplete.wav");

	if (App->scene->tutorialActive)
	CreateQuestsTutorial();

	return true;
}

void QuestManager::Init()
{
	active = true;
	enabled = false;
}

bool QuestManager::Update(float dt)
{
	if (App->scene->tutorialActive) {
		CheckQuests();
	}
	else
	{
		App->gui->RemoveUiElement(questPanel);
	}
	
	return true;
}

bool QuestManager::CleanUp()
{
	App->audio->UnloadFx();
	return true;
}

void QuestManager::CreateQuestsTutorial()
{
	questPanel = App->gui->AddImage(361, 10, { 1256,859,240,127 }, false, false, false, nullptr, this);
	App->gui->AddText(43, 10, "Tutorial Quests", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, questPanel);

	Quest* quest00 = new Quest(0, false, 0, App->gui->AddText(10, 40, "Recruit a Builder", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false,questPanel ), 
		App->gui->AddText(180, 40, std::to_string(0).c_str(), App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, questPanel), 
		App->gui->AddText(195, 40, "/1", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false,questPanel));

	Quest* quest01 = new Quest(1, false, 0, App->gui->AddText(10, 60, "Build a Mine", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false,questPanel), 
		App->gui->AddText(180, 60, std::to_string(0).c_str(), App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, questPanel),
		App->gui->AddText(195, 60, "/1", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, questPanel));

	Quest* quest02 = new Quest(2, false, 0, App->gui->AddText(10, 80, "Build a Barrack", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, questPanel),
		App->gui->AddText(180, 80, std::to_string(0).c_str(), App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, questPanel),
		App->gui->AddText(195, 80, "/1", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, questPanel));

	Quest* quest03 = new Quest(3, false, 0, App->gui->AddText(10, 100, "Recruit a Basic", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, questPanel),
		App->gui->AddText(180, 100, std::to_string(0).c_str(), App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, questPanel),
		App->gui->AddText(195, 100, "/1", App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, questPanel));

	quests.push_back(quest00);
	quests.push_back(quest01);
	quests.push_back(quest02);
	quests.push_back(quest03);
}

void QuestManager::CheckQuests()
{
	eastl::vector<Quest*>::iterator it = quests.begin();

	for (int i = 0; i < quests.size(); ++it,++i)
	{
		int questsId = (*it)->id;

			eastl::list<Entity*>::const_iterator iter;
			switch (questsId)
			{
			case 0:

				for (iter = App->entity->GetEntities().begin(); iter != App->entity->GetEntities().end(); ++iter) {
					if ((*iter)->etype != EntityType::TypeAi)
						continue;
					if (((Ai*)(*iter))->Atype == AiType::Collector && !((Ai*)(*iter))->Building)
					{
						App->audio->PlayFx(questFx);
						App->gui->RemoveUiElement((*it)->requisitesIni);
						(*it)->requisites = 1;
						(*it)->requisitesIni = App->gui->AddText(185, 40, std::to_string((*it)->requisites).c_str(), App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, questPanel);
						delete (*it);
						quests.erase(it);
						LOG("Delete quest 1");
						break;
					}
				}
				break;

			case 1:

				for (iter = App->entity->GetEntities().begin(); iter != App->entity->GetEntities().end(); ++iter) {
					if ((*iter)->etype != EntityType::TypeBuilding)
						continue;
					if (((Building*)(*iter))->Btype == BuildingType::Mine && !((Building*)(*iter))->OnConstruction) {
						App->audio->PlayFx(questFx);
						App->gui->RemoveUiElement((*it)->requisitesIni);
						(*it)->requisites = 1;
						(*it)->requisitesIni = App->gui->AddText(185, 60, std::to_string((*it)->requisites).c_str(), App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, questPanel);
						delete (*it);
						quests.erase(it);
						LOG("Delete quest 2");
						break;
					}
				}
				break;

			case 2:
				for (iter = App->entity->GetEntities().begin(); iter != App->entity->GetEntities().end(); ++iter) {
					if ((*iter)->etype != EntityType::TypeBuilding)
						continue;
					if (((Building*)(*iter))->Btype == BuildingType::Cuartel && !((Building*)(*iter))->OnConstruction) {
						App->audio->PlayFx(questFx);
						App->gui->RemoveUiElement((*it)->requisitesIni);
						(*it)->requisites = 1;
						(*it)->requisitesIni = App->gui->AddText(185, 80, std::to_string((*it)->requisites).c_str(), App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, questPanel);
						delete (*it);
						quests.erase(it);
						LOG("Delete quest 3");
						break;
					}
				}
				break;

			case 3:
				for (iter = App->entity->GetEntities().begin(); iter != App->entity->GetEntities().end(); ++iter) {
					if ((*iter)->etype != EntityType::TypeAi)
						continue;
					if (((Ai*)(*iter))->Atype == AiType::RedShip && !((Ai*)(*iter))->Building) {
						App->audio->PlayFx(questFx);
						App->gui->RemoveUiElement((*it)->requisitesIni);
						(*it)->requisites = 1;
						(*it)->requisitesIni = App->gui->AddText(185, 100, std::to_string((*it)->requisites).c_str(), App->font->smallFont, { 236,178,0,255 }, 1, false, false, false, questPanel);
						delete (*it);
						quests.erase(it);
						LOG("Delete quest 4");
						break;
					}
				}
				break;
			}
	}

	if (quests.size() == 0 && tutorialCompleted == false)
	{
		tutorialCompleted = true;
		App->gui->RemoveUiElement(questPanel);
		questPanel = nullptr;
		questPanel = App->gui->AddButton(288, 355, { 0,356,802,41 }, { 0,356,802,41 }, { 0,356,802,41 }, false, false, false, nullptr, this);
		App->gui->AddText(200, 4, "TUTORIAL COMPLETED", nullptr, { 255,255,255,255 }, 12, false, false, false, questPanel);
		App->audio->PlayFx(tutorialCompleteFx);
		App->scene->tutorialActive = false;
	}

}