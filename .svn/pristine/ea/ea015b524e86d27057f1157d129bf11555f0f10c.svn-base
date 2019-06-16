#ifndef PLAYERMAP
#define PLAYERMAP
#include "Map.h"
#include "Shield.h"

class PlayerMap : public Map
{
private:
   unsigned __int8 _failedFirstPhaseCommands;
   unsigned __int16 _energy;
   bool _killed;
   bool _isWinner;
   unsigned __int16 _shotsFired;
   unsigned __int8 _shotsHits;
   Shield* _shield;
   unsigned __int8 _shipsRemaining;
   std::string _key;
   unsigned __int8 _mapWidth;
   unsigned __int8 _mapHeight;

   void SetFailedFirstPhaseCommands(unsigned __int8 failedCommands);
   void SetEnergy(unsigned __int16 energy);
   void SetKilled(bool killed);
   void SetIsWinner(bool winner);
   void SetShotsFired(unsigned __int16 shotsFired);
   void SetShotsHits(unsigned __int8 shotsHit);
   void SetShield(Shield* shield);
   void SetShipsRemaining(unsigned __int8 shipsRemain);
   void SetKey(std::string key);
   void SetMapWidth(unsigned __int8 mapWidth);
   void SetMapHeight(unsigned __int8 mapHeight);

public:
   PlayerMap();
   ~PlayerMap();
   void StorePlayerMapData(JsonHelper* playerMap);
   unsigned __int8 GetShotsHits() const;
   unsigned __int8 GetFailedFirstPhaseCommands() const;
   unsigned __int16 GetEnergy() const;
   bool GetKilled() const;
   bool GetIsWinner() const;
   unsigned __int16 GetShotsFired() const;
   Shield* GetShield() const;
   unsigned __int8 GetShipsRemaining() const;
   std::string GetKey() const;
   unsigned __int8 GetMapWidth() const;
   unsigned __int8 GetMapHeight() const;
   //Ship* GetLastRemainingShip() const;
  // bool IsShipDestroyed(std::string shipType) const;
};

#endif
