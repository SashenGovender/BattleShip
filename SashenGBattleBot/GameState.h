#ifndef GAMESTATE
#define GAMESTATE
#include<iostream>
#include "PlayerMap.h"
#include "OpponentMap.h"
#include "JsonHelper.h"

class GameState
{
private:
   PlayerMap* _playerMap;
   OpponentMap* _opponentMap;
   std::string _gameVersion;
   unsigned __int16 _gameLevel;
   unsigned __int16 _round;
   unsigned __int8 _mapDimensions;
   unsigned __int8 _phase;
   PlayerMap* _player1Map;
   PlayerMap* _player2Map;
   std::unordered_map<Point, GridLocation>_hitLocations;
   Point _previousFireLocation;
   std::vector<Point> _previousShipsDestroyedCells;
   std::vector<std::string> _previousShipsTypesDestroyed;
   unsigned __int8 _previousDestroyedShipCount;

   void SetPlayer1Map(PlayerMap* pMap);
   void SetPlayer2Map(PlayerMap* pMap);
   PlayerMap* GetPlayer1Map() const;
   PlayerMap* GetPlayer2Map() const;
   bool RemovePointFromHitList(__int8 x, __int8 y);
   bool IsShipTypeDestroyedInPreviousState(std::string shipType) const;
   void UpdatePreviousDestroyedShipData(Ship* newDestroyedShip);
   void RemoveDestroyedShipCellsFromHitList();
   bool FindNewDestroyedShip(Ship* newDestroyedShip);
   bool FindDestroyedShipCells(Ship* newDestroyedShip, Direction direction);

public:
   GameState();
   ~GameState();
   unsigned __int16 GetRound() const;
   unsigned __int8 GetMapDimensions() const;
   OpponentMap* GetOpponentMap() const;
   PlayerMap* GetPlayerMap() const;
   unsigned __int8 GetPhase() const;
   std::string GetGameVersion() const;
   unsigned __int16 GetGameLevel() const;

   void SetPlayerMapState(JsonHelper* playerJsonMapData);
   void SetOpponentMapState(JsonHelper* opponentJsonMapData);
   void SetRound(unsigned __int16 round);
   void SetMapDimensions(unsigned __int8 mapDim);
   void SetPhase(unsigned __int8 phase);
   void SetGameVersion(std::string gVersion);
   void SetGameLevel(unsigned __int16 gLevel);

   bool IsPointInHitList(__int8 x, __int8 y) const;
   void DetermineHitList();
   std::unordered_map<Point, GridLocation> GetHitList() const;
   void RestorePreviousGameState(JsonHelper* previousGameStateData);
   void CreatePreviousGameStateToSave(Point shotFireLocation, Json::Value& currentGameStateToStore);
   void RefineHitList();

};

#endif