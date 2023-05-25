#include <iostream>
#include <ctime>
#include "MainManager.h"

int main() {
    srand(time(NULL));
    Map map;
    InitGame(&map);

   std::cout << R"(
               __            ________  ___________  ____  ____      ___________   __      ___       _______  
              /""\          /"       )("     _   ")("  _||_ " |    ("     _   ") /""\    |"  |     /"     "| 
             /    \        (:   \___/  )__/  \\__/ |   (  ) : |     )__/  \\__/ /    \   ||  |    (: ______) 
            /' /\  \        \___  \       \\_ /    (:  |  | . )        \\_ /   /' /\  \  |:  |     \/    |   
           //  __'  \        __/  \\      |.  |     \\ \__/ //         |.  |  //  __'  \  \  |___  // ___)_  
          /   /  \\  \      /" \   :)     \:  |     /\\ __ //\         \:  | /   /  \\  \( \_|:  \(:      "| 
         (___/    \___)    (_______/       \__|    (__________)         \__|(___/    \___)\_______)\_______) )" << std::endl;
  
   std::cout << "\n\n\t\t\t\t\t" << "A short 2D C++ story bough to you by" << R"(

        ____                                 __  __                                __        
       / __ \___  ____  ____  __  _______   / / / /__  _________  ____ _____  ____/ /__  ____
      / / / / _ \/ __ \/ __ \/ / / / ___/  / /_/ / _ \/ ___/ __ \/ __ `/ __ \/ __  / _ \/_  /
     / /_/ /  __/ / / / / / / /_/ (__  )  / __  /  __/ /  / / / / /_/ / / / / /_/ /  __/ / /_
    /_____/\___/_/ /_/_/ /_/\__, /____/  /_/ /_/\___/_/  /_/ /_/\__,_/_/ /_/\__,_/\___/ /___/
       ____       _       _/____/   __      ____                                             
      / __ \_____(_)___  / /  | |  / /___ _/ / /____                                         
     / / / / ___/ / __ \/ /   | | / / __ `/ / / ___/                                         
    / /_/ / /  / / /_/ / /    | |/ / /_/ / / (__  )                                          
    \____/_/  /_/\____/_/     |___/\__,_/_/_/____/                                           
                                                                                                                               )" << std::endl;

   system("pause");
   system("cls");

   std::cout << "\n   Hi! We are Dennys Hdz Muñiz and Oriol Valls Luna!" << std::endl;
   std::cout << "   and welcome to our Minimal RPG game!" << std::endl;
   std::cout << std::endl;
   std::cout << "   We have created a regular RPG but this one will" << std::endl;
   std::cout << "   be played on the console." << std::endl;
   std::cout << std::endl;
   std::cout << "   You spawn in a Dungeon" << std::endl;
   std::cout << std::endl;
   std::cout << "   Your goal is defeat all the enemies and collect" << std::endl;
   std::cout << "   everything that the chests contain." << std::endl;
   std::cout << std::endl;
   std::cout << "   Good Luck >:3\n" << std::endl;

   system("pause");
   system("cls");

            map.Dungeon();

    return 0;
}