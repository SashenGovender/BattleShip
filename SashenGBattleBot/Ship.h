#ifndef SHIP
#define SHIP

#include "Weapon.h"
#include "GridLocation.h"
#include "JsonHelper.h"
#include <vector>
#include "Common.h"
#include <unordered_map>

class Ship
{
private:
   std::unordered_map<Point, GridLocation> _shipCells;
   bool _destroyed;
   bool _placed;
   std::string _shipType;
   std::vector<Weapon> _weapon;//a ship can only have 2 weapon. the first is a normal weapon
   unsigned __int8 _shipLength;

public:
   Ship(bool destroyed, std::string shipType);
   Ship();
   Ship(bool destroyed, std::string shipType, bool placed);
   ~Ship();

   bool GetDestroyed() const;
   std::string GetShipType() const;
   GridLocation* GetShipCellInfo(Point point);
   std::unordered_map<Point, GridLocation>  GetShipCells();
   bool GetPlaced() const;
   Weapon GetShipWeapon(int index);
   void SetShipLength(std::string shipType);
   void StoreShipData(JsonHelper* singleShipJsonData);
   void AddShipCell(Point point, GridLocation shipPosition);
   unsigned __int8  GetNumberShipCells() const;
   unsigned __int8  GetShipLength() const;// this is only set on a game state read
   unsigned __int8  GetNumberShipHits() const;
   Ship& operator=(const Ship &Other);
};
#endif
