#ifndef SHIELD
#define SHIELD
#include "Common.h"
#include "JsonHelper.h"

class Shield
{
private:
   unsigned __int8 _chargeTime;
   unsigned __int8 _currentCharges;
   unsigned __int8 _currentRadius;
   unsigned __int8 _maxRadius;
   unsigned __int16 _roundLastUsed;
   bool _active;
   Point _centrePoint;

public:
   Shield();
   Shield::Shield(unsigned __int8 chargeTime, unsigned __int16 roundsLastUsed, unsigned __int8 currentCharges, bool active, unsigned __int8 currentRadius, unsigned __int8 maxRadius, Point point);
   void StoreShieldData(JsonHelper* shieldJsonData);
   unsigned __int8 GetChargeTime() const;
   unsigned __int16 GetRoundLastUsed() const;
   unsigned __int8 GetCurrentCharges() const;
   bool GetActive() const;
   unsigned __int8 GetCurrentRadius() const;
   unsigned __int8 GetMaxRadius() const;
   Point GetCenterPoint() const;
};

#endif