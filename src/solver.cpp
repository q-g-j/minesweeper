#include <algorithm>
#include <vector>

#include "../include/field.hpp"
#include "../include/solver.hpp"
#include "../include/symbols.hpp"

void Solver::autoPlaceFlagsRecursive(Field& field)
{
    Common common;
    Symbols symbols;

    std::vector<int> poolCoveredVector;

    // for each cell in field2DVector:
    for (int i = 1; i <= field.getCols(); ++i)
    {
        for (int j = 1; j <= field.getRows(); ++j)
        {
            Common::CoordsStruct tempCoords;
            tempCoords.col = i;
            tempCoords.row = j;

            // if it's a number:
            if (field.isNumber(tempCoords))
            {
                // create 2 vectors: 
                // one for covered neighbors, 
                // one for neighbor flags
                std::vector<Common::CoordsStruct> coveredVector;
                std::vector<Common::CoordsStruct> flagsVector;
                coveredVector = field.findNeighbors(field.field2DVector, tempCoords, symbols.symbolCovered);
                flagsVector = field.findNeighbors(field.field2DVector, tempCoords, symbols.symbolFlag);

                // if the number of covered neighbos plus the number of flag neighbors matches the current cells number,
                // add the covered cells to poolCoveredVector:
                if ((flagsVector.size() + coveredVector.size()) == common.stringToInt(field.getCoordsContent(tempCoords)))
                {
                    for (size_t k = 0; k < coveredVector.size(); ++k)
                    {
                        {
                            if (std::find(poolCoveredVector.begin(), poolCoveredVector.end(), common.coordsToInt(coveredVector.at(0), field.getCols())) == poolCoveredVector.end())
                            {
                                poolCoveredVector.push_back(common.coordsToInt(coveredVector.at(k), field.getCols()));
                            }
                        }
                    }
                }
            }
        }
    }

    // set a flag, if it makes sense:
    if (poolCoveredVector.size() != 0)
    {
        for (size_t i = 0; i < poolCoveredVector.size(); ++i)
        {
            Common::CoordsStruct tempCoords;
            tempCoords = common.intToCoords(poolCoveredVector.at(i), field.getCols());
            field.field2DVector[tempCoords.col][tempCoords.row] = symbols.symbolFlag;
            field.setCoveredLeft(field.getCoveredLeft() - 1);
            field.setMinesLeft(field.getMinesLeft() - 1);
            field.setFlagsCount(field.getFlagsCount() + 1);
            field.printCoords(tempCoords, false);
        }
    }

    // For each number on the game field, create a vector holding the neighbor flags and
    // a vector of covered neighbors.
    // Then, if the number of found flags matches the number inside the current cell and
    // if there are any covered neighbors, run field.flagAutoUncover on the current cell:
    bool ranFlagAutoUncover = false;
    for (int col = 1; col <= field.getCols(); ++col)
    {
        for (int row = 1; row <= field.getRows(); ++row)
        {
            Common::CoordsStruct tempNumberCoords;
            tempNumberCoords.col = col;
            tempNumberCoords.row = row;
            if (field.isNumber(tempNumberCoords))
            {
                std::vector<Common::CoordsStruct> neighborsFlagsVector;
                std::vector<Common::CoordsStruct> neighborsCoveredVector;
                neighborsFlagsVector = field.findNeighbors(field.field2DVector, tempNumberCoords, symbols.symbolFlag);
                neighborsCoveredVector = field.findNeighbors(field.field2DVector, tempNumberCoords, symbols.symbolCovered);

                if (neighborsFlagsVector.size() == common.stringToInt(field.field2DVector[col][row]) && neighborsCoveredVector.size() != 0)
                {
                    Common::UserInputReturnStruct tempUserInputReturnStruct;
                    Common::PlaceUserInputReturnStruct tempPlaceUserInputReturnStruct;
                    tempUserInputReturnStruct.Coords = tempNumberCoords;
                    field.flagAutoUncover(tempUserInputReturnStruct, tempPlaceUserInputReturnStruct);
                    ranFlagAutoUncover = true;
                }
            }
        }
    }

    // repeat, if the following conditions are met:
    if (poolCoveredVector.size() != 0 || ranFlagAutoUncover)
    {
        autoPlaceFlagsRecursive(field);
    }
}

