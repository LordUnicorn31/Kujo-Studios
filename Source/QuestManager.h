#ifndef __QUESTMANAGER_H__
#define __QUESTMANAGER_H__

#include "Module.h"
#include "EASTL/vector.h"

class Quest
{
public:

	Quest();

	~Quest();

	int questNumber = 0;
	bool questTrigger = 0;

	eastl::string questText;
	eastl::string questDescription;

	bool questCompleted = false;
};


class QuestManager : public Module
{

public:

	QuestManager();

	virtual ~QuestManager();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool Update();

	bool CleanUp();

	void LoadQuests();

	eastl::vector<Quest*> quests;

};





#endif // __QUESTMANAGER_H__