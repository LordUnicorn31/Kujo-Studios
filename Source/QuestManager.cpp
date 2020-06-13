#include "QuestManager.h"
#include "p2Log.h"
#include "EASTL/vector.h"


QuestManager::QuestManager()
{}

QuestManager::~QuestManager()
{}

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

bool QuestManager::Update()
{
	return true;
}

bool QuestManager::CleanUp()
{
	return true;
}

void QuestManager::LoadQuests()
{}