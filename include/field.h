#pragma once

// system headers:
#include <random>

class Field
{
private:
    // private variables:
    int cols;
    int rows;
    int fieldOffsetX;
    int fieldOffsetY;
    int fieldCellWidth;
    int minesTotal;
    int minesLeft;
    int coveredLeft;
    int flagsCount;
    std::string difficultyString;

    // random number generator:
    std::random_device rng;
    std::mt19937 urng;

    // return variables for class methods:
    Common::PlaceUserInputReturnStruct placeUserInputReturn;

    // private methods:
    std::vector<std::vector<stringconv>> create2DVector(std::string const&);
    void fillMines(Common::CoordsStruct const&);
    void gameWon();
    void gameLost();

public:
    Field(Common::GameModeReturnStruct&);
    ~Field();

    std::vector<std::vector<stringconv>> field2DVector;
    std::vector<std::vector<stringconv>> mines2DVector;
    std::vector<std::vector<stringconv>> cursor2DVector;

    // getter methods:
    const int &getCols() const;
    const int &getRows() const;
    const int &getOffsetX() const;
    const int &getOffsetY() const;
    const int &getCoveredLeft() const;
    const int &getMinesTotal() const;
    const int &getMinesLeft() const;
    const int &getFlagsCount() const;
    const int &getCellWidth() const;
    const std::string &getDifficultyString() const;
    const stringconv &getCoordsContent(Common::CoordsStruct const&) const;

    // setter methods to increment / decrement using operator overloading
    // (just for learning purposes):
    struct setFlagsCount
    {
        private:
            Field &field_;
        public:
            setFlagsCount(Field& field) : field_(field) { }
            void operator--();
            void operator++();
    };
    struct setMinesLeft
    {
        private:
            Field& field_;
        public:
            setMinesLeft(Field& field) : field_(field) { }
            void operator--();
            void operator++();
    };
    struct setCoveredLeft
    {
        private:
            Field& field_;
        public:
            setCoveredLeft(Field& field) : field_(field) { }
            void operator--();
            void operator++();
    };

    // public methods:
    bool isFlag(Common::CoordsStruct const&);
    bool isNumber(Common::CoordsStruct const&);
    void drawField();
    void printAll();
    void printCoords(Common::CoordsStruct const&, bool);
    std::vector<Common::CoordsStruct> findNeighbors(std::vector<std::vector<stringconv>> const&, Common::CoordsStruct const&, stringconv const&);
    void autoRevealRecursive(Common::CoordsStruct const&, std::vector<unsigned int>&);
    void flagAutoReveal(Common::CoordsStruct const&, Common::PlaceUserInputReturnStruct&, bool);
    const Common::PlaceUserInputReturnStruct &placeUserInput(Common::UserInputReturnStruct&, int&);
};
