/*#include "MovementManager.h"
#include "j1Pathfinding.h"

MovementManager::MovementManager() : j1Module() {
	name = "MovementManager";
}

MovementManager::~MovementManager() {

}

void MovementManager::Init() {
	active = true;
	enabled = false;
}

bool MovementManager::Start() {

	return true;
}

bool MovementManager::Update(float dt) {
	if (!_transitionOn)
		return;

	UpdateTransition();
	return true;
}

bool MovementManager::CleanUp() {
	MovingEntities.clear();
	return true;
}

void MovementManager::AddEntity(Entity* entity) {
	MovingEntities.push_back(entity);
}

void UpdateTransition()
{
    if (_sprite.TransitionOn)
        return;

    if (_path.Count > 0)
    {
        var wantedXTile = (int)_path[0].X;
        var wantedYTile = (int)_path[0].Y;


        if (_sprite.XTilePos < wantedXTile)
        {
            _sprite.Move(1, 0, _speed);
        }
        else if (_sprite.XTilePos > wantedXTile)
        {
            _sprite.Move(-1, 0, _speed);
        }
        else if (_sprite.YTilePos < wantedYTile)
        {
            _sprite.Move(0, 1, _speed);
        }
        else if (_sprite.YTilePos > wantedYTile)
        {
            _sprite.Move(0, -1, _speed);
        }

        _path.RemoveAt(0);
        if (_path.Count > 0)
            _path = _pathfinding.FindPath(_goalX, _goalY);
    }
    else
    {
        _transitionOn = false;
    }
}
*/