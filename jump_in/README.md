  					Jump In
  					written by : Orpaz Houta								 
  					Last update : 1.2.22									 
 
 An actual game you can play on the terminal.

* In order to play:
  - Run the command "./play" at the terminal.
  - Build & run the project at your IDE.

* End of game - You finish all the levels.
* End of level - all the rabbits inside a hole.                              

- Game prossess:
  - Move the parts on the board acording to every part rules until you put
  - all the rabbits to their hole.
  - to move parts on the board, write the name & the id of the part you
    wish to move, 
  than add a space and the direction you choose according to:
   -   8(up) 
   -   6(right) 
   -   2(down) 
   -   4(left)
   for example - 'rabbit1 8' or 'fox2 2'
 
 * Game options:
   - 1. 'solve' - to automatically solve the level
   - 2. 'rules' - to print the rules
   - 3. 'quit' - to quit the game
   - 4. 'undo' - to cancel the last movement
  
 * Parts Rules:                                                              
 * Mushrooms:
   - are stationary & cannot be moved (1 space on the board)                    
 * Foxes:
   - can only move backward or forward. 
   - foxes cannot jump over obstacles (2 spaces on the board)                                              
 * Rabbits:
   - move by jumping horizontally or vertically over one or more     
     spaces with obstacles (other rabbits, mushrooms, foxes or       
     combination of these)                                           
   - rabbits must land on the first empty space after a jump - means 
     they can never jump over empty spaces.                          
   - rabbits can never move without jumping over at least 1 obstacle,
     thus they can't move to adjacent space.                         
   - rabbits cannot jump over an empty hole.                         
   - rabbits can jump over a fox no matter the orientation           
    (tail/front/over the side).
            
  * Notes
    - it is possible to choose more advance level by adding wanted level as an 
      enviroment variable.
            
  GoodLuck!!
