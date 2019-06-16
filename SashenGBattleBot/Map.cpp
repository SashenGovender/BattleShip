#include "Map.h"

Map::Map()
{
   _name = "";
   _points = 0;

   _ships.reserve(5);
}

Map::~Map()
{
   for (int index = 0; index < static_cast<int>(_ships.size()); index++)
   {
      Ship* ship = _ships.at(index);
      if (ship)
      {
         delete ship;
         ship = nullptr;
      }
   }

   for (std::unordered_map<Point, GridLocation*> ::const_iterator it = _cells.begin(); it != _cells.end(); ++it)
   {
      GridLocation* locationInfo = it->second;
      if (locationInfo)
      {
         delete locationInfo;
         locationInfo = nullptr;
      }
   }
}

Ship* Map::GetShipInfo(std::string shipType) const
{
   for (int index = 0; index <static_cast<int>( _ships.size()); index++)
   {
      Ship* ship = _ships.at(index);
      if (shipType.compare(ship->GetShipType())==0)
      {
         return ship;
      }
   }
   return nullptr;
}

GridLocation* Map::GetMapCell(Point point) const
{
   std::unordered_map<Point, GridLocation*> ::const_iterator it = _cells.find(point);
   if (it != _cells.end())
   {
      return _cells.at(point);
   }
   return nullptr;
}

std::string Map::GetName() const
{
   return _name;
}

unsigned __int16 Map::GetPoints() const
{
   return _points;
}

void Map::AddShip(Ship* ship)
{
   _ships.push_back(ship);
}

void Map::AddMapCell(Point point, GridLocation* location)
{
   std::unordered_map<Point, GridLocation*> ::const_iterator it = _cells.find(point);
   if (it == _cells.end())
   {
      _cells.insert(std::make_pair(point, location));
   }
}

void Map::SetName(std::string name)
{
   _name = name;
}

void Map::SetPoints(unsigned __int16  points)
{
   _points = points;
}

std::unordered_map<Point, GridLocation*> Map::GetMapGrid() const
{
   return _cells;
}

std::vector<Ship*> Map::GetShips() const
{
   return _ships;
}

bool Map::IsShipDestroyed(std::string shipType) const
{
   Ship* ship = GetShipInfo(shipType);
   if (ship != nullptr && ship->GetDestroyed() == true)
   {
      return true;
   }
   return false;
}

Ship* Map::GetLastRemainingShip() const
{
   for (int index = 0; index < static_cast<int>(_ships.size()); index++)
   {
      Ship* ship = _ships.at(index);
      if (IsShipDestroyed(ship->GetShipType()) == false)
      {
         return ship;
      }
   }
   return nullptr;
}

unsigned __int8 Map::NumCurrentDestroyedShips() const
{
   unsigned __int8 destoyedShipsCount = 0;
   for (int index = 0; index < static_cast<int>(_ships.size()); index++)
   {
      Ship* ship = _ships.at(index);
      if (IsShipDestroyed(ship->GetShipType()) == true)
      {
         destoyedShipsCount++;
      }
   }
   return destoyedShipsCount;
}

unsigned __int8 Map::NumCurrentDestroyedShipsHits() const
{
   unsigned  __int8 destoyedShipsCellCount = 0;
   for (int index = 0; index < static_cast<int>(_ships.size()); index++)
   {
      Ship* ship = _ships.at(index);
      if (IsShipDestroyed(ship->GetShipType()) == true)
      {
         destoyedShipsCellCount += ship->GetShipLength();
      }
   }
   return destoyedShipsCellCount;
}

bool Map::IsThisAValidMapPoint(unsigned __int8 mapDimension, Point point) const
{
   if (point._x < 0 || point._y < 0 || point._x >= mapDimension || point._y >= mapDimension)//if a point if equal to map dimension its invalid because our points start from 0,0 not 1,1
   {
      return false;// This is an invalid point
   }
   return true;
}

