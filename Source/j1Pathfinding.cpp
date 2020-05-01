#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1PathFinding.h"

j1PathFinding::j1PathFinding() : j1Module(), map(NULL), last_path(DEFAULT_PATH_LENGTH),width(0), height(0)
{
	name = "pathfinding";
}

// Destructor
j1PathFinding::~j1PathFinding()
{
	RELEASE_ARRAY(map);
}

// Called before quitting
bool j1PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	last_path.clear();
	RELEASE_ARRAY(map);
	return true;
}

// Sets up the walkability map
void j1PathFinding::SetMap(uint width, uint height, uchar* data)
{
	this->width = width;
	this->height = height;

	RELEASE_ARRAY(map);
	map = new uchar[width*height];
	memcpy(map, data, width*height);
}

// Utility: return true if pos is inside the map boundaries
bool j1PathFinding::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x <= (int)width &&
			pos.y >= 0 && pos.y <= (int)height);
}

// Utility: returns true is the tile is walkable
bool j1PathFinding::IsWalkable(const iPoint& pos) const
{
	uchar t = GetTileAt(pos);
	return t != INVALID_WALK_CODE && t > 0;
}

// Utility: return the walkability value of a tile
uchar j1PathFinding::GetTileAt(const iPoint& pos) const
{
	if(CheckBoundaries(pos))
		return map[(pos.y*width) + pos.x];

	return INVALID_WALK_CODE;
}

// To request all tiles involved in the last generated path
const eastl::vector<iPoint>* j1PathFinding::GetLastPath() const
{
	return &last_path;
}

// PathList ------------------------------------------------------------------------
// Looks for a node in this list and returns it's list node or NULL
// ---------------------------------------------------------------------------------
const PathNode* PathList::Find(const iPoint& point) const
{
	eastl::list<PathNode>::const_iterator item = list.begin();

	while (item != list.end())
	{
		if ((*item).pos == point)
			return &(*item);
		item++;
	}
	return NULL;
}

// PathList ------------------------------------------------------------------------
// Returns the Pathnode with lowest score in this list or NULL if empty
// ---------------------------------------------------------------------------------
const PathNode* PathList::GetNodeLowestScore() const
{
	const PathNode* ret = NULL;
	int min = 65535;

	eastl::list <PathNode>::const_reverse_iterator item = list.rbegin();

	while (item != list.rend())
	{
		if ((*item).Score() < min)
		{
			min = (*item).Score();
			ret = &(*item);
		}
		item++;
	}
	return ret;
}

// PathNode -------------------------------------------------------------------------
// Convenient constructors
// ----------------------------------------------------------------------------------
PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
{}

PathNode::PathNode(int g, int h, const iPoint& pos, const PathNode* parent) : g(g), h(h), pos(pos), parent(parent)
{}

PathNode::PathNode(const PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{}

// PathNode -------------------------------------------------------------------------
// Fills a list (PathList) of all valid adjacent pathnodes
// ----------------------------------------------------------------------------------
uint PathNode::FindWalkableAdjacents(PathList& list_to_fill) const
{
	iPoint cell;
	uint before = list_to_fill.list.size();

	//diagonals
	cell.create(pos.x + 1, pos.y + 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	cell.create(pos.x + 1, pos.y - 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	cell.create(pos.x - 1, pos.y + 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	cell.create(pos.x - 1, pos.y - 1);
	if (App->pathfinding->IsWalkable(cell))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	// north
	cell.create(pos.x, pos.y + 1);
	if(App->pathfinding->IsWalkable(cell))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	// south
	cell.create(pos.x, pos.y - 1);
	if(App->pathfinding->IsWalkable(cell))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	// east
	cell.create(pos.x + 1, pos.y);
	if(App->pathfinding->IsWalkable(cell))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	// west
	cell.create(pos.x - 1, pos.y);
	if(App->pathfinding->IsWalkable(cell))
		list_to_fill.list.push_back(PathNode(-1, -1, cell, this));

	return list_to_fill.list.size();
}

// PathNode -------------------------------------------------------------------------
// Calculates this tile score
// ----------------------------------------------------------------------------------
int PathNode::Score() const
{
	return g + h;
}

// PathNode -------------------------------------------------------------------------
// Calculate the F for a specific destination tile
// ----------------------------------------------------------------------------------
int PathNode::CalculateF(const iPoint& destination)
{
	g = parent->g + 1;
	h = pos.DistanceTo(destination);

	return g + h;
}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int j1PathFinding::CreatePath(const iPoint& origin, const iPoint& destination)
{
	int ret = -1;
	// TODO 1: if origin or destination are not walkable, return -1
	if (!(IsWalkable(origin) && IsWalkable(destination) && origin!=destination))
		return ret;
	// TODO 2: Create two lists: open, close
	// Add the origin tile to open
	// Iterate while we have tile in the open list
	PathList open;
	PathList closed;
	open.list.push_back(PathNode(0,0,origin,nullptr));
	while (open.list.size() > 0) {
	// TODO 3: Move the lowest score cell from open list to the closed list
		PathNode* lowest = (PathNode*) open.GetNodeLowestScore();
		closed.list.push_back(*lowest);

		eastl::list<PathNode>::iterator it = open.list.begin();
		while (it != open.list.end()) {
			if ((&(*it) == lowest)) {
				open.list.erase(it);
				break;
			}
			it++;
		}
		
	// TODO 4: If we just added the destination, we are done!
	// Backtrack to create the final path
	// Use the Pathnode::parent and Flip() the path when you are finish
		if (closed.list.back().pos == destination) {
			last_path.clear();
			const PathNode* path_node = &closed.list.back();
			while (path_node) {
				last_path.push_back(path_node->pos);
				path_node = path_node->parent;
			}
			eastl::reverse(last_path.begin(), last_path.end());
			ret = last_path.size();
			break;
		}
	// TODO 5: Fill a list of all adjancent nodes
		PathList adjacent;
		closed.list.back().FindWalkableAdjacents(adjacent);
	// TODO 6: Iterate adjancent nodes:
		//p2List_item<PathNode>*item = adjacent.list.start;
		eastl::list<PathNode>::iterator item = adjacent.list.begin();
		for (; item != adjacent.list.end(); item++){
	        // ignore nodes in the closed list
			if (closed.Find((*item).pos)!=NULL)
				continue;
			// If it is NOT found, calculate its F and add it to the open list
			if (open.Find((*item).pos) == NULL) {
				(*item).CalculateF(destination);
				open.list.push_back((*item));
			}
			else {
				// If it is already in the open list, check if it is a better path (compare G)
				// If it is a better path, Update the parent
				PathNode adjacent_in_open = *open.Find((*item).pos);
				// --- We compare walkable cost and if the neighbor's is bigger than current + offset we know this is a better path and update neighbor's parent and F ---
				//if (adjacent_in_open.diagonal == false)
				if (adjacent_in_open.g > (*item).g + 1){
					adjacent_in_open.parent = (*item).parent;
					adjacent_in_open.CalculateF(destination);
				}
			}
		}
	}

	return ret;
}