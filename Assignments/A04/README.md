# Assignment A04
- This assignment had two parts
  - To add int `int frameRate` & `int frameCounter` to the `gameOfLife` struct
  - Use the two to limit the speed that it redraws the window.
  
 ## Part 1
  - The implementation of these two were fairly simple and added into the struct. 
  I chose however to set `int frameCounter` with `const int FRAMERATE` so that possible
  future use of the variable after changing would be easier to reuse as well as change
  
 ## Part 2
  - While there were many options of doing this, I chose to do it in the while loop that draws the window.
  I chose this as to make the drawing of the `frameCounter` or the generation count easier when it is later
  implemented. The drawing was controlled by setting a for loop before it draws, as well as an if statement
  To count up to the `frameRate` desired, and only run it when it is equal to the amount of times the for
  loop has been ran. Because it is in a while loop, `%` was not needed as the for loop would reset everytime
  it finishes until the window is closed. After every draw, the `frameCounter` is also incremented so that 
  the generation is increased everytime the window is redrawn. 
