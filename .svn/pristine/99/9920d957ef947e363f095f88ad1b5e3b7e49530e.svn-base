#include "GameState.h"

GameState::GameState()
{
   _playerMap = new PlayerMap();
   _opponentMap = new OpponentMap();
   _gameVersion = "";
   _gameLevel = 0;
   _round = 0;
   _mapDimensions = 0;
   _phase = 0;
   _player1Map = nullptr;
   _player2Map = nullptr;
   _previousDestroyedShipCount = 0;
}

GameState::~GameState()
{
   if (_playerMap != nullptr)
   {
      delete _playerMap;
      _playerMap = nullptr;
   }

   if (_opponentMap != nullptr)
   {
      delete _opponentMap;
      _opponentMap = nullptr;
   }
}

PlayerMap* GameState::GetPlayerMap() const
{
   return _playerMap;
}

OpponentMap* GameState::GetOpponentMap() const
{
   return _opponentMap;
}

std::string GameState::GetGameVersion() const
{
   return _gameVersion;
}

unsigned __int16 GameState::GetGameLevel() const
{
   return _gameLevel;
}

unsigned __int16 GameState::GetRound() const
{
   return _round;
}

unsigned __int8 GameState::GetMapDimensions() const
{
   return _mapDimensions;
}

unsigned __int8 GameState::GetPhase() const
{
   return _phase;
}

PlayerMap* GameState::GetPlayer1Map() const
{
   return _player1Map;
}

PlayerMap* GameState::GetPlayer2Map() const
{
   return _player2Map;
}

//------------------------------------------------------------------------
void GameState::SetGameVersion(std::string gVersion)
{
   _gameVersion = gVersion;
}

void GameState::SetGameLevel(unsigned __int16 gLevel)
{
   _gameLevel = gLevel;
}

void GameState::SetRound(unsigned __int16 round)
{
   _round = round;
}

void GameState::SetMapDimensions(unsigned __int8 mapDim)
{
   _mapDimensions = mapDim;
}

void GameState::SetPhase(unsigned __int8 phase)
{
   _phase = phase;
}

void GameState::SetPlayer1Map(PlayerMap* pMap)
{
   _player1Map = pMap;
}

void GameState::SetPlayer2Map(PlayerMap* pMap)
{
   _player2Map = pMap;
}

void GameState::SetOpponentMapState(JsonHelper* opponentJsonMapData)
{
   _opponentMap->StoreOpponentMapData(opponentJsonMapData);
}
void GameState::SetPlayerMapState(JsonHelper* playerJsonMapData)
{
   _playerMap->StorePlayerMapData(playerJsonMapData);
}

//Previous Game State logic ahead
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
void GameState::RestorePreviousGameState(JsonHelper* previousGameStateJson)
{
   int cellIndex = 0;
   JsonHelper* destoyedCells = previousGameStateJson->GetArray("DestroyedCells");
   JsonHelper* destoyedCell = destoyedCells->GetJsonObject(cellIndex);
   while (destoyedCell != nullptr)
   {
      __int8 x = static_cast<__int8>(destoyedCell->GetInt("X"));
      __int8 y = static_cast<__int8>(destoyedCell->GetInt("Y"));
      _previousShipsDestroyedCells.push_back(Point(x, y));

      destoyedCell->Release();
      cellIndex++;
      destoyedCell = destoyedCells->GetJsonObject(cellIndex);
   }
   destoyedCells->Release();

   _previousDestroyedShipCount = static_cast<unsigned __int8>(previousGameStateJson->GetInt("ShipDestroyedCount"));

   // we need to record the location of the destroyed ships
   int shipTypeCount = 0;
   JsonHelper* shipsDestroyed = previousGameStateJson->GetArray("ShipDestroyed");
   std::string destroyedShipType = shipsDestroyed->GetString(shipTypeCount);
   while (destroyedShipType.length() > 0)
   {
      _previousShipsTypesDestroyed.push_back(destroyedShipType);

      shipTypeCount++;
      destroyedShipType = shipsDestroyed->GetString(shipTypeCount);
   }
   shipsDestroyed->Release();

   JsonHelper* fireLocation = previousGameStateJson->GetJsonObject("FireLocation");
   _previousFireLocation._x = static_cast<__int8>(fireLocation->GetInt("X"));
   _previousFireLocation._y = static_cast<__int8>(fireLocation->GetInt("Y"));
   fireLocation->Release();
}

void GameState::DetermineHitList()
{
   std::unordered_map<Point, GridLocation*>  mapGrid = GetOpponentMap()->GetMapGrid();
   for (std::unordered_map<Point, GridLocation*>::const_iterator it = mapGrid.begin(); it != mapGrid.end(); ++it)
   {
      GridLocation* opponentCellLocation = it->second;
      if (opponentCellLocation->GetDamaged() == true)//Is this a damaged cell location? 
      {
         GridLocation location = *opponentCellLocation;
         Point point = Point(location.GetX(), location.GetY());
         _hitLocations.insert(std::make_pair(point,location));
      }
   }
}

void GameState::RefineHitList()
{
   unsigned __int8 playerShotsHit = GetPlayerMap()->GetShotsHits();
   if (playerShotsHit > _opponentMap->NumCurrentDestroyedShipsHits())//Do we have any partial hits?
   {
      RemoveDestroyedShipCellsFromHitList();//remove previous destroyed ships from the hit list
     //Is there any new Destroyed ships?
      if (_opponentMap->NumCurrentDestroyedShips() > _previousDestroyedShipCount)
      {
         // we now have a new destroyed ship
         Ship* newDestroyedShip = new Ship();
         if (FindNewDestroyedShip(newDestroyedShip))
         {
            //we have a ship with locations. Lets removes the ship from the hit list and update the previous ships destroyed
            UpdatePreviousDestroyedShipData(newDestroyedShip);
         }
         delete newDestroyedShip;
      }
   }
   //All hits are destroyed ship locations
   else if (playerShotsHit > 0 && (playerShotsHit == _opponentMap->NumCurrentDestroyedShipsHits()))
   {
      _previousShipsDestroyedCells.clear();
      _previousShipsTypesDestroyed.clear();
      _previousDestroyedShipCount = 0;
      _previousShipsDestroyedCells.reserve(_hitLocations.size());

      for (std::unordered_map<Point, GridLocation>::const_iterator it = _hitLocations.begin(); it != _hitLocations.end(); ++it)
      {
         _previousShipsDestroyedCells.push_back( it->first);
      }

      std::vector<Ship*>opponentShips=  _opponentMap->GetShips();
      for (int index = 0; index < static_cast<int>(opponentShips.size()); index++)
      {
         Ship* ship = opponentShips.at(index);
         if (ship->GetDestroyed() == true)
         {
            _previousShipsTypesDestroyed.push_back(ship->GetShipType());
         }
      }

      _previousDestroyedShipCount = _opponentMap->NumCurrentDestroyedShips();
      _hitLocations.clear();// remember we have no hits. all hits are destroyed points
   }
}

bool GameState::IsShipTypeDestroyedInPreviousState(std::string shipType) const
{
   std::vector < std::string>::const_iterator it;
   it= std::find(_previousShipsTypesDestroyed.begin(), _previousShipsTypesDestroyed.end(), shipType);
   if (it != _previousShipsTypesDestroyed.end())
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool GameState::IsPointInHitList(__int8 x, __int8 y) const
{   
   std::unordered_map<Point, GridLocation>::const_iterator it = _hitLocations.find(Point(x,y));
   if (it != _hitLocations.end())
   {
      return true;
   }
   return false;
}

bool GameState::RemovePointFromHitList(__int8 x, __int8 y)
{
   std::unordered_map<Point, GridLocation>::const_iterator it = _hitLocations.find(Point(x, y));
   if (it != _hitLocations.end())
   {
      _hitLocations.erase(it);
      return true;
   }
   return false;
}

bool GameState::FindNewDestroyedShip(Ship* newDestroyedShip)
{
   std::vector<Ship* > oppShips= GetOpponentMap()->GetShips();
   for (int index = 0; index < static_cast<int>(oppShips.size()); index++)
   {
      Ship* ship = oppShips.at(index);
      if (ship->GetDestroyed() == true && !IsShipTypeDestroyedInPreviousState(ship->GetShipType()))
      {
         *newDestroyedShip = *ship;
         break;         //we have found our new ship which is destroyed;
      }
   }

   if (FindDestroyedShipCells(newDestroyedShip, Direction::North))
   {
      return true;
   }
   else if (FindDestroyedShipCells(newDestroyedShip, Direction::South))
   {
      return true;
   }
   else if (FindDestroyedShipCells(newDestroyedShip, Direction::East))
   {
      return true;
   }
   else if (FindDestroyedShipCells(newDestroyedShip, Direction::West))
   {
      return true;
   }
   else
   {
      //if we get here. It means there is a destroyed ship but we cannot conclusively locate its position
      return false;
   }
}

bool GameState::FindDestroyedShipCells(Ship* newDestroyedShip, Direction direction)
{
   std::vector<Point> possibleNewShipCells;
   unsigned __int8 mapDimension = GetMapDimensions();

   for (int cellBlock = 1; cellBlock < static_cast<int>(newDestroyedShip->GetShipLength()); cellBlock++)
   {
      Point pointToCheck;
      switch (direction)
      {
      case North:
         pointToCheck = Point(_previousFireLocation._x, _previousFireLocation._y + cellBlock);
         break;

      case South:
         pointToCheck = Point(_previousFireLocation._x, _previousFireLocation._y - cellBlock);
         break;

      case East:
         pointToCheck = Point(_previousFireLocation._x + cellBlock, _previousFireLocation._y);
         break;

      case West:
         pointToCheck = Point(_previousFireLocation._x - cellBlock, _previousFireLocation._y);
         break;
      }

      if (_opponentMap->IsThisAValidMapPoint(mapDimension,pointToCheck) && IsPointInHitList(pointToCheck._x, pointToCheck._y))
      {
         possibleNewShipCells.push_back(pointToCheck);
         continue;
      }
      return false;//we could not find the ship cells
   }

   possibleNewShipCells.push_back(Point(_previousFireLocation._x, _previousFireLocation._y));
   if (possibleNewShipCells.size() == newDestroyedShip->GetShipLength())
   {
      //we did  find all our locations
      for (int index = 0; index < static_cast<int>(newDestroyedShip->GetShipLength()); index++)
      {
         Point point = Point(possibleNewShipCells.at(index)._x, possibleNewShipCells.at(index)._y);
         newDestroyedShip->AddShipCell(point,GridLocation(point._x, point._y));
      }
      return true;
   }

   return false;
}

void GameState::UpdatePreviousDestroyedShipData(Ship* newDestroyedShip)
{
   // just a precaution check if the destroyed ships cells are known? must be at least 2 locations
   if (newDestroyedShip->GetNumberShipCells() <= 1)
   {
      return;
   }

   // update the previous state data with information from the current 
   std::unordered_map<Point, GridLocation> shipCells = newDestroyedShip->GetShipCells();
   for (std::unordered_map<Point, GridLocation> ::const_iterator it = shipCells.begin(); it != shipCells.end(); ++it)
   {
      _previousShipsDestroyedCells.push_back(Point(it->first._x, it->first._y));

      _hitLocations.erase(it);// the destroyed ship point must be removed from hit list
   }

   _previousShipsTypesDestroyed.push_back(newDestroyedShip->GetShipType());
   _previousDestroyedShipCount++;

}

void GameState::RemoveDestroyedShipCellsFromHitList()
{
   for (int index = 0; index < static_cast<int>(_previousShipsDestroyedCells.size()); index++)
   {
      Point destroyedPoint = _previousShipsDestroyedCells.at(index);
      RemovePointFromHitList(destroyedPoint._x, destroyedPoint._y);// the destroyed ship point must be removed from the partial hit list to missed location list. a destroyed ship is a missed ship
   }
}

/* Sample PreviousState Json
"DestroyedCells": [
{
"X": 6,
"Y": 3,

},
{
"X": 6,
"Y": 4,

}],
"ShipDestroyedCount": 1,
"ShipDestroyed":["Destroyer"],
"FireLocation":
{
"X": 2,
"Y": 3,
}
*/
void GameState::CreatePreviousGameStateToSave(Point shotFireLocation, Json::Value& currentGameStateToStore)
{
   Json::Value destroyedCells(Json::arrayValue);
   for (int index = 0; index < static_cast<int>(_previousShipsDestroyedCells.size()); index++)
   {
      Json::Value cell;
      cell["X"] = _previousShipsDestroyedCells.at(index)._x;
      cell["Y"] = _previousShipsDestroyedCells.at(index)._y;
      destroyedCells[index] = cell;
   }
   currentGameStateToStore["DestroyedCells"] = destroyedCells;

   currentGameStateToStore["ShipDestroyedCount"] = _previousDestroyedShipCount;

   Json::Value shipTypeDestroyed(Json::arrayValue);
   for (int index = 0; index < static_cast<int>(_previousShipsTypesDestroyed.size()); index++)
   {
      shipTypeDestroyed.append(Json::Value(_previousShipsTypesDestroyed.at(index)));
   }
   currentGameStateToStore["ShipDestroyed"] = shipTypeDestroyed;

   Json::Value fireLocation;
   fireLocation["X"] = shotFireLocation._x;
   fireLocation["Y"] = shotFireLocation._y;
   currentGameStateToStore["FireLocation"] = fireLocation;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::unordered_map<Point, GridLocation> GameState::GetHitList() const
{
   return _hitLocations;
}

