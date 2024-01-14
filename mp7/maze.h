/* Your code here! */

#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "cs225/PNG.h"
#include <iostream>
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include "stdlib.h"
#include "queue"
#include <algorithm>
using namespace cs225;
using namespace std;
class SquareMaze
{
    public:

        /**
         * default Constructor for this class
         */
        SquareMaze();

        /**
         * Makes a new SquareMaze of the given height and width.
         *
         * @param width The width of the SquareMaze (number of cells)
         * @param height The height of the SquareMaze (number of cells)
         */
        void makeMaze(int width, int height);

        /**
         * Makes a new SquareMaze of the given height and width.This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y).
         *
         * For example, after makeMaze(2,2), the possible input coordinates will be (0,0), (0,1), (1,0), and (1,1).
         * dir = 0 represents a rightward step (+1 to the x coordinate)
         * dir = 1 represents a downward step (+1 to the y coordinate)
         * dir = 2 represents a leftward step (-1 to the x coordinate)
         * dir = 3 represents an upward step (-1 to the y coordinate)
         *
         * @param x The x coordinate of the current cell
         * @param y The y coordinate of the current cell
         * @param dir The desired direction to move from the current cell
         * @return bool that whether it can travel
         */
        bool canTravel(int x, int y, int dir) const;

        /**
         * Sets whether or not the specified wall exists.
         *
         * @param x The x coordinate of the current cell
         * @param y The y coordinate of the current cell
         * @param dir 	Either 0 (right) or 1 (down), which specifies which wall to set (same as the encoding explained in canTravel).
         * @return true if setting the wall to exist, false otherwise
         */
        void setWall(int x, int y, int dir, bool exists);


        /**
         * For each square on the bottom row (maximum y coordinate), there is a distance from the origin (i.e. the top-left cell), which is defined as the length (measured as a number of steps) of the only path through the maze from the origin to that square.
         * Select the square in the bottom row with the largest distance from the origin as the destination of the maze. solveMaze() returns the winning path from the origin to the destination as a vector of integers, where each integer represents the direction of a step, using the same encoding as in canTravel().
         *
         * @return a vector of directions taken to solve the maze
         */   
        vector<int> solveMaze();
        
        /**
         * Draws the maze without the solution.
         *
         * @return a PNG of the unsolved SquareMaze
         */      
        PNG* drawMaze() const;

        /**
         * This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit.
         *
         * @return a PNG of the solved SquareMaze
         */  
        PNG* drawMazeWithSolution();
        /** struct to describe each square, with x and y coordinate **/
        struct Cell
        {
            int x_,y_;
            Cell(int a,int b) :x_(a),y_(b){}
        };
    private:
        /** strore solotion **/
        vector<int> solution_;
        /** maze's width **/
        int width_;
        /** maze's height **/
        int height_;
        /** vector for the graph, first bool mean the right wall, second bool means the down wall **/
        vector<pair<bool,bool>> graph_;
        /** vector to store the visited, value =x+y*width **/
        vector<bool> visited_;
        /** vector that store prev of eahc square in bfs traversal **/
        vector<int> prev_;
        //PNG* maze_png;
        /** coordination of final destination **/
        int destination;
};

#endif
