#ifndef ROOM_HPP
#define ROOM_HPP

#include <vector>

#include "Enemy.hpp"
#include "Item.hpp"

class Room {
	public:
		Room(int number);
		Room(Enemy* enemy, int number);
		Room(Item* item, int number);
		std::string GetAdjacencies();
		Enemy* GetEnemy();
		Item* GetItem();
		int GetNumber();
		bool HasEnemy(int enemiesDefeated);
		bool HasItem();
		void PrintInfo();
		void RemoveEnemy();
		void RemoveItem();
	private:
		Enemy* enemy = NULL;
		int number;
		Item* item = NULL;
		std::vector<Room*> rooms;
};

#endif

/*
	* Representation of a single room in the dungeon.
	* Contains various item/enemy functions, as well as a vector of pointers to adjacent rooms in the 4x4 layout.
*/