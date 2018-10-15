# Course: CMPS 2143 - OOP

## Purpose: Play John Conway's Game of Life

### @author Evan Jackson
### @version 1.0 10/14/18

John Conway's Game of Life is a game to emmulate life with 4 simple rules
- Any live cell with less than 2 neighbors dies by underpopulation
- Any live cell with 2 or 3 neighbors live onto the next generation
- Any live cell with more than 3 neighbors dies by overpopulation
- Any dead cell with 3 neighbors becomes alive by reproduction

This concept is perfect for object oriented programing. While the program only called for finding what it the world would look like after so many generations, the graphics library sfml was used to make it more interesting to code and debug.

The program used the concepts of structs and inheritance to create the world of cells
