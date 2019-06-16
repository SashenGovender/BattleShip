#ifndef WEAPON
#define WEAPON
#include <string>
#include <iostream>


class Weapon
{
private:
   unsigned __int8 _energyrequired;
   std::string _weaponType;

public:
   Weapon();
   Weapon(std::string weaponType, unsigned __int8 energyRequired);
   __int8 GetEnergyRequired();
   std::string GetWeaponType();
   void SetEnergyRequired(unsigned __int8 energyRequired);
   void SetWeaponType(std::string weaponType);
};

#endif