#ifndef MAP
#define MAP

#include "GridLocation.h"
#include "Ship.h"
#include <vector>
#include <string>
#include <unordered_map>

class Map
{
private:
   std::vector< Ship*> _ships;
   std::unordered_map<Point,GridLocation*> _cells;
   std::string _name;
   unsigned __int16 _points;

public:
   Map();
   ~Map();

   GridLocation* GetMapCell(Point point) const;
   std::unordered_map<Point, GridLocation*> GetMapGrid() const;
   void AddMapCell(Point point, GridLocation* shipPositions);

   std::string GetName() const;
   unsigned __int16 GetPoints() const;
   void SetName(std::string name);
   void SetPoints(unsigned __int16  points);

   void AddShip(Ship* ship);
   Ship* GetShipInfo(std::string shipType) const;
   std::vector< Ship*>  GetShips() const;
   Ship* GetLastRemainingShip() const;
   bool IsShipDestroyed(std::string shipType) const;
   unsigned __int8  NumCurrentDestroyedShips() const;
   unsigned __int8  NumCurrentDestroyedShipsHits() const;
   bool IsThisAValidMapPoint(unsigned __int8 mapDimension,Point point) const;
};

#endif