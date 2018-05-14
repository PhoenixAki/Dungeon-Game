#include "Living.hpp"

Living::Living(std::string name, int health, Item* weapon){
	this->name = name;
	this->health = health;
	this->weapon = weapon;
}

void Living::ChangeHealth(int amount){
	health -= amount;
}

int Living::GetHealth(){
	return health;
}

std::string Living::GetName(){
	return name;
}

Item* Living::GetWeapon(){
	return weapon;
}