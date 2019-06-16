#include "PlayerMap.h"

PlayerMap::~PlayerMap()
{
   if (_shield != nullptr)
   {
      delete _shield;
      _shield = nullptr;
   }
}

PlayerMap::PlayerMap()
{
   _failedFirstPhaseCommands = 0;
   _energy = 0;
   _killed = false;
   _isWinner = false;
   _shotsFired = 0;
   _shotsHits = 0;
   _shield = nullptr;
   _shipsRemaining = 0;
   _key = "";
   _mapWidth = 0;
   _mapHeight = 0;
}
//--------------------------------------------------------------------------------------
unsigned __int8 PlayerMap::GetFailedFirstPhaseCommands() const
{
   return _failedFirstPhaseCommands;
}

unsigned __int16 PlayerMap::GetEnergy() const
{
   return _energy;
}

bool PlayerMap::GetKilled() const
{
   return _killed;
}

bool PlayerMap::GetIsWinner() const
{
   return _isWinner;
}

unsigned __int16 PlayerMap::GetShotsFired() const
{
   return _shotsFired;
}

unsigned __int8 PlayerMap::GetShotsHits() const
{
   return _shotsHits;
}

Shield* PlayerMap::GetShield() const
{
   return _shield;
}

unsigned __int8 PlayerMap::GetShipsRemaining() const
{
   return _shipsRemaining;
}

std::string PlayerMap::GetKey() const
{
   return _key;
}

unsigned __int8 PlayerMap::GetMapWidth() const
{
   return _mapWidth;
}

unsigned __int8 PlayerMap::GetMapHeight() const
{
   return _mapHeight;
}

//---------------------------------------------------------------------------
void PlayerMap::SetFailedFirstPhaseCommands(unsigned __int8 failedCommands)
{
   _failedFirstPhaseCommands = failedCommands;
}

void PlayerMap::SetEnergy(unsigned __int16 energy)
{
   _energy = energy;
}

void PlayerMap::SetKilled(bool killed)
{
   _killed = killed;
}

void PlayerMap::SetIsWinner(bool winner)
{
   _isWinner = winner;
}

void PlayerMap::SetShotsFired(unsigned __int16 shotsFired)
{
   _shotsFired = shotsFired;
}

void PlayerMap::SetShotsHits(unsigned __int8 shotsHit)
{
   _shotsHits = shotsHit;
}

void PlayerMap::SetShield(Shield* shield)
{
   _shield = shield;
}

void PlayerMap::SetShipsRemaining(unsigned __int8 shipsRemain)
{
   _shipsRemaining = shipsRemain;
}

void PlayerMap::SetKey(std::string key)
{
   _key = key;
}

void PlayerMap::SetMapWidth(unsigned __int8 mapWidth)
{
   _mapWidth = mapWidth;
}

void PlayerMap::SetMapHeight(unsigned __int8 mapHeight)
{
   _mapHeight = mapHeight;
}
void PlayerMap::StorePlayerMapData(JsonHelper* playerJsonMapData)
{
   //Read Map attributes
   SetMapWidth(static_cast<unsigned __int8>(playerJsonMapData->GetInt("MapWidth")));
   SetMapHeight(static_cast<unsigned __int8>(playerJsonMapData->GetInt("MapHeight")));

   //Read Player cell data
   JsonHelper* cells = playerJsonMapData->GetArray("Cells");
   int cellIndex = 0;
   JsonHelper* cell = cells->GetJsonObject(cellIndex);
   while (cell != nullptr)
   {
      GridLocation* location = new GridLocation();
      location->StorePlayerLocationData(cell);
      AddMapCell(Point(location->GetX(), location->GetY()), location);

      cell->Release();
      cellIndex++;
      cell = cells->GetJsonObject(cellIndex);
   }
   cells->Release();

   //read owner attributes
   JsonHelper* ownerJsonData = playerJsonMapData->GetJsonObject("Owner");
   SetFailedFirstPhaseCommands(static_cast<unsigned __int8>(ownerJsonData->GetInt("FailedFirstPhaseCommands")));
   SetName(ownerJsonData->GetString("Name"));
   SetPoints(static_cast<unsigned __int16>(ownerJsonData->GetInt("Points")));
   SetEnergy(static_cast<unsigned __int16>(ownerJsonData->GetInt("Energy")));
   SetKilled(ownerJsonData->GetBool("Killed"));
   SetIsWinner(ownerJsonData->GetBool("IsWinner"));
   SetShotsFired(static_cast<unsigned __int16>(ownerJsonData->GetInt("ShotsFired")));
   SetShotsHits(static_cast<unsigned __int8>(ownerJsonData->GetInt("ShotsHit")));
   SetShipsRemaining(static_cast<unsigned __int8>(ownerJsonData->GetInt("ShipsRemaining")));
   SetKey(ownerJsonData->GetString("Key"));

   //read ship data
   JsonHelper* shipsJsonData = ownerJsonData->GetArray("Ships");
   int shipNumber = 0;
   JsonHelper* singleShipJsonData = shipsJsonData->GetJsonObject(shipNumber);
   while (singleShipJsonData != nullptr)
   {
      Ship* ship = new Ship();
      ship->StoreShipData(singleShipJsonData);
      AddShip(ship);

      singleShipJsonData->Release();
      shipNumber++;
      singleShipJsonData = shipsJsonData->GetJsonObject(shipNumber);
   }
   singleShipJsonData->Release();
   shipsJsonData->Release();

   //read shield data
   JsonHelper* shieldJsonData = ownerJsonData->GetJsonObject("Shield");
   Shield* shield = new Shield();
   shield->StoreShieldData(shieldJsonData);
   SetShield(shield);

   shieldJsonData->Release();
   ownerJsonData->Release();
}


