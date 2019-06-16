#ifndef GRIDLOCATION
#define GRIDLOCATION
#include "JsonHelper.h"

class GridLocation
{
private:
   bool _damaged;
   bool _missed;
   __int8 _x;
   __int8 _y;
   bool _shieldHit;
   bool _shielded;
   bool _hit;
   bool _occupied;

public:
   GridLocation(__int8 x, __int8 y);
   GridLocation();
   GridLocation(bool occupied, bool hit, __int8 x, __int8 y, bool shielded, bool shieldedHit);
   GridLocation(const GridLocation &copyFrom);
   __int8 GetX() const;
   __int8 GetY() const;
   bool GetDamaged() const;
   bool GetMissed() const;
   bool GetShieldHit() const;
   bool GetShielded() const;
   bool GetHit() const;
   bool GetOccupied() const;
   bool IsPointEitherDamagedMissedShieldHit() const;
   void StorePlayerLocationData(JsonHelper* singleCellJsonData);
   void StoreOpponentLocationData(JsonHelper* singleCellJsonData);
};

#endif