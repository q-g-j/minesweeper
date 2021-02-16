#ifdef _DEBUG
    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        #define _CRTDBG_MAP_ALLOC
        #include <stdlib.h>
        #include <crtdbg.h>
        #define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
        // Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
        // allocations to be of _CLIENT_BLOCK type
    #endif
#endif

// system headers:
#include <algorithm>
#include <vector>
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    #include <windows.h>
#else
    #include <unistd.h>
#endif

// project headers:
#include <field.hpp>
#include <solver.hpp>
#include <symbols.hpp>

Solver::Solver()
:
    common(std::make_unique<Common>()),
    symbols(std::make_unique<Symbols>())
{
}

Solver::~Solver()
{
}

void Solver::autoSolve(Field& field, bool doPlaceFlags, bool doFlagAutoUncover, bool doSolve)
{
    std::vector<int> poolCoveredVector;

    if (doPlaceFlags)
    {
        // for each cell in field2DVector:
        for (int i = 1; i <= field.getRows(); ++i)
        {
            for (int j = 1; j <= field.getCols(); ++j)
            {
                Common::CoordsStruct tempCoords;
                tempCoords.row = i;
                tempCoords.col = j;

                // if it's a number:
                if (field.isNumber(tempCoords))
                {
                    // create 2 vectors: 
                    // one for covered neighbors, 
                    // one for neighbor flags
                    std::vector<Common::CoordsStruct> coveredVector;
                    coveredVector = field.findNeighbors(field.field2DVector, tempCoords, symbols->symbolCovered, false);
                    std::vector<Common::CoordsStruct> flagsVector;
                    flagsVector = field.findNeighbors(field.field2DVector, tempCoords, symbols->symbolFlag, false);

                    // if the number of covered neighbors plus the number of neighbor flags matches the current cells number,
                    // add the covered cells to poolCoveredVector:
                    if ((flagsVector.size() + coveredVector.size()) == static_cast<size_t>(common->stringToInt(field.getCoordsContent(tempCoords))))
                    {
                        for (size_t k = 0; k < coveredVector.size(); ++k)
                        {
                            if (std::find(poolCoveredVector.begin(), poolCoveredVector.end(), common->coordsToInt(coveredVector.at(k), field.getCols())) == poolCoveredVector.end())
                            {
                                poolCoveredVector.push_back(common->coordsToInt(coveredVector.at(k), field.getCols()));
                            }
                        }
                    }
                }
            }
        }

        // place a flag at the coords of each element of poolCoveredVector:
        if (poolCoveredVector.size() != 0)
        {
            for (size_t i = 0; i < poolCoveredVector.size(); ++i)
            {
                Common::CoordsStruct tempCoords;
                Field::setCoveredLeft coveredLeft(field);
                Field::setMinesLeft minesLeft(field);
                Field::setFlagsCount flagsCount(field);
                tempCoords = common->intToCoords(poolCoveredVector.at(i), field.getCols());
                field.field2DVector[tempCoords.col][tempCoords.row] = symbols->symbolFlag;
                --coveredLeft;
                --minesLeft;
                ++flagsCount;
                #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
                    Sleep(100);
                #else
                    usleep(100*1000);
                #endif
                field.printCoords(tempCoords, false);
            }
        }
    }

    // run field.flagAutoUncover() on all cells:
    if (doFlagAutoUncover)
    {
        for (int i = 1; i <= field.getRows(); ++i)
        {
            for (int j = 1; j <= field.getCols(); ++j)
            {
                Common::CoordsStruct tempCoords;
                Common::PlaceUserInputReturnStruct tempPlaceUserInputStruct;
                tempCoords.row = i;
                tempCoords.col = j;
                field.flagAutoUncover(tempCoords, tempPlaceUserInputStruct);
            }
        }
    }

    // re-run the whole function, if there are cells in poolCoveredVector or
    // if it's the first run of this function when "s" or "S" (= "solve") was hit:
    if (poolCoveredVector.size() != 0 || doSolve == true)
    {
        autoSolve(field, doPlaceFlags, doFlagAutoUncover, false);
    }
}