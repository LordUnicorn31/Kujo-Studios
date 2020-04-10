#pragma once
//Creo una struct entity info?
class Entity {
public:
	Entity();
	~Entity();
	//SDL_Rect entity_rect;
	//inagroup?/selected?
	int health;//total health?
	//type?
	//state (constructing/training/collecting...)
	//intendencia?
	//construction time
	//speed???
public:
	virtual void Draw(); 
	virtual void Update();
};

class Building :public Entity {
public:
	Building();
	~Building();
	//state (constructing/aviable...)
	//construction time
	//SDL_Texture/Animation texture;
	//SDL_Texture/Animation constructing_texture;
	void Draw();
	void Update();
};

//class x :public Building {};
//Building x;

class Collector :public Entity {
public:
	Collector();
	~Collector();
	//state (working/free)
	//SDL_Texture/Animation texture;
	//path intendencia->mina
	//wight (capacitat que pot transportar)
	//speed
	void Draw();
	void Update();
};

class CombatUnit :public Entity {
public:
	CombatUnit();
	~CombatUnit();
	//state (selected?)
	//bool training
	//training time
	//SDL_Texture/Animation texture; (per cada accio)
	//attack
	//range
	//cost
	//speed
	void Draw();
	void Update();
};

//class y :public CombatUnit{};
//CombatUnit a;