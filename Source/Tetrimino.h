/*
 ==============================================================================
 
 Tetrimino.h
 Created: 23 Oct 2017 1:20:09pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#ifndef TETRIMINO_H_INCLUDED
#define TETRIMINO_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
constexpr int oneSquare = 28;
constexpr int twoSquares = oneSquare * 2;
constexpr int threeSquares = oneSquare * 3;
constexpr int fourSquares = oneSquare * 4;


class Tetrimino: public Component
{
public:
    
    Tetrimino();
    ~Tetrimino();
    
    void setType(int type, int size);
    void paint (Graphics&) override;
    bool rotateShape(int type);
    void setPositionOfRotatedSqaures();
    bool checkForRotatedShapeHittingOtherSqaures();
    void addCordinatesForThreeByTwoShapes();
    void getGridInformation(std::vector<std::vector <int >> gridValues, int tetriminoXposition, int tetriminoYposition);
    std::vector <int> returnXorYPositions(int tetriminoXorYPosition, int widthOrHeight, int type);
    
private:
    
    int typeSelect = 0;                         // Selects what tetrimino is used
    int rotateCounter = 0;                      // Counts how many times the piece has been rotated
    int xPosition[4] = {0};                     // The x position of each of the 6 sqaures for all shapes apart from i and 0
    int yPosition[4] = {0};                     // The y position "...... "
    int rowSelect[8] = {0,oneSquare,oneSquare,0,oneSquare,0,0,oneSquare};   // The cordinates of the staring position for the current rotation
    int xOrYcordintates[3] = {0,oneSquare,twoSquares};         // The cordinates for the row or collum
    int xOrYdirection[4] = {1,1,-1,-1};         // The direction that the above x or y cordiates are drawn
    int xOrYstartPos[4] = {0,0,2,2};            // If it starts at the highest or lowest value for the x or y
    int squareSize = 0;
    int widthForIblock = 0;
    
    int xPositionCopy[6] = {0};
    int yPositionCopy[6] = {0};
    
    int iXdimensionsFlat[4] = {0,oneSquare,twoSquares,threeSquares};
    int iYdimensionsFlat[4] = {0,0,0,0};
    int iXdimensionsStanding[4] = {0,0,0,0};
    int iYdimensionsStanding[4] = {0,oneSquare,twoSquares,threeSquares};
    int oXdimensions[4] = {0,oneSquare,0,oneSquare};
    int oYdimensions[4] = {0,0,oneSquare,oneSquare};
    int typeOfTetriminoForLoopSize = 0;
    int normalPieceOrIhold = 4;
    
    
    std::vector<std::vector <int >> gridValuesCopy;
    int tetriminoXpositionCopy = 0;
    int tetriminoYpositionCopy = 0;
    bool firstRotation = true;
    
    
    Colour tetriminoColorus[7] =
    {
        Colours::lightskyblue,
        Colours::yellow,
        Colours::pink,
        Colours::navy,
        Colours::orange,
        Colours::green,
        Colours::red
    };
    
    
    int tetriminoSquaresChecker[7][6] =         // 1 is if a square should be present, 0 is if its a blank space
    {
        {1,1,1,1,1,1},      // I
        {0},                // O
        {1,1,1,0,1,0},      // T
        {1,0,0,1,1,1},      // J
        {0,0,1,1,1,1},      // L
        {0,1,1,1,1,0},      // S
        {1,1,0,0,1,1}       // Z
        
    };
    
};




#endif  // TETRIMINO_H_INCLUDED
