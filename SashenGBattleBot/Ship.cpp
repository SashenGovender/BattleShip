#include "Ship.h"

Ship::Ship()
{
   _destroyed = false;
   _placed = false;
   _shipType = "";
   _shipLength = 0;
}
Ship::Ship(bool destroyed, std::string shipType)
{
   _destroyed = destroyed;
   _placed = false;
   _shipType = shipType;
   _shipLength = 0;
}
Ship::Ship(bool destroyed, std::string shipType, bool placed)
{
   _destroyed = destroyed;
   _placed = placed;
   _shipType = shipType;
   _shipLength = 0;
}
Ship::~Ship()
{

}
//-----------------------------------------------------------------------------
GridLocation* Ship::GetShipCellInfo(Point point)
{
   std::unordered_map<Point, GridLocation>::const_iterator it = _shipCells.find(point);
   if (it != _shipCells.end())
   {
      return &(_shipCells.at(point));
   }
   return nullptr;
}

std::unordered_map<Point, GridLocation> Ship::GetShipCells()
{
   return _shipCells;
}

unsigned __int8  Ship::GetNumberShipCells() const
{
   return static_cast<unsigned __int8>(_shipCells.size());
}

bool Ship::GetDestroyed() const
{
   return _destroyed;
}

bool Ship::GetPlaced() const
{
   return _placed;
}

std::string Ship::GetShipType() const
{
   return _shipType;
}

Weapon Ship::GetShipWeapon(int index)
{
   return _weapon.at(index);
}

//-----------------------------------------------------------------------------
void Ship::AddShipCell(Point point, GridLocation shipPosition)
{
   std::unordered_map<Point, GridLocation>::const_iterator it = _shipCells.find(point);
   if (it == _shipCells.end())
   {
      _shipCells.insert(std::make_pair(point, shipPosition));
   }
}

void Ship::StoreShipData(JsonHelper* singleShipJsonData)
{
   _destroyed = singleShipJsonData->GetBool("Destroyed");
   _placed = singleShipJsonData->GetBool("Placed");
   _shipType = singleShipJsonData->GetString("ShipType");
   SetShipLength(_shipType);

   JsonHelper* shipCells = singleShipJsonData->GetArray("Cells");
   if (shipCells == nullptr)
   {
      shipCells->Release();
      return;
   }

   int shipCellNumber = 0;
   JsonHelper* shipCell = shipCells->GetJsonObject(shipCellNumber);
   while (shipCell != nullptr)
   {
      bool occupied = shipCell->GetBool("Occupied");
      bool hit = shipCell->GetBool("Hit");
      bool shielded = shipCell->GetBool("Shielded");
      bool shieldedHit = shipCell->GetBool("ShieldHit");
      __int8 x = static_cast<__int8>(shipCell->GetInt("X"));
      __int8 y = static_cast<__int8>(shipCell->GetInt("Y"));
      AddShipCell(Point(x, y), GridLocation(occupied, hit, x, y, shielded, shieldedHit));

      shipCell->Release();
      shipCellNumber++;
      shipCell = shipCells->GetJsonObject(shipCellNumber);
   }

   JsonHelper* shipWeapons = singleShipJsonData->GetArray("Weapons");
   if (shipWeapons == nullptr)
   {
      shipWeapons->Release();
      return;
   }
   int shipWeaponsNumber = 0;
   JsonHelper* shipWeapon = shipWeapons->GetJsonObject(shipWeaponsNumber);
   _weapon.reserve(2);//expect 2 weapons

   while (shipWeapon != nullptr)
   {
      std::string weaponType = shipWeapon->GetString("WeaponType");
      unsigned __int8 energyRequired = static_cast<unsigned __int8>( shipWeapon->GetInt("EnergyRequired"));
      _weapon.push_back(Weapon(weaponType, energyRequired));

      shipWeapon->Release();
      shipWeaponsNumber++;
      shipWeapon = shipWeapons->GetJsonObject(shipWeaponsNumber);
   }

   shipWeapons->Release();
   shipCells->Release();
}

unsigned __int8  Ship::GetShipLength() const
{
   return _shipLength;
}

void Ship::SetShipLength(std::string shipType)
{
   if (!(shipType.compare("Submarine")))
   {
      _shipLength = 3;
   }
   else if (!(shipType.compare("Destroyer")))
   {
      _shipLength = 2;
   }
   else if (!(shipType.compare("Battleship")))
   {
      _shipLength = 4;
   }
   else if (!(shipType.compare("Carrier")))
   {
      _shipLength = 5;
   }
   else if (!(shipType.compare("Cruiser")))
   {
      _shipLength = 3;
   }
}

unsigned __int8  Ship::GetNumberShipHits() const
{
   __int8 shipHit = 0;
   for (std::unordered_map<Point, GridLocation>::const_iterator it = _shipCells.begin(); it != _shipCells.end(); ++it)
   {
      if ((it->second).GetHit())
      {
         shipHit++;
      }
   }
   return shipHit;
}

Ship& Ship::operator=(const Ship &rhs)
{
   using std::swap;
   _destroyed = rhs.GetDestroyed();
   _placed = rhs.GetPlaced();
   swap(_shipType, rhs.GetShipType());
   _shipLength = rhs.GetShipLength();

   return *this;
}
