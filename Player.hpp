#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include "Living.hpp"

class Player : public Living {
	public:
		Player(std::string name, int health, Item* weapon);
		void AddPotion(Item* potion);
		void ChangeWeapon(Item* weapon);
		std::vector<Item*> GetPotions();
		void PrintInfo();
		bool UsePotion();
	private:
		std::vector<Item*> potions;
};

#endif

/*
	* Player is the main implementation of Living, and allows the Player to do numerous actions.
	* Because held items are only ever going to be health potions, functions are named accordingly.
*/