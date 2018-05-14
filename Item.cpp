#include "Item.hpp"

Item::Item(std::string name, std::string description, int damage){
	this->name = name;
	this->description = description;
	this->damage = damage;
}

int Item::GetDamage(){
	return damage;
}

std::string Item::GetDescription(){
	return description;
}

std::string Item::GetName(){
	return name;
}