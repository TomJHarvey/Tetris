/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#include "MainComponent.h"
#include "../JuceLibraryCode/JuceHeader.h"



//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (16 * oneSquare, 21 * oneSquare);                             // The grid consists of sqaures 38 X 38
    
    holdLabel.setText("Hold", sendNotification);    // drawn all lables and text
    holdLabel.setColour(00, Colours::red);
    addAndMakeVisible(holdLabel);
    nextLabel.setText("Next", sendNotification);
    addAndMakeVisible(nextLabel);
    levelLabel.setText("Level", sendNotification);
    addAndMakeVisible(levelLabel);
    goalLabel.setText("Goal", sendNotification);
    addAndMakeVisible(goalLabel);
    scoreLabel.setText("Score", sendNotification);
    addAndMakeVisible(scoreLabel);
    level = std::to_string(levelCounter + 1);
    levelNumber.setText(level, sendNotification);
    addAndMakeVisible(levelNumber);
    scoreNumber.setText("0", sendNotification);
    addAndMakeVisible(scoreNumber);
    goal = std::to_string(levelGoals[levelCounter]);
    goalNumber.setText(goal, sendNotification);
    addAndMakeVisible(goalNumber);
    addAndMakeVisible(tetrimino);               // add the objects
    addAndMakeVisible(drawTetrimino);
    addAndMakeVisible(nextTetrimino);
    addAndMakeVisible(holdTetrimino);
    threadCounter.startCounter();               // Starts the counter in the future select the level to chnage the speed
    threadCounter.setSpeed(200);                // Sets the speed for the first level
    threadCounter.setListener(this);
    setWantsKeyboardFocus(true);                // Enable use of the keyboard
    addKeyListener(this);
    
    currentXpositions.resize(4);                // resize vectors
    currentYpositions.resize(4);
    gridValues.resize(21);                      // Make it hold 21 different vectors, which is one for each line
    
    for (int i = 0; i < gridValues.size(); i ++)
    {
        gridValues[i].resize(10);               // Make each of the 21 gridValues vectors have 10 items which makes each line 10 across.
    }
    
    for (int i = 0; i < gridValues.size(); i ++)
    {
        for (int j = 0; j < gridValues[i].size(); j ++)
        {
            gridValues[i][j] = -1;              // Sets each piece of the grid equal to -1 so it has no 'tetrimino type'
        }
    }
}

MainContentComponent::~MainContentComponent()
{
    
    
}

void MainContentComponent::counterChanged (int counterValue_)
{
    if (canPieceFallFurther == false) // if the piece can't fall further
    {
        pieceCanBeMoved = false;
        drawTetriminoOnGrid();  // draw the tetrimino

        for (int i = 0; i < 4; i ++)
        {
            if (currentYpositions[i] == 0)
            {
                resetSequence(0);
            }
        }
        
    }
    
    if (isPieceFalling == false)    // if the piece has fallen and been drawn
    {
        createNewPiece();    // create a new piece
    }
    
    else if (isPieceFalling == true) // if there is room for it to fall
    {
        if (tetrimino.getY() + tetrimino.getHeight() <= 20 * oneSquare) // If the piece isn't below the grid
        {
            moveTetrimino(oneSquare, 0);   // Move the piece down
        }
        else
        {
            canPieceFallFurther = false; // set the piece to unable to fall further
        }
    }
    
    if (pieceHasLanded == true){
        isPieceFalling = false;
    }
    
    testCounter ++;
}

void MainContentComponent::createNewPiece()
{
    isPieceFalling = true;                                          // Set the piece to be falling
    pieceHasLanded = false;                                         // Reset the piece to not have landed
    numberOfSquaresFallen = 0;                                      // How many squares the piece has fallen is reset each time its a new piece
    rotationCounter = 0;                                            // Reset the rotation counter
    currentTetriminoXposition = oneSquare * 8;                                // Reset the piece to the middle
    pieceCanBeMoved = true;
    
    if (holdPiece != true)                                          // If the piece is not retrieved from the hold
    {
        randomTetrimino();
    }
    else
    {
        if (firstTimeHold == true)                                  // If its the first time it is held, it creates a random piece
        {
            firstTimeHold = false;
            holdPiece = false;
            holdTetriminoType = tetriminoType;
            drawHoldPiece();
            randomTetrimino();
        }
        
        else                                                        // If it has been held before, it swaps the current piece with the last hold piece.
        {
            int copy = tetriminoType;
            tetriminoType = holdTetriminoType;
            holdTetriminoType = copy;
            drawHoldPiece();
            holdPiece = false;
        }
    }
    
    //tetriminoType = 0;                                            // Set type for testing purposes
    
    // Checks to see if the component has the correct default width and height
    
    if (tetriminoWidthAndHeight[tetriminoType][0] == twoSquares || tetriminoWidthAndHeight[tetriminoType][0] == oneSquare)        // If they are incorrect they are swapped back to the default width and height
    {
        int sizeCopy = tetriminoWidthAndHeight[tetriminoType][0];
        tetriminoWidthAndHeight[tetriminoType][0] = tetriminoWidthAndHeight[tetriminoType][1];
        tetriminoWidthAndHeight[tetriminoType][1] = sizeCopy;
    }
    
    tetrimino.setBounds(currentTetriminoXposition, 0, tetriminoWidthAndHeight[tetriminoType][0], tetriminoWidthAndHeight[tetriminoType][1]);  // The tetrimino piece's position is set to the default
    tetrimino.setType(tetriminoType, 1);                                                      // The type is selected and in tetriminos paint function the piece is drawn.
    currentXpositions = tetrimino.returnXorYPositions(tetrimino.getX(), tetrimino.getWidth(), 0);
    currentYpositions = tetrimino.returnXorYPositions(tetrimino.getY(), tetrimino.getWidth(), 1);
}

void MainContentComponent::randomTetrimino()
{
    // When selecting a random piece it has twelve attempts but can can only select the same piece twice, seeing as there are 14 tetriminos, this means that
    
    int rand = 0;
    
    if (firstTimeRandom == true)
    {
        for (int i = 0; i < 6; i ++)    // resizes the vector to 6 values and adds the first 6 to the array.
        {
            rand = random.nextInt(7);
            
            if (tetriiminoRandomTypes[rand] == 2)           // if this tetrimino has aleady been selected twice, it selects another
            {
                while (tetriiminoRandomTypes[rand] == 2)
                {
                    rand = random.nextInt(7);
                }
            }
            tetriminoRandomCounter ++;
            tetriiminoRandomTypes[rand] ++;                 // increase the counter for the selected piece
            
            randomPieces.push_back(rand);                   // add each piece to the vector
            
        }
        
        tetriminoType = randomPieces[0];
        firstTimeRandom = false;
    }
    else
    {
        rand = random.nextInt(7);
        
        if (tetriiminoRandomTypes[rand] == 2)           // if this tetrimino has aleady been selected twice, it selects another
        {
            while (tetriiminoRandomTypes[rand] == 2)
            {
                rand = random.nextInt(7);
            }
        }
        
        tetriiminoRandomTypes[rand] ++;
        tetriminoRandomCounter ++;
        randomPieces.erase(randomPieces.begin());   // remove the first item in the array
        randomPieces.push_back(rand);               // add the latest item to the end
        tetriminoType = randomPieces[0];
        
        if (tetriminoRandomCounter == 12)   // the counter is reset
        {
            tetriminoRandomCounter = 0;
            
            for (int i = 0; i < 12; i ++){                      // the twelve values are reset for next time
                tetriiminoRandomTypes[i] = 0;
            }
        }
        
    }
    
    drawNextTetriminos();
}

void MainContentComponent::moveTetrimino(int downIncrement, int leftOrRightIncrement)
{
    int yValue = 0;
    int xValue = 0;
    bool tetriminoCanMove = true;

    
    for (int i = 0; i < 4; i ++)
    {
        xValue = ((currentXpositions[i] / oneSquare) - 3) + (leftOrRightIncrement/oneSquare);     // this checks to see if each sqaure of the tetrimino will hit another piece if moved left or right
        yValue = (currentYpositions[i] / oneSquare) + (downIncrement/oneSquare);
        
        if (yValue == 21) {
            tetriminoCanMove = false;                       // this means that the value has exceeded the grid so it can't move any further
            break;
        }
        
        if (gridValues[yValue][xValue] != -1){              // if there is a sqaure in the same position the whole piece can't move
            tetriminoCanMove = false;
        }
    }

    //std::cout << testCounter << "Y before = " << tetrimino.getY() << std::endl;

    if (tetriminoCanMove == true)
    {
        currentTetriminoXposition += leftOrRightIncrement;  // move the piece left or right
        numberOfSquaresFallen += downIncrement;             // increase number of sqaures fallen.
        canPieceFallFurther = true;                         // update the piece to be falling because the piece may not have been able to fall before it was moved (left or right)
        tetrimino.setBounds(currentTetriminoXposition, numberOfSquaresFallen, tetriminoWidthAndHeight[tetriminoType][0], tetriminoWidthAndHeight[tetriminoType][1]);// Apply the updated x or y position
    }
    
    else
    {
        if(leftOrRightIncrement == 0)
        {
            canPieceFallFurther = false;
        }
    }

    currentXpositions = tetrimino.returnXorYPositions(tetrimino.getX(), tetrimino.getWidth(), 0);
    currentYpositions = tetrimino.returnXorYPositions(tetrimino.getY(), tetrimino.getWidth(), 1);
    //std::cout << testCounter << "Y After = " << tetrimino.getY() << std::endl;
}

void MainContentComponent::drawTetriminoOnGrid()
{
   int numberOfLinesCleared = drawTetrimino.updateDimensions(currentXpositions, currentYpositions, tetriminoType); // Draws the new sqaures that have just been added

    if (numberOfLinesCleared == 0)                      // If no lines were cleared
    {
        int xValue = 0;
        int yValue = 0;
        
        for (int i = 0 ; i < 4 ; i ++)
        {
            xValue = ((currentXpositions[i] / oneSquare) - 3);     // The x position is scaled into a number from 0 - 9
            yValue = (currentYpositions[i] / oneSquare);           // The y position is scaled into a number between 0 - 21
            gridValues[yValue][xValue] = tetriminoType;     // The grid values for these positions are now updated so a block is in this position. The type determines the colour.
        }
    }
    
    else
    {
        drawTetrimino.updateGrid(gridValues);               // If a 1 or more lines have been cleared the new positions in the grid are updated and moved in the vector.
        increaseScore(numberOfLinesCleared);
    }
    
    isPieceFalling = false;                                 // A new piece can now be created once it has been drawn
    canPieceFallFurther = true;
}


bool MainContentComponent::keyPressed(const KeyPress &key, Component* originatingComponent )
{
    //DBG(key.getKeyCode());
    
    if (pieceCanBeMoved == true)
    {
        pieceCanBeMoved = false;
        if (key.getKeyCode() == 63234)                              // Move tetrimino to the left
        {
            if (currentTetriminoXposition >= 4 * oneSquare){
                moveTetrimino(0, -oneSquare);
            }
        }
        
        else if (key.getKeyCode() == 63235)                         // Move the tetrimino to the right
        {
            if (currentTetriminoXposition + tetriminoWidthAndHeight[tetriminoType][0] <= oneSquare * 12){
                moveTetrimino(0, oneSquare);
            }
        }
        
        else if (key.getKeyCode() == 63233)                         // Move tetrimino down
        {
            if (tetrimino.getY() + tetrimino.getHeight() <= oneSquare * 20){   // If the piece is not outside of the grid
                moveTetrimino(oneSquare, 0);
            }
            
            else
                canPieceFallFurther = false;
        }
        
        else if (key.getKeyCode() == 32)                            // Hard drop
        {
            while (canPieceFallFurther == true){
                moveTetrimino(oneSquare, 0);
            }
        }
        
        else if (key.getKeyCode() == 63232)
        {
            if (tetriminoType != 1) {
                rotateTetrimino();
            }
        }
        
        else if (key.getKeyCode() == 96)
        {
            isPieceFalling = false;
            holdPiece = true;
        }
        
        pieceCanBeMoved = true;
        
        // after every key press update to see if it can fall or not
    }
    else
    {
        DBG("TASK NOT DONE");
    }
}


void MainContentComponent::rotateTetrimino()
{
    int xOffset = 0;
    int yOffset = 0;
    rotationCounter ++;
    
    if (rotationCounter == 4)
    {
        rotationCounter = 0;
    }
    
    else if (rotationCounter == 1)  // When a piece rotates it has a different x position for both of the horizontal instances of the rotation, these if loops set this.
    {
        xOffset = oneSquare;
    }
    
    if (rotationCounter == 1 || rotationCounter == 3)
    {
        yOffset = -oneSquare;
    }
    
    tetrimino.getGridInformation(gridValues, tetrimino.getX() + xOffset, tetrimino.getY() + yOffset);
    
    if (tetrimino.rotateShape(tetriminoType) == true)
    {
        int sizeCopy0 = tetriminoWidthAndHeight[tetriminoType][0];                        // this swaps the width and the height values around
        int sizeCopy1 = tetriminoWidthAndHeight[tetriminoType][1];
        tetriminoWidthAndHeight[tetriminoType][0] = sizeCopy1;
        tetriminoWidthAndHeight[tetriminoType][1] = sizeCopy0;
        currentTetriminoXposition += xOffset;
        numberOfSquaresFallen += yOffset;
        tetrimino.setBounds(currentTetriminoXposition, numberOfSquaresFallen, tetriminoWidthAndHeight[tetriminoType][0], tetriminoWidthAndHeight[tetriminoType][1]);
        currentXpositions = tetrimino.returnXorYPositions(tetrimino.getX(), tetrimino.getWidth(), 0);
        currentYpositions = tetrimino.returnXorYPositions(tetrimino.getY(), tetrimino.getWidth(), 1);
    }
    
    canPieceFallFurther = true;
    
    // comment
}

void MainContentComponent::drawNextTetriminos()
{
    // make the O piece more centered and the I more centered vertically
    nextTetrimino.setType(randomPieces[1], 2);
    nextTetrimino.setBounds(oneSquare * 13.8, oneSquare * 1.5, oneSquare * 4, oneSquare * 4);
}

void MainContentComponent::drawHoldPiece()
{
    holdTetrimino.setType(holdTetriminoType, 2);
    holdTetrimino.setBounds(oneSquare * 0.8, oneSquare * 1.5, oneSquare * 4, oneSquare * 4);
}

void MainContentComponent::increaseScore(int numberOfLines)
{
    currentScore +=numberOfLines;
    score = std::to_string(currentScore);
    scoreNumber.setText(score, sendNotification);
    
    if (levelGoals[levelCounter] == currentScore)
    {
        levelCounter ++;
        currentScore = 0;
        score = std::to_string(currentScore);
        scoreNumber.setText(score, sendNotification);
        threadCounter.setSpeed(levelSpeeds[levelCounter]);
        goal = std::to_string(levelGoals[levelCounter]);
        goalNumber.setText(goal, sendNotification);
        level = std::to_string(levelCounter + 1);
        levelNumber.setText(level, sendNotification);
        
    }
    
}

void MainContentComponent::resetSequence(int buttonType_)
{
    // this is called when the counter needs to start again, so when the game is over, or if its paused it will start from where it left off
    // change the arugments for both counter ones
    
    drawTetrimino.resetGrid();
    
    for (int i = 0; i < gridValues.size(); i ++)
    {
        for (int j = 0; j < gridValues[i].size(); j ++)
        {
            gridValues[i][j] = -1;              // Sets each piece of the grid equal to -1 so it has no 'tetrimino type'
        }
    }
    
    firstTimeHold = true;
    
    levelCounter = 0;
    currentScore = 0;
    score = std::to_string(currentScore);
    scoreNumber.setText(score, sendNotification);
    level = std::to_string(levelCounter);
    levelNumber.setText(level, sendNotification);
    goal = std::to_string(levelGoals[levelCounter]);
    goalNumber.setText(goal, sendNotification);
    threadCounter.setSpeed(levelSpeeds[levelCounter]);
    
    
}


void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::black);
    g.setColour(Colours::grey);
    
    // The grid
    for (int count = 0; count < 16; count ++)
    {
        g.drawLine(0 + (count * oneSquare), 0 , 0 + (count * oneSquare), getHeight());
    }
    
    for (int count = 0; count < 22; count ++)
    {
        g.drawLine(0, 0 + (count * oneSquare) ,getWidth(),  0 + (count * oneSquare));
    }
    
    // Left side bar
    g.setColour (Colours::purple);
    g.drawRect (0, 0, threeSquares, getHeight());
    g.fillRect (0, 0, threeSquares, getHeight());
    
    // Right side bar
    g.setColour (Colours::purple);
    g.drawRect (getWidth() - threeSquares, 0, threeSquares, getHeight());
    g.fillRect (getWidth() - threeSquares, 0, threeSquares, getHeight());
    
    
    // Thin top bar
    g.setColour(Colours::slategrey);
    g.drawRect (threeSquares, 0, oneSquare * 10, oneSquare);
    g.fillRect (threeSquares, 0, oneSquare * 10, oneSquare);
    
    // Hold
    g.setColour(Colours::black);
    g.drawRect(oneSquare /2, oneSquare, twoSquares, twoSquares);
    g.fillRect(oneSquare /2, oneSquare, twoSquares, twoSquares);
    
    // Next tetrimino
    g.drawRect(oneSquare * 13.5, oneSquare, twoSquares, twoSquares);
    g.fillRect(oneSquare * 13.5, oneSquare, twoSquares, twoSquares);

}

void MainContentComponent::resized()
{
    // These sizes were origanally fixed, however to make it so it can be resized each of the values are based off the size of the main square
    
    holdLabel.setBounds(oneSquare/2, oneSquare * 0.5, twoSquares, oneSquare/2);
    nextLabel.setBounds(oneSquare * 13.5, oneSquare * 0.5, twoSquares, oneSquare/2);
    
    levelLabel.setBounds(oneSquare/2, oneSquare * 14.5, twoSquares, 10);
    levelNumber.setBounds(oneSquare/2, oneSquare * 15, oneSquare * 2.5, oneSquare * 1.5);
    
    goalLabel.setBounds(oneSquare/2, oneSquare * 16.5, twoSquares, 10);
    goalNumber.setBounds(oneSquare/2, oneSquare * 16.9, oneSquare * 2.5, oneSquare * 1.5);
    
    scoreLabel.setBounds(oneSquare * 13.5, oneSquare * 14.5, twoSquares, 10);
    scoreNumber.setBounds(oneSquare * 13.5, oneSquare * 15, oneSquare * 2.5, oneSquare * 1.5);
    
    
    drawTetrimino.setBounds(0, 0, getWidth(), getHeight());
    
}
