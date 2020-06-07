#include "Module.h"
#include "EASTL/vector.h"

class DialogNode;

class DialogOptions 
{
public:
	DialogOptions(eastl::string text, int returnCode, DialogNode* nextNode);

	eastl::string text;
	int returnCode;
	DialogNode* nextNode;
};

class DialogNode
{
public:

	DialogNode(eastl::string text);
	eastl::string text;
	eastl::vector<DialogOptions> dialogOptions;

};

class DialogTree : public Module
{
public:

	DialogTree();

	// Destructor
	virtual ~DialogTree();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

private:

	eastl::vector<DialogNode*> dialogueNodes;
};