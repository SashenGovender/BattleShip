#ifndef OPPONENTMAP
#define OPPONENTMAP
#include "Map.h"

class OpponentMap : public Map
{
private:
   bool _alive;
   std::unordered_map<Point, GridLocation*> _mapGrid;
public:
   OpponentMap();
   bool GetAlive() const;
   void SetAlive(bool alive);
   void StoreOpponentMapData(JsonHelper* opponentJsonMapData);
   bool IsMapPointEitherDamagedMissedShieldHit(Point point) const;
};

#endif