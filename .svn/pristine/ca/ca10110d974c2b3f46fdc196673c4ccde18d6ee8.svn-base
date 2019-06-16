#include "OpponentMap.h"

OpponentMap::OpponentMap()
{
   _alive = true;
}

bool OpponentMap::GetAlive() const
{
   return _alive;
}

void OpponentMap::SetAlive(bool alive)
{
   _alive = alive;
}
void OpponentMap::StoreOpponentMapData(JsonHelper* opponentJsonMapData)
{
   JsonHelper* ships = opponentJsonMapData->GetArray("Ships");

   //Read Ship Opponent Data
   int shipIndex = 0;
   JsonHelper* singleShip = ships->GetJsonObject(shipIndex);
   while (singleShip != nullptr)
   {
      //Read ship data
      Ship* ship = new Ship();
      ship->StoreShipData(singleShip);
      AddShip(ship);

      singleShip->Release();
      shipIndex++;
      singleShip = ships->GetJsonObject(shipIndex);
   }
   ships->Release();

   //Read other opponents attributes
   SetAlive(opponentJsonMapData->GetBool("Alive"));
   SetPoints(static_cast<unsigned __int16>(opponentJsonMapData->GetInt("Points")));
   SetName(opponentJsonMapData->GetString("Name"));

   //Read Cell Opponent Cell Data
   JsonHelper* cells = opponentJsonMapData->GetArray("Cells");
   int cellIndex = 0;
   JsonHelper* cell = cells->GetJsonObject(cellIndex);
   while (cell != nullptr)
   {
      GridLocation* location = new GridLocation();
      location->StoreOpponentLocationData(cell);
      AddMapCell(Point(location->GetX(), location->GetY()), location);

      cell->Release();
      cellIndex++;
      cell = cells->GetJsonObject(cellIndex);
   }
   cells->Release();

   _mapGrid = GetMapGrid();
}

//***********************************************************************Check performance*****************
//The Point MUST be valid
bool OpponentMap::IsMapPointEitherDamagedMissedShieldHit(Point point) const
{
   //std::unordered_map<Point, GridLocation*>::const_iterator it = _mapGrid.find(point);

   //if (it == _mapGrid.end())
   //{
   //   return false;
   //}
   //if (it->second->IsPointEitherDamagedMissedShieldHit())
   //{
   //   return true;
   //}
   //return false;


   GridLocation* location = _mapGrid.at(point);
   if (location->IsPointEitherDamagedMissedShieldHit())
   {
      return true;
   }
   return false;
}

