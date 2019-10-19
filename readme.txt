**************************************************************************************************
Instructions to Build Project
**************************************************************************************************
* Unzip file
* Open the solution "SashenGBattleBot.sln" in visual studio and build project
* This will create the "SashenGBattleBot.exe" which is required to play the game

**************************************************************************************************
Brief Description
**************************************************************************************************
--------------------------
Project Structure
--------------------------
It was quite easy to see that the battleship game state would play an important role in the overall solution. So my first step was to accurately represent the game state by creating several contained object.  Hence the project was divided into multiple classes:

* Weapon – This represents the energy and type of weapon
* Gridlocation – Represents a single cell on the map. E.g. the x,y coordinates, damaged or missed…
* Ship – All information related to a ship. A ship has multiple cells on the map, a weapon, a length and whether or not it is destroyed
* Shield – I saw this command as being quite unique. So a Shield object was created. This houses the property of a shield such as radius, centre point, active…
* Map - A generic map which represent the battleship map such as ships, and the ocean (grid cells)
* OpponentMap – Inherits maps and adds the additional functionally to represent the opponents map
* PlayerMap - Inherits maps and adds the additional functionally to represent the players map. E.g. shots fired, shots hits, shield…
* Shooting – Logic to determine the next location to shot at and the associated command (singleShot, DoubleShot)
* GameState – Represents the entire state.json all accessible from this object
* JsonHelper – Used to assist with the associated json processing and representation
* Common – Meant to house common functionality used across objects
* PlayGame – The overarching logic of battleship. E.g. when to read the state.json. When to deploy and fire
* Main- project entry location

--------------------------
Strategy
--------------------------
* Start by reading the state.json file and populate my internal gameState object. The next step was to check if it is the first phase which required ships to be placed. Once the second phase has been reached I proceed to fire a shot along with a command

FireShot
^^^^^^^^
* Check if we have any partial hits (are there any damaged in the state.json). If no hits I randomly choose a location that is missed and fire
If there are partials, I proceed to remove the destroyed ships locations from the known damaged locations. This logic refines my list. I then choose one corner of this partial hit and fire the next shot.

How I track opponents destroyed ships
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
“When a ship is destroyed, the opponent must say that this ship is destroyed”.
* I compare the current game state to the previous and I process the changes. If a ship is destroyed in the current game state but not in the previous then I know that the previous damaged locations are in fact destroyed ship location. I then store this to a textfile in my exe’s root. I also store the previous destroyed ship count and previous fire location.

