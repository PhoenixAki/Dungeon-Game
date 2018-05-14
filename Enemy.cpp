#include "Enemy.hpp"

Enemy::Enemy(std::string name, int health, Item* weapon) : Living::Living(name, health, weapon){
	
}

void Enemy::PrintInfo(){
	std::cout << "\nEnemy Info:\n-----------\nName: " << name << " (" << health << "hp)\nWeapon: " << weapon->GetName() << ", " << weapon->GetDamage() 
			  << "dmg\nWeapon Description: " << weapon->GetDescription() << "\n";
}