#include <stdexcept>
#include <iostream>
#include "Game.hpp"

int main(){

	//Creation of game object - starting info/story is done in the constructor.
	Game* game = new Game();
	std::string input;
	int choice;

	do{
		game->RoomOptions();
		std::cin >> input;

		try{
			choice = std::stoi(input);
		}catch(std::invalid_argument){
			choice = 0;
		}

		switch(choice){
			case 1:
				game->GetCurrentRoom()->PrintInfo();
				break;
			case 2:
				if(game->GetCurrentRoom()->HasItem())
					game->TakeItem();
				else if(game->GetCurrentRoom()->HasEnemy(game->GetEnemiesDefeated()) || (game->GetCurrentRoom()->GetNumber() == 16 && game->GetEnemiesDefeated() >= 4))
					game->Combat();
				else
					game->GetPlayer()->PrintInfo();
				break;
			case 3:
				if(game->GetCurrentRoom()->HasItem() || game->GetCurrentRoom()->HasEnemy(game->GetEnemiesDefeated()))
					game->GetPlayer()->PrintInfo();
				else
					game->MoveRoom();
				break;
			case 4:
				if(game->GetCurrentRoom()->HasItem() || game->GetCurrentRoom()->HasEnemy(game->GetEnemiesDefeated())){
					game->MoveRoom();
				}else{
					std::cout << "Invalid choice - must be a number 1-4 (if applicable to current room.)\n";
				}
				break;
			default:
				std::cout << "Invalid choice - must be a number 1-4 (if applicable to current room.)\n";	
				break;
		}
	}while(game->GetFinished() == false);

	std::cout << "After defeating the Giant you managed to find your way out of the cave. You feel like you learned a thing or two about how to kill random creatures for a few hours until you "
			  << "found your way back home. Congrats!\n";
}