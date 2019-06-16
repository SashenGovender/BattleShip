#ifndef COMMON
#define COMMON
#include <unordered_map>

namespace
{
   const char* stateFilename = "state.json";
   const char* placeFilename = "place.txt";
   const char* commandFilename = "command.txt";
   const char* previousGameStateFilename = "PreviousGameState.txt";
}

struct Point
{
   __int8 _x;
   __int8 _y;
   Point()
   {
      _x = 0;
      _y = 0;
   };
   Point(__int8 x, __int8 y)
   {
      _x = x;
      _y = y;
   };
   bool operator==(const Point &otherPoint) const
   {
      return (_x == otherPoint._x  && _y == otherPoint._y);
   }
};

enum Direction
{
   North,
   South,
   East,
   West
};
/*enum ShipType
{
Battleship,
Carrier,
Cruiser,
Destroyer,
Submarine
}*/

enum Command
{
   DoNothing = 0,
   FireShotCommand = 1,
   DoubleShot,
   CornerShot=4,
   CrossShotDiagonal,
   CrossShotHorizontal,
   SeekerMissile,
   PlaceShield = 8,
};

namespace std {

   template <>
   struct hash<Point>
   {
      std::size_t operator()(const Point& k) const
      {
         using std::hash;

         // Compute individual hash values for first,
         // second and third and combine them using XOR
         // and bit shifting:

         return ((hash<__int8>()(k._x)^ (hash<__int8>()(k._y) << 1)) >> 1);
      }
   };

}
#endif