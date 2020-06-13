#ifndef __QUESTMANAGER_H__
#define __QUESTMANAGER_H__

#include "Module.h"
#include "EASTL/vector.h"
#include "Gui.h"

class Quest
{
public:

	Quest(int id, bool trigger, int requisites, UiElement* text, UiElement* requisitesIni, UiElement* requisitesFinal);

	~Quest();

	int id;
	bool trigger;
	int requisites;

	UiElement* requisitesIni;
	UiElement* requisitesFinal;
	UiElement* text;

	bool completed;
};


class QuestManager : public Module
{

public:

	QuestManager();

	virtual ~QuestManager();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void CreateQuests();

	void CheckQuests();

	eastl::vector<Quest*> quests;

};





#endif // __QUESTMANAGER_H__