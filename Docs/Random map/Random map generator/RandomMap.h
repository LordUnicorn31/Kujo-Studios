//#pragma once
//#include <iostream>
//#include <random>
//#include <string>
//#include <cassert>
//
//
//enum class Tile
//{
//	Unused,
//	Wall,
//	Floor,
//	Goldmine,
//	Dungeon,
//	Oremine,
//	DownStairs,
//};
//
//enum class Direction
//{
//	North,
//	South,
//	East,
//	West,
//};
//
//class Map
//{
//
//private:
//	int xSize;
//	int ySize;
//public:
//	Map() :
//		xSize(0), ySize(0),
//	void SetCell(int x, int y, Tile celltype);
//	Tile GetCell(int x, int y) const;
//	void SetCells(int xStart, int yStart, int xEnd, int yEnd, Tile cellType);
//	bool isXInBounds(int x) const;
//	bool isYInBounds(int y) const;
//	bool isAreaUnused(int xStart, int yStart, int xEnd, int yEnd);
//	bool isAdjacent(int x, int y, Tile tile);
//	void Print() const;
//
//
//};
//
//class MapGenerator
//{
//private:
//	typedef std::mt19937 RngT;
//	int GetRandomInt(RngT& rng, int min, int max) const;
//	Direction GetRandomDirection(RngT& rng) const;
//	bool MakeCorridor(Map& map, RngT& rng, int x, int y, int maxLength, Direction direction) const;
//	bool MakeRoom();
//	bool MakeFeature(Map& map, RngT& rng) const;
//	bool MakeStairs(Map& map, RngT& rng, Tile tile) const;
//	bool MakeMap(Map& map, RngT& rng) const;
//	
//public:
//	typedef std::mt19937 RngT;
//	int Seed;
//	int xSize, Ysize;
//	int MaxFeatures;
//	int ChanceRoom, ChanceCorridor;
//
//	Map Generate();
//	
//};
