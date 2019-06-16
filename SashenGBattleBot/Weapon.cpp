#include "Weapon.h"

Weapon::Weapon()
{
   _energyrequired = 0;;
   _weaponType = "";
}

__int8 Weapon::GetEnergyRequired()
{
   return  _energyrequired;
}

std::string Weapon::GetWeaponType()
{
   return _weaponType;
}

Weapon::Weapon(std::string weaponType, unsigned __int8 energyRequired)
{
   _energyrequired = energyRequired;
   _weaponType = weaponType;
}

void Weapon::SetEnergyRequired(unsigned __int8 energyRequired)
{
   _energyrequired = energyRequired;
}

void Weapon::SetWeaponType(std::string weaponType)
{
   _weaponType = weaponType;
}
