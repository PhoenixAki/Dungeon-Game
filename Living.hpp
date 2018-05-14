#ifndef LIVING_HPP
#define LIVING_HPP

#include "Item.hpp"

class Living{
	public:
		Living(std::string name, int health, Item* weapon);
		void ChangeHealth(int amount);
		int GetHealth();
		std::string GetName();
		Item* GetWeapon();
		virtual void PrintInfo() = 0;
	protected:
		int health;
		Item* weapon;
		std::string name;
};

#endif

/*
	* Living is the parent class between Player and Enemy.
	* Contains health/weapon information.
	* ChangeHealth() allows for a negative value to "heal" if a healing potion is used.
	* PrintInfo() is virtual because exact outputs differ between player/enemies
*/