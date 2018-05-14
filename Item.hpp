#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>

class Item {
	public:
		Item(std::string name, std::string description, int damage);
		int GetDamage();
		std::string GetDescription();
		std::string GetName();
	private:
		int damage;
		std::string description, name;
};

#endif

/*
	* Item exists to be instantiated as either a Health Potion or a weapon.
	* Contains basic getters to access name/description/damage.
	* In the case of a health potion, damage is negative to represent gaining health as opposed to losing health.
*/