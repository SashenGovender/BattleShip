#include<iostream>
#include<fstream>
#include <sstream>

#include "PlayGame.h"

int main(int argc, char** argv)
{
   if (argc != 3)
   {
      std::cout << "Usage: SashenGBattleBot.exe PlayerKey WorkingDirectory" << std::endl;
      return 1;
   }

   PlayGame* timeToWin = new PlayGame(argv[1], argv[2]);
   timeToWin->Play();
   delete timeToWin;

   return 0;
}

//Debug Main
//int main(int argc, char** argv)
//{
//   std::string workingDirPhase1 = "D:\\Downloads\\Entelect\\Game.Engine.-.Version.1.2.0\\Version 1.2.0\\Game Engine\\Replays\\2017-08-30 22-35-29-643\\Phase 1 - Round 0\\B";
//   std::string workingDirPhase2 = "D:\\Downloads\\Entelect\\Game.Engine.-.Version.1.2.0\\Version 1.2.0\\Game Engine\\Replays\\2017-08-30 22-35-29-643\\Phase 2 - Round 89\\B";
//   std::string key = "B";
//   PlayGame* timeToWin = new PlayGame(key, workingDirPhase2);
//
//   timeToWin->Play();
//   delete timeToWin;
//
//   system("pause");
//   return 0;
//}
