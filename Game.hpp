#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "Room.hpp"
#include "Player.hpp"

class Game {
	public:
		Game();
		void Combat();
		Room* GetCurrentRoom();
		int GetEnemiesDefeated();
		bool GetFinished();
		Player* GetPlayer();
		void MoveRoom();
		void RoomOptions();
		void TakeItem();
	private:
		bool finished = false;
		int enemiesDefeated = 0;
		Player* player;
		Room* currentRoom;
		std::vector<Room*> rooms;
};

#endif

/*
	* As the name might suggest, Game class holds all of the central game functions.
	* Main.cpp passes control to this class to handle combat, moving, etc.
*/