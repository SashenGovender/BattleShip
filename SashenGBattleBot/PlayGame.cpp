#include "PlayGame.h"
#include "windows.h"

PlayGame::PlayGame(std::string playerKey, std::string workingDir)
{
   _jsonGameState = nullptr;
   _playerKey = playerKey;
   _workingDir = workingDir;
   _gameState = new GameState();
   _previousJsonGameState = nullptr;
   _shootingAI = nullptr;
}

PlayGame::~PlayGame()
{
   if (_gameState != nullptr)
   {
      delete _gameState;
      _gameState = nullptr;
   }

   if (_jsonGameState != nullptr)
   {
      _jsonGameState->Release();
   }

   if (_previousJsonGameState != nullptr)
   {
      _previousJsonGameState->Release();
   }
   if (_shootingAI != nullptr)
   {
      delete _shootingAI;
      _shootingAI = nullptr;
   }

}

void PlayGame::Play()
{
   bool dataReadSuccess = ReadGameState();
   if (dataReadSuccess)
   {
      SetInitialGameStateAttributes();
      if (_gameState->GetPhase() == 1)
      {
         DeployShips();
         //DeployShipsFromFile();
      }
      else
      {
         PopulateGameState();
         FireShot();
         SaveCurrentGameStateData();
         SaveFinalGameState();
      }
   }
}

void PlayGame::SaveFinalGameState()
{
   //Has the game ended?
   if (_gameState->GetPlayerMap()->GetKilled() == true || _gameState->GetOpponentMap()->GetAlive() == false)
   {
      std::string filePathPreviousGameState = GetPreviousGameStatePath();
      if (filePathPreviousGameState.length() > 0)
      {
         remove(filePathPreviousGameState.c_str());
         SaveCurrentGameStateData(true);
      }
   }
}

bool PlayGame::ReadGameState()
{
   std::string filepath = _workingDir + "\\" + stateFilename;
   std::string stringCurrentGameStateRead = ReadFromFile(filepath);

   if (stringCurrentGameStateRead == "" || stringCurrentGameStateRead.length() == 0)//Did we read any data
   {
      std::cout << "Error Reading GameState Data at:" << filepath << std::endl;
      return false;
   }

   _jsonGameState = new JsonHelper();
   const char* cstringCurrentGameStateRead = stringCurrentGameStateRead.c_str();
   _jsonGameState->Deserialise(cstringCurrentGameStateRead);

   std::string filePathPreviousGameState = GetPreviousGameStatePath();
   if (filePathPreviousGameState.length() > 0)
   {
      std::string previousGameStateRead = ReadFromFile(filePathPreviousGameState);
      if (previousGameStateRead != "" && previousGameStateRead.length() > 0)//Did we read any data
      {
         _previousJsonGameState = new JsonHelper();
         const char* cstringPreviousGameStateRead = previousGameStateRead.c_str();
         _previousJsonGameState->Deserialise(cstringPreviousGameStateRead);
      }
   }
   return true;
}

void PlayGame::PopulateGameState()
{
   if (_gameState != nullptr)//Retrieve Previous State Data starting from  Phase 2 Round 2 
   {
      JsonHelper* playerJsonMapData = _jsonGameState->GetJsonObject("PlayerMap");
      _gameState->SetPlayerMapState(playerJsonMapData);
      playerJsonMapData->Release();

      JsonHelper* opponentJsonMapData = _jsonGameState->GetJsonObject("OpponentMap");
      _gameState->SetOpponentMapState(opponentJsonMapData);
      opponentJsonMapData->Release();

      _gameState->SetGameVersion(_jsonGameState->GetString("GameVersion"));
      _gameState->SetGameLevel(static_cast<unsigned __int16 >(_jsonGameState->GetInt("GameLevel")));
      _gameState->SetRound(static_cast<unsigned __int16 >(_jsonGameState->GetInt("Round")));

      //phase should have already been stored
      //JsonHelper* player1Map =_jsonGameState->GetJsonObject("Player1Map");
      //JsonHelper* player1Map=_jsonGameState->GetJsonObject("Player2Map");
   }

   //Previous Game State
   if (_previousJsonGameState != nullptr)//Retrieve Previous State Data starting from  Phase 2 Round 2 
   {
      _gameState->RestorePreviousGameState(_previousJsonGameState);
   }

   _gameState->DetermineHitList();
   _gameState->RefineHitList();//Remove destroyed ship cells

   _shootingAI = new Shooting(_gameState);
}
void PlayGame::DeployShipsFromFile()
{
   std::vector<std::string> shipLoctaion;

   std::string deployShipPath = "";
   char exepath[MAX_PATH + 1] = { 0 };
   if (GetModuleFileName(0, exepath, MAX_PATH + 1))
   {
      std::string fullExePath = std::string(exepath);
      std::string exePathWithoutExeFileName = fullExePath.substr(0, fullExePath.find_last_of("\\"));
      deployShipPath = exePathWithoutExeFileName + "\\" + "deploy.txt";
   }
   std::string previousGameStateRead = ReadFromFile(deployShipPath);
   std::string filepath = _workingDir + "\\" + placeFilename;
   WriteToFile(filepath, previousGameStateRead);
}
void PlayGame::DeployShips()
{
   std::vector<std::string> shipLoctaion;
   shipLoctaion.reserve(5);//expect 5 ships

   if (_gameState->GetMapDimensions() == 14)
   {
      shipLoctaion.push_back("Battleship 1 10 South\n");
      shipLoctaion.push_back("Carrier 12 8 South\n");
      shipLoctaion.push_back("Cruiser 5 12 East\n");
      shipLoctaion.push_back("Submarine 2 6 South\n");
      shipLoctaion.push_back("Destroyer 4 1 East\n");
   }
   else if (_gameState->GetMapDimensions() == 10)
   {
      shipLoctaion.push_back("Battleship 1 1 East\n");
      shipLoctaion.push_back("Carrier 5 8 South\n");
      shipLoctaion.push_back("Cruiser 6 1 East\n");
      shipLoctaion.push_back("Submarine 4 7 West\n");
      shipLoctaion.push_back("Destroyer 1 8 East\n");
   }
   else if (_gameState->GetMapDimensions() == 7)
   {
      shipLoctaion.push_back("Battleship 0 2 North\n");
      shipLoctaion.push_back("Carrier 1 6 East\n");
      shipLoctaion.push_back("Cruiser 5 3 North\n");
      shipLoctaion.push_back("Submarine 4 1 East\n");
      shipLoctaion.push_back("Destroyer 2 1 North\n");
   }

   std::string filepath = _workingDir + "\\" + placeFilename;
   WriteToFile(filepath, shipLoctaion);
}

void PlayGame::FireShot()
{
   _shootingAI->Fire();
   Point fireShot = _shootingAI->GetFireLocation();
   int command = _shootingAI->GetFireCommand();

   std::string filePathCommand = _workingDir + "\\" + commandFilename;
   std::string shot = std::to_string(command);
   shot.append(",");
   shot.append(std::to_string(fireShot._x));
   shot.append(",");
   shot.append(std::to_string(fireShot._y));

   WriteToFile(filePathCommand, shot);//the command to carry out
}

void PlayGame::SetInitialGameStateAttributes()
{
   unsigned __int8  phase = static_cast<unsigned __int8 >(_jsonGameState->GetInt("Phase"));
   _gameState->SetPhase(phase);
   unsigned __int8  mapDimension = static_cast<unsigned __int8 >(_jsonGameState->GetInt("MapDimension"));
   _gameState->SetMapDimensions(mapDimension);
}

std::string PlayGame::GetPlayerKey()
{
   return _playerKey;
}

std::string PlayGame::GetWorkingDirectory()
{
   return _workingDir;
}

void PlayGame::SaveCurrentGameStateData(bool gameEnded)
{
   Json::Value currentGameStateToSave;
   _gameState->CreatePreviousGameStateToSave(_shootingAI->GetFireLocation(), currentGameStateToSave);
   Json::FastWriter writer;
   std::string previousGameState = writer.write(currentGameStateToSave);
   //currentGameStateToSave.Serialise(previousGameState);

   //store previous game state
   std::string filePathPreviousGameState = GetPreviousGameStatePath();
   if ((filePathPreviousGameState.length() > 0) && gameEnded==false)
   {
      WriteToFile(filePathPreviousGameState, previousGameState);
   }
   else if ((filePathPreviousGameState.length() > 0) && gameEnded == true)
   {
      //lets save the final game state for review :)
      std::string finalGameStatePath = filePathPreviousGameState.substr(0, filePathPreviousGameState.find_last_of(".")) +"Final.txt";
      WriteToFile(finalGameStatePath, previousGameState);
   }
}

//Helper Read/Write from/to file Functions
#pragma region Helpers
std::string PlayGame::GetPreviousGameStatePath()
{
   std::string filePathPreviousGameState = "";
   char exepath[MAX_PATH + 1] = { 0 };
   if (GetModuleFileName(0, exepath, MAX_PATH + 1))
   {
      std::string fullExePath = std::string(exepath);
      std::string exePathWithoutExeFileName = fullExePath.substr(0, fullExePath.find_last_of("\\"));
      filePathPreviousGameState = exePathWithoutExeFileName + "\\" + previousGameStateFilename;
   }
   return filePathPreviousGameState;
}

std::string PlayGame::ReadFromFile(std::string filepath)
{
   std::ifstream ifs;
   ifs.open(filepath);

   std::stringstream bufferStream;
   bufferStream << ifs.rdbuf();
   std::string bufferFileData = bufferStream.str();

   ifs.close();
   return bufferFileData;
}

void PlayGame::WriteToFile(std::string filepath, std::vector<std::string>& data)
{
   std::ofstream ofs;
   ofs.open(filepath);

   for (int index = 0; index < static_cast<int>(data.size()); index++)
   {
      ofs << data.at(index);
   }

   ofs.close();
}
void PlayGame::WriteToFile(std::string filepath, std::string data, bool append)
{
   std::ofstream ofs;
   if (append)
   {
      ofs.open(filepath, std::ios_base::app);
   }
   else
   {
      ofs.open(filepath);
   }

   ofs << data;

   ofs.close();
}
#pragma endregion