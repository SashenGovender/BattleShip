#include "Shield.h"

Shield::Shield()
{
   _chargeTime = 0;
   _roundLastUsed = 0;
   _currentCharges = 0;
   _active = false;
   _currentRadius = 0;
   _maxRadius = 0;
   _centrePoint = Point(0, 0);
}
Shield::Shield(unsigned __int8  chargeTime, unsigned __int16 roundsLastUsed, unsigned __int8  currentCharges, bool active, unsigned __int8  currentRadius, unsigned __int8  maxRadius, Point point)
{
   _chargeTime = chargeTime;
   _roundLastUsed = 0;
   _currentCharges = currentCharges;
   _active = active;
   _currentRadius = currentRadius;
   _maxRadius = maxRadius;
   _centrePoint = Point(point._x, point._y);
}

unsigned __int8 Shield::GetChargeTime() const
{
   return _chargeTime;
}

unsigned __int16 Shield::GetRoundLastUsed() const
{
   return _roundLastUsed;
}

unsigned __int8 Shield::GetCurrentCharges() const
{
   return _currentCharges;
}

bool Shield::GetActive() const
{
   return _active;
}

unsigned __int8 Shield::GetCurrentRadius() const
{
   return _currentRadius;
}

unsigned __int8 Shield::GetMaxRadius() const
{
   return _maxRadius;
}

Point Shield::GetCenterPoint() const
{
   return _centrePoint;
}
//------------------------------------------------------------------------------------

void Shield::StoreShieldData(JsonHelper* shieldJsonData)
{
   _chargeTime = static_cast<unsigned __int8 >(shieldJsonData->GetInt("ChargeTime"));
   _roundLastUsed = static_cast<unsigned __int16 >(shieldJsonData->GetInt("RoundLastUsed"));
   _currentCharges = static_cast<unsigned __int8 >(shieldJsonData->GetInt("CurrentCharges"));
   _active = shieldJsonData->GetBool("Active");
   _currentRadius = static_cast<unsigned __int8 >(shieldJsonData->GetInt("CurrentRadius"));
   _maxRadius = static_cast<unsigned __int8 >(shieldJsonData->GetInt("MaxRadius"));

   std::string centerPoint = shieldJsonData->GetString("CenterPoint");
   int locationOfSplit = centerPoint.find(",");
   __int8 x = static_cast<__int8 >(atoi(centerPoint.substr(0, locationOfSplit).c_str()));
   __int8 y = static_cast<__int8 >( atoi(centerPoint.substr(locationOfSplit).c_str()));
   _centrePoint = Point(x, y);
}

