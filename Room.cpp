#include "Room.hpp"

Room::Room(int number){
	this->number = number;
}

Room::Room(Enemy* enemy, int number){
	this->enemy = enemy;
	this->number = number;
}

Room::Room(Item* item, int number){
	this->item = item;
	this->number = number;
}

std::string Room::GetAdjacencies(){
	std::string rooms;

	if(number < 13)
		rooms += "north ";
	if(number > 4)
		rooms += "south ";
	if(number != 16 && number != 12 && number != 8 && number != 4)
		rooms += "east ";
	if(number != 1 && number != 5 && number != 9 && number != 13)
		rooms += "west ";

	return rooms += "\n";
}

Enemy* Room::GetEnemy(){
	return enemy;
}

Item* Room::GetItem(){
	return item;
}

int Room::GetNumber(){
	return number;
}

bool Room::HasEnemy(int enemiesDefeated){
	if(enemy == NULL){
		return false;
	}else{
		if(number == 16 && enemiesDefeated >= 4)
			return true;
		else if(number != 16 && enemy->GetHealth() > 0)
			return true;
		else
			return false;
	}
}

bool Room::HasItem(){
	return item != NULL;
}

void Room::PrintInfo(){
	if(enemy != NULL && enemy->GetHealth() > 0)
		std::cout << "\nRoom Info\n---------\nRoom Number: " << number << "\nEnemies: 1 (" << enemy->GetName() << ", " << enemy->GetHealth() << "hp)\nItems: 0\nAvailable Paths: " 
				  << GetAdjacencies() << std::endl;
	else if(item != NULL)
		std::cout << "\nRoom Info\n---------\nRoom Number: " << number << "\nEnemies: 0\nItems: 1 (" << item->GetName() << ")\nAvailable Paths: " << GetAdjacencies() << std::endl;
	else
		std::cout << "\nRoom Info\n---------\nRoom Number: " << number << "\nEnemies: 0\nItems: 0\nAvailable Paths: " << GetAdjacencies() << std::endl;
}

void Room::RemoveEnemy(){
	enemy = NULL;
}

void Room::RemoveItem(){
	item = NULL;
}