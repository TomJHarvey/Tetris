/*
 ==============================================================================
 
 DrawTetriminos.cpp
 Created: 7 Nov 2017 2:38:08pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "DrawTetriminos.h"
#include "../JuceLibraryCode/JuceHeader.h"


DrawTetrimino::DrawTetrimino()
{
    gridValues.resize(21);                      // Make it hold 21 different vectors, which is one for each line
    
    for (int i = 0; i < gridValues.size(); i ++)
    {
        gridValues[i].resize(10);               // Make each of the vectors have 10 items which makes each line 10 across.
    }
    
    for (int i = 0; i < gridValues.size(); i ++)
    {
        for (int j = 0; j < gridValues[i].size(); j ++)
        {
            gridValues[i][j] = -1;           // Sets each piece of the grid equal to 0
        }
    }
    
    

}
DrawTetrimino::~DrawTetrimino()
{
    
}

void DrawTetrimino::updateGrid(vector<vector <int>> &gridValuesReference)
{
    for (int i = 0; i < 21; i ++)
    {
        for (int j = 0; j < 10; j ++)
        {
            gridValuesReference[i][j] = gridValues[i][j];
        }
    }
}

void DrawTetrimino::resetGrid()
{
    for (int i = 0; i < gridValues.size(); i ++)
    {
        for (int j = 0; j < gridValues[i].size(); j ++)
        {
            gridValues[i][j] = -1;           // Sets each piece of the grid equal to 0
        }
    }
    
    
    for (int i = 0; i < 20; i ++)
    {
        numberOfsquaresPerLine[i] = 0;
        for (int j = 0; j < 10; j ++)
        {
            valueOfSquaresPerLine[i][j] = 0;
        }
    }


}

int DrawTetrimino::updateDimensions(std::vector <int> xDimensions,std::vector<int> yDimensions, int type)
{
    
    bool linesHaveBeenCleared = false;
    numberOfLinesCleared = 0;
    
    for (int i = 0; i < 4; i ++)
    {
        int xValue = (xDimensions[i] / oneSquare) - 3;
        int yValue = yDimensions[i]/oneSquare;
        
        gridValues[yValue][xValue] = type;
        numberOfsquaresPerLine[yValue] ++;
        
    }
    
    for (int i = 0; i < 21; i ++)
    {
        if (numberOfsquaresPerLine[i] == 10)
        {
            numberOfsquaresPerLine[i] = 0;
            for (int j = 0; j < 10; j ++)
            {
                gridValues[i][j] = -1;
            }
            
            for (int k = i; k > 0; k --)
            {
                numberOfsquaresPerLine[k] = numberOfsquaresPerLine[k-1];
                
                for (int l = 0; l < 10; l ++)
                {
                    gridValues[k][l] = gridValues[k - 1][l];
                }
            }
            repaint();
            linesHaveBeenCleared = true;
            numberOfLinesCleared ++;
        }
    }
    
    repaint();
    
    return numberOfLinesCleared;
    
}

void DrawTetrimino::paint(Graphics& g)
{
    for (int i = 0; i < 21; i ++)
        {
            for (int j = 0; j < 10; j ++)
            {
                if (gridValues[i][j] != -1)
                {
                    g.setColour(tetriminoColorus[gridValues[i][j]]);
                    g.drawRect((j + 3) * oneSquare, i*oneSquare, oneSquare, oneSquare);
                    g.fillRect((j + 3) * oneSquare, i*oneSquare, oneSquare, oneSquare);
                }
            }
        }
}


