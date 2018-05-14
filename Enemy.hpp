#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Living.hpp"

class Enemy : public Living {
	public:
		Enemy(std::string name, int health, Item* weapon);
		void PrintInfo();
};

#endif

/*
	* There are 7 different types of enemies encountered in the game.
	* Low-tier: Orc, Goblin (30hp/5dmg)
	* Mid-tier: Cyclops, Troll (40hp/10dmg)
	* High-tier: Wizard, Vampire (60hp/15dmg)
	* Final Boss: Giant (100hp/20dmg)
	* Enemy class is mostly an implementation of PrintInfo() for enemy-specific output.
*/