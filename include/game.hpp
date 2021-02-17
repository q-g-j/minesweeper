#pragma once

// system headers:
#include <memory>

// project headers:
#include <common.hpp>
#include <debug.hpp>

class Colors;
class Common;
class Field;
class Input;
class Print;

class Game
{
private:
    // declare class objects as unique pointers:
    std::unique_ptr<Colors> colors;
    std::unique_ptr<Common> common;
    std::unique_ptr<Input> input;
    std::unique_ptr<Print> print;

    std::unique_ptr<Common::CoordsStruct> Dimensions;
    std::unique_ptr<Common::GameModeReturnStruct> GameModeReturn;
    std::unique_ptr<Common::UserInputReturnStruct> UserInput;
    std::unique_ptr<Common::PlaceUserInputReturnStruct> PlaceUserInputReturn;

    // define the 3 main game modes:
    const int smallCols       = 9;
    const int smallRows       = 9;
    const int smallMines      = 10;

    const int mediumCols      = 16;
    const int mediumRows      = 16;
    const int mediumMines     = 40;

    const int largeCols       = 30;
    const int largeRows       = 16;
    const int largeMines      = 99;

    // set X/Y position of the field
    const int fieldOffsetX    = 5;
    const int fieldOffsetY    = 6;

    // set width of each cell:
    const int fieldCellWidth  = 3;

    int difficulty;
    std::string difficultyString;
public:
    Game();
    ~Game();

    Common::GameModeReturnStruct choseGamemode();
    void startGame();
};