#include "Player.hpp"

Player::Player(std::string name, int health, Item* weapon) : Living::Living(name, health, weapon){

}

void Player::AddPotion(Item* potion){
	potions.push_back(potion);
}

void Player::ChangeWeapon(Item* weapon){
	this->weapon = weapon;
}

std::vector<Item*> Player::GetPotions(){
	return potions;
}

void Player::PrintInfo(){
	std::cout << "\nPlayer Info:\n------------\nHealth: " << health << "/200\nWeapon: " << weapon->GetName() << ", " << weapon->GetDamage() << "dmg\nWeapon Description: " 
			  << weapon->GetDescription() << "\nItems: " << potions.size() << "x Health Potions\n\n";
}

bool Player::UsePotion(){
	if(potions.size() != 0){
		//potion "damage" is negative which heals the player
		health += potions.at(0)->GetDamage();

		//clamp health to be 200 at most
		if(health > 200)
			health = 200;

		potions.pop_back();
		return true;
	}else{
		std::cout << "You don't have any items!\n";
		return false;
	}
}