#include "DialogSystem.h"
#include "p2Log.h"

DialogNode::DialogNode(eastl::string text)
{
	this->text = text;
}

DialogOptions::DialogOptions(eastl::string text, int returnCode, DialogNode* nextNode)
{
	this->text = text;
	this->returnCode = returnCode;
	this->nextNode = nextNode;
}

DialogTree::DialogTree() : Module()
{
	name = "DialogSystem";
}

DialogTree::~DialogTree()
{
}

bool DialogTree::Awake(pugi::xml_node& config)
{
	LOG("Loading DialogTree");
	bool ret = true;
	return ret;
}

bool DialogTree::Start()
{
	DialogNode* node0 = new DialogNode("Hola Bebe");
	DialogNode* node1 = new DialogNode("Como vas?");
	DialogNode* node2 = new DialogNode("Perro");

	node0->dialogOptions.push_back(DialogOptions("Hi", 0, node1));
	node0->dialogOptions.push_back(DialogOptions("Polla Pequeña", 0, node2));

	dialogueNodes.push_back(node0);
}

bool DialogTree::Update(float dt)
{
	bool ret = true;

	if (dialogueNodes.empty())
	{
		ret = false;
	}

	DialogNode* currentNode = dialogueNodes[0];

	return ret;
}

bool DialogTree::CleanUp()
{

}