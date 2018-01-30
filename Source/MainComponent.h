/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Counter.h"
#include "Tetrimino.h"
#include "DrawTetriminos.h"

//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
class MainContentComponent   : public Component, public KeyListener, public Counter::Listener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();
    void paint (Graphics&) override;
    void resized() override;
    void moveTetrimino(int downIncrement, int leftOrRightIncrement);
    void createNewPiece();
    void drawTetriminoOnGrid();
    void rotateTetrimino();
    void randomTetrimino();
    void drawNextTetriminos();
    void drawHoldPiece();
    void increaseScore(int numberOfLines);
    
    
    /** Updates the sequence based on the main thread counter position.*/
    void counterChanged (int counterValue_) override;
    void resetSequence(int buttonType_);
    bool keyPressed(const KeyPress &key, Component* originatingComponent ) override;
    
private:
    
    int lineSpace = oneSquare;
    Path horizontalLines[16];
    Path verticalLines[21];
    Label holdLabel;
    Label nextLabel;
    Label levelLabel;
    Label goalLabel;
    Label levelNumber;
    Label goalNumber;
    Label scoreLabel;
    Label scoreNumber;
    Counter threadCounter;
    Tetrimino tetrimino;
    DrawTetrimino drawTetrimino;
    Tetrimino nextTetrimino;
    Tetrimino holdTetrimino;
    
    Random random;                      // generates the random tetrimino type
    int tetriminoRandomCounter = 0;
    int tetriiminoRandomTypes[7] = {0};
    int randomTetriminos[12] = {0};
    int tetriminoCounter = 0;           // the number of the current tetrimino
    int fallingCounter = 0;             // how many sqaures the current tetrimino has fallen
    int tetriminoType = 0;
    int numberOfSquaresFallen = 0;
    int currentTetriminoXposition = 0;
    int rotationCounter = 0;            // This is used to offset the tetrimino if it on its 4th rotation.
    bool isPieceFalling = false;        // keeps track if a piece is falling
    bool pieceHasLanded = false;        // is true when a piece has landed which resets and creates a new piece.
    bool canPieceFallFurther = true;
    bool holdPiece = false;
    bool firstTimeHold = true;
    bool firstTimeRandom = true;
    bool pieceCanBeMoved = true;
    bool holdHasBeenPressed = false;
    int holdTetriminoType = 0;
    std::vector <int> randomPieces;
    std::vector <int> currentXpositions;
    std::vector <int> currentYpositions;
    vector<vector <int>> gridValues;
    
    std::string score;
    std::string level;
    std::string goal;
    
    int currentScore = 0;
    int levelCounter = 0;
    int levelGoals[4] = {4,10,6,10};
    int levelSpeeds[4] = {500,200,50,25};
    
    int testCounter = 0;
    
    int defineArray [2];
    
    int tetriminoWidthAndHeight[7][2] = {
        
        {fourSquares,oneSquare},   // i
        {twoSquares,twoSquares},    // o
        {threeSquares,twoSquares},   // t
        {threeSquares,twoSquares},   // j
        {threeSquares,twoSquares},   // l
        {threeSquares,twoSquares},   // s
        {threeSquares,twoSquares}    // z
    };
    
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
    
    
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
