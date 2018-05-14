#include "Game.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Game::Game(){
	//Creating player character & setting up random seed for some combat actions
	this->player = new Player("Player", 200, new Item("Rusty Sword", "A rusty sword. Not very strong but it gets the job done.", 15));
	srand(time(NULL));

	//Story setup
	std::cout << "You wake up surrounded by walls in a dimly lit room.\n...\nWhat happened? After spending some time examining the room you remember what happened; while returning home through a" << 
	" woodsy path you heard a hypnotic sound coming from a nearby cave.\n\nAs much as you tried to resist, your body felt compelled to follow this sound to its origin, down through" <<
	" the dark cave until you arrived in this room, its exit sealing behind you.\n...\nYou should probably try to find a way out.\nBelow you is an old rusty sword " << 
	"(15 damage) which will act as your weapon until you can find a better one.\n\n";

	//I messed with ways to do this through a loop but due to the varying names/descriptions, the only reasonable way to do this was sequentially
	rooms.push_back(new Room(1));
	rooms.push_back(new Room(new Enemy("Orc", 30, new Item("Small Dagger", "A small dagger. If he manages to poke you with this it will hurt a little bit.", 5)), 2));
	rooms.push_back(new Room(new Item("Battle Axe", "A heavy Battle Axe. Hard to pick up, but will deal some good damage to enemies.", 20), 3));
	rooms.push_back(new Room(new Enemy("Cyclops", 40, new Item("Hands", "He wants to punch you. Really bad. You should probably be careful.", 10)), 4));
	rooms.push_back(new Room(new Item("Health Potion", "A simple health potion. Heals 25hp.", -25), 5));
	rooms.push_back(new Room(6));
	rooms.push_back(new Room(new Enemy("Goblin", 30, new Item("Stick", "A small stick that was probably part of a larger weapon at some point.", 5)), 7));
	rooms.push_back(new Room(8));
	rooms.push_back(new Room(9));
	rooms.push_back(new Room(new Enemy("Troll", 40, new Item("Small Club", "A small club that this troll found while wandering in circles.", 10)), 10));
	rooms.push_back(new Room(new Item("Steel Longsword", "A steel longsword. Very durable and will give any enemy a bad headache.", 30), 11));
	rooms.push_back(new Room(new Enemy("Wizard", 60, new Item("Wizard Staff", "A magical staff that allows a Wizard to perform his spells.", 15)), 12));
	rooms.push_back(new Room(new Item("Health Potion", "A simple health potion. Heals 25hp.", -25), 13));
	rooms.push_back(new Room(14));
	rooms.push_back(new Room(new Enemy("Vampire", 60, new Item("Dark Staff", "A staff that was passed down for generations of vampires.", 15)), 15));
	rooms.push_back(new Room(new Enemy("Giant", 100, new Item("Giant Club", "A massive club that will raise your chances of skull fracture today by at least 50%.", 20)), 16));

	/*
		* Dungeon room layout is:
		* 13 14 15 16
		* 9  10 11 12
		* 8  9  10 11
		* 1  2  3  4
		* Start in 1, goal is 16
	*/

	currentRoom = rooms.at(0);
}

void Game::Combat(){
	//storing enemy for shorter references during combat
	Enemy* enemy = currentRoom->GetEnemy();

	std::cout << "Entering combat with " << enemy->GetName() << " (" << enemy->GetHealth() << "hp)\n";
	std::string input;
	bool counter, flee, playerDone;
	int choice;

	//outer loop (controls battle in-progress or not)
	do{
		//reset bools to false to ensure each player turn functions properly
		playerDone = false;
		counter = false;
		flee = false;

		//inner loop (controls when player's turn is done, does not end if simply viewing inventory/battle info)
		do{
			std::cout << "\nAttack\n------\n1) Use Weapon (" << player->GetWeapon()->GetDamage() << "dmg)\n2) Counter (50% chance to block and reflect damage)\n\nItems\n-----\n3) Use Item (" <<
			player->GetPotions().size() << "x Health Potion)\n4) Player Stats\n\nOther\n-----\n5) Enemy Stats\n6) Flee (50% chance to leave fight)\n\nChoice: ";

			std::cin >> input;
		
			try{
				choice = std::stoi(input);
			}catch(std::invalid_argument){
				choice = 0;
			}

			//determining player's choice
			switch(choice){
				case 1:
					enemy->ChangeHealth(player->GetWeapon()->GetDamage());
					std::cout << "Dealt " << player->GetWeapon()->GetDamage() << "dmg to " << enemy->GetName() << ".\n";
					playerDone = true;
					break;
				case 2:
					counter = true;
					playerDone = true;
					break;
				case 3:
					//UseItem will return false if player does not have any items currently
					playerDone = player->UsePotion();
					break;
				case 4:
					player->PrintInfo();
					break;
				case 5:
					enemy->PrintInfo();
					break;
				case 6:
					flee = true;
					playerDone = true;
					break;
				default:
					std::cout << "Invalid choice - must be a number 1-6.\n";
					break;
			}
		}while(!playerDone);

		//for both fleeing and countering, rand() determines a 50/50 chance of success
		if(flee){
			if(rand() % 100 + 1 > 50){
				std::cout << "Flee successful - leaving fight.\n";
				return;
			}else{
				std::cout << "Flee failed - combat continues.\n";
			}
		}
		
		//enemy's turn (if still alive)
		if(enemy->GetHealth() > 0){
			std::cout << enemy->GetName() << " attacks with a " << enemy->GetWeapon()->GetName() << ".\n";

			if(counter){
				if(rand() % 100 + 1 < 50){
					std::cout << "You attempted to counter but it failed - " << enemy->GetName() << " deals " << enemy->GetWeapon()->GetDamage() << "dmg to you.\n";
					player->ChangeHealth(enemy->GetWeapon()->GetDamage());
				}else{
					std::cout << "You attempted to counter and it succeeded - you reflect " << enemy->GetWeapon()->GetDamage() << "dmg back to the " << enemy->GetName() << ".\n";
					enemy->ChangeHealth(enemy->GetWeapon()->GetDamage());
				}
			}else{
				std::cout << enemy->GetName() << " deals " << enemy->GetWeapon()->GetDamage() << " to you.\n";
				player->ChangeHealth(enemy->GetWeapon()->GetDamage());
			}
		}
	}while(enemy->GetHealth() > 0);

	std::cout << "Enemy " << enemy->GetName() << " defeated.\n\n";
	currentRoom->RemoveEnemy();
	//enemiesDefeated is used to allow access to the final boss in room 16
	enemiesDefeated++;

	//if enemy defeated was the final boss, trigger the game to be finished (exits main function loop)
	if(enemy->GetName() == "Giant")
		finished = true;
}

Room* Game::GetCurrentRoom(){
	return currentRoom;
}

int Game::GetEnemiesDefeated(){
	return enemiesDefeated;
}

bool Game::GetFinished(){
	return finished;
}

Player* Game::GetPlayer(){
	return player;
}

void Game::MoveRoom(){
	std::string input;
	std::cout << "Which direction do you want to move? ";
	std::cin >> input;

	//tries to "find" the user input in the available move options for current room
	if(currentRoom->GetAdjacencies().find(input) != std::string::npos){
		//if here, then this is a valid move to do - shift current room to new room
		if(input == "north")
			currentRoom = rooms.at(currentRoom->GetNumber() + 3);
		else if(input == "south")
			currentRoom = rooms.at(currentRoom->GetNumber() - 5);
		else if(input == "east")
			currentRoom = rooms.at(currentRoom->GetNumber());
		else if(input == "west")
			currentRoom = rooms.at(currentRoom->GetNumber() - 2);

		std::cout << "Moving " << input << "...\n";
		currentRoom->PrintInfo();
	}else{
		//There is no fairly simple "equalsIgnoreCase" function like in java, so input is case sensitive
		std::cout << "Invalid direction (direction is case-sensitive, not capitalized).\n\n";
	}
}

void Game::RoomOptions(){
	//Outputs what options the player can choose from for this room (checks especially if in the boss room without 4/6 enemies defeated yet)
	if(currentRoom->GetNumber() == 16){
		std::cout << "Boss Room! Should make sure you have the best weapon you can before challenging the boss.\n**Must also defeat 4/6 of the dungeon's enemies.**\n\n";
		if(enemiesDefeated < 4)
			std::cout << "Room Options:\n--------------\n1) Examine Room\n2) Player Stats\n3) Move\nChoice: ";
		else
			std::cout << "Room Options:\n--------------\n1) Examine Room\n2) Fight Boss\n3) Move\nChoice: ";
	}else{
		if(currentRoom->HasItem()){
			std::cout << "Room Options:\n--------------\n1) Examine Room\n2) Take Item\n3) Player Statas\n4) Move\nChoice: ";
		}else if(currentRoom->HasEnemy(enemiesDefeated)){
			std::cout << "Room Options:\n--------------\n1) Examine Room\n2) Fight Enemy\n3) Player Stats\n4) Move\nChoice: ";
		}else{
			std::cout << "Room Options:\n--------------\n1) Examine Room\n2) Player Stats\n3) Move\nChoice: ";
		}
	}

}

void Game::TakeItem(){
	//Items will only ever be a health potion or weapon
	if(currentRoom->GetItem()->GetName() == "Health Potion"){
		player->AddPotion(currentRoom->GetItem());
		std::cout << "1x Health Potion added to inventory (heals " << currentRoom->GetItem()->GetDamage()*-1 << "hp).\n\n";
	}else{
		player->ChangeWeapon(currentRoom->GetItem());
		std::cout << "Weapon changed to " << currentRoom->GetItem()->GetName() << "\n\n";
	}

	currentRoom->RemoveItem();
}