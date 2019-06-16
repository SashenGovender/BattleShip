#ifndef SHOOTING
#define SHOOTING
#include "GameState.h"
#include <algorithm>//sort
#include <math.h>  //round

struct PointWeight
{
   Point _point;
   unsigned __int8 _weight;
   PointWeight()
   {
      _weight = 0;
      _point._x = 0;
      _point._y = 0;
   };
   PointWeight(Point point, unsigned __int8 weight)
   {
      _point = point;
      _weight = weight;
   };
};

class Shooting
{
private:
   unsigned __int8 _minimumLivingShipLength;
   GameState* _gameStateShoot;
   Point _nextHitLocation;
   Command _command;
   std::vector<PointWeight> _gridWeighting;
   unsigned __int8 _mapDimension;
   OpponentMap*  _opponentMap;
   PlayerMap*  _playerMap;
   unsigned __int8 _minimumFireEnergyRequired;

   void FindMinimumLivingShipLength();
   bool IsPointAvailable(Point point) const;
   unsigned __int8 FindWeightInDirection(Point point, Direction direction) const;
   bool TryDirectionPointShot(Point centreHitPoint, Direction direction);
   PointWeight BestPointWeightInCrossArea(Point point) const;
   Point GetNewDirectionPoint(Point point, unsigned __int8 poistionChange, Direction direction) const;
   Direction GetReverseDirection(Direction direction);
   bool CanUseShipSpecialWeapon(std::string shipType, Command command);
   void DetermineCommand();
   bool ShouldDeployShield() const;
   void OptimiseShieldCentre();
   bool Target();
   void HuntV2();//time to find a partial hit;
   void DeterminePointWeightings();
   unsigned __int8 CalculatePointWeighting(Point point) const;
   bool IsThisAValidPoint(Point point) const;
public:
   Shooting();
   Shooting(GameState* gameState);
   ~Shooting();

   void Fire();
   Point GetFireLocation() const;
   unsigned __int8 GetFireCommand() const;

};

#endif