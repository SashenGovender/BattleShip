#include "GridLocation.h"

GridLocation::GridLocation()
{
   _damaged = false;
   _missed = false;
   _x = -1;
   _y = -1;
   _shieldHit = false;;
   _shielded = false;;
   _hit = false;
   _occupied = false;
}

GridLocation::GridLocation(__int8 x, __int8 y)
{
   _damaged = false;
   _missed = false;
   _x = x;
   _y = y;
   _shieldHit = false;;
   _shielded = false;;
   _hit = false;
   _occupied = false;
}
GridLocation::GridLocation(bool occupied, bool hit, __int8 x, __int8 y,bool shielded,bool shieldedHit)
{
   _damaged = false;
   _missed = false;
   _x = x;
   _y = y;
   _shieldHit = shieldedHit;;
   _shielded = shielded;;
   _hit = hit;
   _occupied = occupied;
}

//-----------------------------------------------------------------------
bool GridLocation::GetDamaged() const
{
   return _damaged;
}

bool GridLocation::GetMissed() const
{
   return _missed;
}

__int8 GridLocation::GetX() const
{
   return _x;
}

__int8 GridLocation::GetY() const
{
   return _y;
}

bool GridLocation::GetShieldHit() const
{
   return _shieldHit;
}

bool GridLocation::GetShielded() const
{
   return _shielded;
}

bool GridLocation::GetHit() const
{
   return _hit;
}

bool GridLocation::GetOccupied() const
{
   return _occupied;
}

bool GridLocation::IsPointEitherDamagedMissedShieldHit() const
{
   if (_damaged == true || _missed == true || _shieldHit == true)
   {
      return true;
   }
   return false;
}

void GridLocation::StorePlayerLocationData(JsonHelper* singleCellJsonData)
{
   _occupied = singleCellJsonData->GetBool("Occupied");
   _hit = singleCellJsonData->GetBool("Hit");
   _x = static_cast<__int8>(singleCellJsonData->GetInt("X"));
   _y = static_cast<__int8>(singleCellJsonData->GetInt("Y"));
   _shielded = singleCellJsonData->GetBool("Shielded");
   _shieldHit = singleCellJsonData->GetBool("ShieldHit");
}

void GridLocation::StoreOpponentLocationData(JsonHelper* singleCellJsonData)
{
   _damaged = singleCellJsonData->GetBool("Damaged");
   _missed = singleCellJsonData->GetBool("Missed");
   _x = static_cast<__int8>(singleCellJsonData->GetInt("X"));
   _y = static_cast<__int8>(singleCellJsonData->GetInt("Y"));
   _shieldHit = singleCellJsonData->GetBool("ShieldHit");
}

GridLocation::GridLocation(const GridLocation &copyFrom)
{
   _damaged = copyFrom._damaged;
   _missed = copyFrom._missed;
   _x = copyFrom._x;
   _y = copyFrom._y;
   _shieldHit = copyFrom._shieldHit;
   _shielded = copyFrom._shielded;
   _hit = copyFrom._hit;
   _occupied = copyFrom._occupied;
}
