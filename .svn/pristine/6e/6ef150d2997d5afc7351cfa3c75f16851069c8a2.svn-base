#ifndef PLAYGAME
#define PLAYGAME

#include <sstream>
#include<iostream>
#include<fstream>
#include "GameState.h"
//#include "Common.h"
#include "JsonHelper.h"
#include "Shooting.h"

class PlayGame
{

private:
   std::string _playerKey;
   std::string _workingDir;
   GameState* _gameState;
   JsonHelper* _jsonGameState;
   JsonHelper* _previousJsonGameState;
   Shooting* _shootingAI;

   bool ReadGameState();
   void PopulateGameState();
   void DeployShipsFromFile();
   void DeployShips();
   void FireShot();
   void SaveCurrentGameStateData(bool gameEnded = false);
   std::string GetPreviousGameStatePath();
   void SetInitialGameStateAttributes();
   std::string GetPlayerKey();
   std::string GetWorkingDirectory();
   std::string ReadFromFile(std::string filepath);
   void WriteToFile(std::string filepath, std::vector<std::string>& data);
   void WriteToFile(std::string filepath, std::string data, bool append = false);
   void SaveFinalGameState();

public:
   PlayGame(std::string playerKey, std::string workingDir);
   ~PlayGame();
   void Play();
};

#endif