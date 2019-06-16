#include "Shooting.h"

bool CompareWeights(const PointWeight &lhs, const PointWeight &rhs)
{
   return (lhs._weight > rhs._weight);
}

Shooting::Shooting(GameState* gameState)
{
   _gameStateShoot = gameState;
   _minimumLivingShipLength = 0;
   _command = Command::FireShotCommand;
   _mapDimension = _gameStateShoot->GetMapDimensions();
   _opponentMap = _gameStateShoot->GetOpponentMap();
   _playerMap = _gameStateShoot->GetPlayerMap();

   if (_mapDimension == 14)
   {
      _minimumFireEnergyRequired = 40;
   }
   else if (_mapDimension == 10)
   {
      _minimumFireEnergyRequired = 30;
   }
   else
   {
      _minimumFireEnergyRequired = 20;
   }
   
}

Shooting::Shooting()
{

}

Shooting::~Shooting()
{

}

void Shooting::HuntV2()//time to find a partial hit
{
   if (IsPointAvailable(Point(0, 0)))//first point
   {
      _nextHitLocation = Point(0, 0);
      return;
   }
   else  if (IsPointAvailable(Point(0, _mapDimension-2)))//second last point in first column
   {
      _nextHitLocation = Point(0, _mapDimension-2);
      return;
   }
   else  if (IsPointAvailable(Point(1, _mapDimension - 1)))// last point in second column
   {
      _nextHitLocation = Point(1, _mapDimension - 1);
      return;
   }
   else  if (IsPointAvailable(Point(_mapDimension-2, 0)))// second last column first point
   {
      _nextHitLocation = Point(_mapDimension-2, 0);
      return;
   }
   else  if (IsPointAvailable(Point(_mapDimension - 1, 1)))// last column second point
   {
      _nextHitLocation = Point(_mapDimension - 1, 1);
      return;
   }
   else  if (IsPointAvailable(Point(_mapDimension - 1, _mapDimension-1)))//last point
   {
      _nextHitLocation = Point(_mapDimension - 1, _mapDimension-1);
      return;
   }

   // let target the next highest weighted point
   std::sort(_gridWeighting.begin(), _gridWeighting.end(), CompareWeights);

   for (int index = 0; index < _gameStateShoot->GetMapDimensions(); index++)//no need to loop the entire grid. just a few
   {
      Point point = Point(_gridWeighting.at(index)._point._x, _gridWeighting.at(index)._point._y);
      if ((point._x + point._y) % 2 == 0)
      {
         _nextHitLocation = point;
         return;
      }
   }
   _nextHitLocation = Point(_gridWeighting.at(0)._point._x, _gridWeighting.at(0)._point._y);
}

void Shooting::DeterminePointWeightings()
{
   std::unordered_map<Point, GridLocation*>  mapGrid = _opponentMap->GetMapGrid();
   _gridWeighting.reserve(mapGrid.size());

   for (std::unordered_map<Point, GridLocation*>::const_iterator it = mapGrid.begin(); it != mapGrid.end(); ++it)
   {
      Point point = it->first;
      unsigned __int8  weight = CalculatePointWeighting(point);
      _gridWeighting.push_back(PointWeight(point, weight));
   }
}

unsigned __int8  Shooting::FindWeightInDirection(Point point, Direction direction) const
{
   unsigned __int8  weight = 0;
   //calculate weight for each direction
   for (int cellBlock = 1; cellBlock < 5; cellBlock++)
   {
      Point directionPoint = GetNewDirectionPoint(point, cellBlock, direction);
      if (IsPointAvailable(directionPoint))
      {
         weight++;
         continue;
      }
      break;
   }
   return weight;
}

unsigned __int8 Shooting::CalculatePointWeighting(Point originalPoint) const
{
   unsigned __int8 weight = 0;

   //original point 
   if (IsPointAvailable(originalPoint) == false)// if the original location is hit/damaged/shieldHit its weight it zero.
   {
      return 0;
   }

   //calculate weight for each direction
   weight = weight + FindWeightInDirection(originalPoint, Direction::West);
   weight = weight + FindWeightInDirection(originalPoint, Direction::East);
   weight = weight + FindWeightInDirection(originalPoint, Direction::North);
   weight = weight + FindWeightInDirection(originalPoint, Direction::South);

   return weight;
}

bool Shooting::IsThisAValidPoint(Point point) const
{
   if (point._x < 0 || point._y < 0 || point._x >= _mapDimension || point._y >= _mapDimension)//if a point if equal to map dimension its invalid because our points start from 0,0 not 1,1
   {
      return false;// This is an invalid point
   }
   return true;
}

Point Shooting::GetNewDirectionPoint(Point point, unsigned __int8 poistionChange, Direction direction) const
{
   Point newPoint = { 0,0 };
   switch (direction)
   {
   case North:
      newPoint = Point(point._x, point._y + poistionChange);
      break;

   case South:
      newPoint = Point(point._x, point._y - poistionChange);
      break;

   case East:
      newPoint = Point(point._x + poistionChange, point._y);
      break;

   case West:
      newPoint = Point(point._x - poistionChange, point._y);
      break;
   }

   return newPoint;
}

Direction Shooting::GetReverseDirection(Direction direction)
{
   switch (direction)
   {
   case North:
      return Direction::South;
      break;

   case South:
      return Direction::North;
      break;

   case East:
      return Direction::West;
      break;

   case West:
      return Direction::East;
      break;
   }
}

bool Shooting::TryDirectionPointShot(Point centreHitPoint, Direction direction)
{
   Point oppositeDirectionPoint = GetNewDirectionPoint(centreHitPoint, 1, GetReverseDirection(direction));
   if (IsThisAValidPoint(oppositeDirectionPoint) == false)
   {
      return false;//not a valid point
   }

   if (_gameStateShoot->IsPointInHitList(oppositeDirectionPoint._x, oppositeDirectionPoint._y))//Is the opposite adjacent point already hit? we now have a direction to try
   {
      Point adjacentDirectionPoint = GetNewDirectionPoint(centreHitPoint, 1, direction);//try hit at direction passed in because we found our line :)
      if (IsPointAvailable(adjacentDirectionPoint))
      {
         _nextHitLocation = adjacentDirectionPoint;
         return true;
      }
   }
   return false;
}
PointWeight Shooting::BestPointWeightInCrossArea(Point point) const
{
   PointWeight bestPointWeight = { {0,0},0 };
   Direction bestDirection;

   for (int direction = 0; direction < 4; direction++)
   {
      unsigned __int8 tempDirectionWeight = FindWeightInDirection(point, static_cast<Direction>(direction));
      if (tempDirectionWeight > bestPointWeight._weight)
      {
         bestDirection = static_cast<Direction>(direction);
         bestPointWeight._weight = tempDirectionWeight;
      }
   }

   bestPointWeight._point = GetNewDirectionPoint(point, 1, bestDirection);
   return bestPointWeight;
}
bool Shooting::Target()//we already have a partial hit, need to find the next partial
{
   std::unordered_map<Point, GridLocation>  hitList = _gameStateShoot->GetHitList();
   //if we only have 1 hit. lets use weighting to determine the next shot
   if (hitList.size() == 1)
   {
      std::unordered_map<Point, GridLocation>::const_iterator it = hitList.begin();
      Point hitPoint = it->first;
      PointWeight pointWeightToFire = BestPointWeightInCrossArea(hitPoint);

      if (pointWeightToFire._weight > 0)
      {
         _nextHitLocation = pointWeightToFire._point;
         return true;
      }
      //something went horribly wrong. we should not get here but if we do, Lets hunt instead
      return false;
   }

   // we know that there are atleast two hits here. check if there are any adjacent hits and fire
   for (std::unordered_map<Point, GridLocation> ::const_iterator it = hitList.begin(); it != hitList.end(); ++it)
   {
      Point centreHitPoint = it->first;
      if (TryDirectionPointShot(centreHitPoint, Direction::North))
      {
         return true;
      }
      else if (TryDirectionPointShot(centreHitPoint, Direction::South))
      {
         return true;
      }
      else if (TryDirectionPointShot(centreHitPoint, Direction::East))
      {
         return true;
      }
      else if (TryDirectionPointShot(centreHitPoint, Direction::West))
      {
         return true;
      }
   }

   //more than two hits. none adjacent.
   //lets just choose the first hit and decide to fire
   PointWeight bestPointWeightLocation;
   for (std::unordered_map<Point, GridLocation> ::const_iterator it = hitList.begin(); it != hitList.end(); ++it)
   {
      Point hitPoint = it->first;
      PointWeight pointWeightToFire = BestPointWeightInCrossArea(hitPoint);
      if (pointWeightToFire._weight > bestPointWeightLocation._weight)
      {
         bestPointWeightLocation = pointWeightToFire;
      }
   }

   if (bestPointWeightLocation._weight != 0)
   {
      _nextHitLocation = bestPointWeightLocation._point;
      return true;
   }

   return false;
}

bool Shooting::IsPointAvailable(Point point) const
{
   if (!IsThisAValidPoint(point))
   {
      return false;
   }

   if (_opponentMap->IsMapPointEitherDamagedMissedShieldHit(point) == true)// the point is damaged or missed or shielded 
   {
      return false;
   }
   return true;

}
void Shooting::FindMinimumLivingShipLength()
{
   _minimumLivingShipLength = 10;//a random large number 
   std::vector<Ship*> oppShips = _opponentMap->GetShips();
   for (int index = 0; index < static_cast<int>(oppShips.size()); index++)
   {
      Ship* ship = oppShips.at(index);
      if (ship->GetDestroyed() == false)
      {
         int shipLen = ship->GetShipLength();
         if (shipLen < _minimumLivingShipLength)
         {
            _minimumLivingShipLength = shipLen;
         }
      }
   }
}

void Shooting::Fire()
{
   if (ShouldDeployShield())
   {
      std::unordered_map<Point, GridLocation> shipCells = _playerMap->GetLastRemainingShip()->GetShipCells();
      std::unordered_map<Point, GridLocation>::const_iterator it = shipCells.begin();
      it++;//Choose the second cell location of the ship. Cannot go more than two because the ship we looking at could be the destroyer which has only two cells

      _nextHitLocation = it->first;//our shield centre point
      OptimiseShieldCentre();
      _command = Command::PlaceShield;

      return;
   }

   DeterminePointWeightings();
   if (_gameStateShoot->GetHitList().size() > 0)//Do we have any partial hits?
   {
      bool didWeFindNextShot = Target();
      if (didWeFindNextShot == false)
      {
         //something went horribly wrong. we should not get here but if we do, Lets hunt instead
         HuntV2();
      }
      _command = Command::FireShotCommand;
   }
   else
   {
      HuntV2();
      DetermineCommand();
   }
}

Point Shooting::GetFireLocation() const
{
   return _nextHitLocation;
}

unsigned __int8 Shooting::GetFireCommand() const
{
   return static_cast<unsigned __int8>(_command);
}

void Shooting::DetermineCommand()
{
   //we have no hits at the moment, lets see if we can fire a special command
   if (_playerMap->GetEnergy() < _minimumFireEnergyRequired) //Do we have the minimum required energy?
   {
      _command = Command::FireShotCommand;
      return;
   }

   if (CanUseShipSpecialWeapon("Submarine", Command::SeekerMissile))
   {
      return;
   }
   else if (CanUseShipSpecialWeapon("Battleship", Command::CrossShotDiagonal))
   {
      return;
   }
   else if (CanUseShipSpecialWeapon("Carrier", Command::CornerShot))
   {
      return;
   }
   else if (CanUseShipSpecialWeapon("Cruiser", Command::CrossShotHorizontal))
   {
      return;
   }
   else
   {
      _command = Command::FireShotCommand;
   }
}

bool Shooting::CanUseShipSpecialWeapon(std::string shipType, Command command) 
{
   Ship* ship = _playerMap->GetShipInfo(shipType);
   if (ship->GetDestroyed()==false)
   {
      if (_playerMap->GetEnergy() >= ship->GetShipWeapon(1).GetEnergyRequired()) //index 1 has the special weapon
      {
         _command = command;
      }
      else
      {
         //we wanted to use the special command of a non destroyed ship but domt have enough energy
         // lets do a single shot now and hope next round we will have enough energy for our special shot
         _command = Command::FireShotCommand;
      }
      return true;
   }
   return false;
}

bool Shooting::ShouldDeployShield() const
{
   //Is the shield currently active or we dont have enough energy -> we cannot deploy
   if (_playerMap->GetShield()->GetActive() == true || _playerMap->GetShield()->GetCurrentCharges() == 0)
   {
      return false;//lets not redeploy the shield if its active or no energy
   }

   if (_playerMap->GetShipsRemaining() == 1)//is this my last ship
   {
      //which ship is the last one remaining?
      Ship* ship = _playerMap->GetLastRemainingShip();

      //Does this ship have one only more hit to go before its destroyed?
      if (ship != nullptr && ((ship->GetNumberShipHits() + 2) == ship->GetNumberShipCells()))
      {
         return true;
      }
   }
   return false;
}

void Shooting::OptimiseShieldCentre()
{
   int currentRadius = _playerMap->GetShield()->GetCurrentRadius();
   int mapDimension = _gameStateShoot->GetMapDimensions();

   //lets try and maximise our shield location if the ship (which is our centre point atm) is on the border
   if (_nextHitLocation._x + currentRadius > mapDimension)
   {
      _nextHitLocation._x = mapDimension - currentRadius;
   }
   else if (_nextHitLocation._x - currentRadius < 0)
   {
      _nextHitLocation._x = currentRadius;
   }

   if (_nextHitLocation._y + currentRadius > mapDimension)
   {
      _nextHitLocation._y = mapDimension - currentRadius;
   }
   else if (_nextHitLocation._y - currentRadius < 0)
   {
      _nextHitLocation._y = currentRadius;
   }
}
