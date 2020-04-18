#include "p2Log.h"
#include "j1App.h"
#include "pugixml.hpp"
#include <SDL.h>

enum class MainState
{
	CREATE = 1,
	AWAKE,
	START,
	LOOP,
	CLEAN,
	FAIL,
	EXIT
};

void* __cdecl operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{
	return new uint8_t[size];
}

void* __cdecl operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line) {
	return new uint8_t[size];
}

j1App* App = NULL;

int main(int argc, char* args[])
{
	LOG("Engine starting ... %d");

	MainState state = MainState::CREATE;
	int result = EXIT_FAILURE;

	while (state != MainState::EXIT)
	{
		switch (state)
		{

			// Allocate the engine --------------------------------------------
		case MainState::CREATE:
			LOG("CREATION PHASE ===============================");

			App = new j1App(argc, args);

			if (App != NULL)
				state = MainState::AWAKE;
			else
				state = MainState::FAIL;

			break;

			// Awake all modules -----------------------------------------------
		case MainState::AWAKE:
			LOG("AWAKE PHASE ===============================");
			if (App->Awake() == true)
				state = MainState::START;
			else
			{
				LOG("ERROR: Awake failed");
				state = MainState::FAIL;
			}

			break;

			// Call all modules before first frame  ----------------------------
		case MainState::START:
			LOG("START PHASE ===============================");
			if (App->Start() == true)
			{
				state = MainState::LOOP;
				LOG("UPDATE PHASE ===============================");
			}
			else
			{
				state = MainState::FAIL;
				LOG("ERROR: Start failed");
			}
			break;

			// Loop all modules until we are asked to leave ---------------------
		case MainState::LOOP:
			if (App->Update() == false)
				state = MainState::CLEAN;
			break;

			// Cleanup allocated memory -----------------------------------------
		case MainState::CLEAN:
			LOG("CLEANUP PHASE ===============================");
			if (App->CleanUp() == true)
			{
				RELEASE(App);
				result = EXIT_SUCCESS;
				state = MainState::EXIT;
			}
			else
				state = MainState::FAIL;

			break;

			// Exit with errors and shame ---------------------------------------
		case MainState::FAIL:
			LOG("Exiting with errors :(");
			result = EXIT_FAILURE;
			state = MainState::EXIT;
			break;
		}
	}

	LOG("... Bye! :)\n");
	return result;
}