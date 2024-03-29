#pragma once

class Input
{    
private:
    enum class Direction : int
    {
        UP, DOWN, LEFT, RIGHT
    };

    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        const char KEY_UP = 72;
        const char KEY_DOWN = 80;
        const char KEY_RIGHT = 77;
        const char KEY_LEFT = 75;
        const char KEY_ENTER = '\r';
        const char KEY_SPACE = ' ';
    #else
        const char KEY_UP = 'A';
        const char KEY_DOWN = 'B';
        const char KEY_RIGHT = 'C';
        const char KEY_LEFT = 'D';
        const char KEY_ENTER = '\n';
        const char KEY_SPACE = ' ';
    #endif

    bool toggleEdgeJump;
    bool* toogleEdgeJumpP;

    // return variables for class methods:
    int getInputDifficultyReturn;
    int getInputCustomCellWidthReturn;
    Common::CoordsStruct getInputCustomDimensionsReturn;
    int getInputCustomMinesCountReturn;
    Common::UserInputReturnStruct getInputGameplayReturn;
    
    // private methods:
    void moveCursor(Field&, Common::CoordsStruct&, Direction&, bool*);
    void toggleHelp(Field&, Common::CoordsStruct const&);
    
public:
    Input();
    ~Input();

    // public methods:
    #if !defined(_WIN32) && !defined(WIN32) && !defined(_WIN64) && !defined(WIN64)
        static void enableNonCanonicalMode();
        static void disableNonCanonicalMode();
    #endif

    static void showBlinkingCursor(bool);
    const int &getInputDifficulty();
    const int &getInputCustomCellWidth();
    const Common::CoordsStruct &getInputCustomDimensions(int const&);
    const int &getInputCustomMinesCount(int const&);
    const Common::UserInputReturnStruct &getInputGameplay(Field&, bool);
    void getInputEnterKey(std::string const&);
};


