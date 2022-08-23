//
// Created by marsar on 24/8/22.
//

#include "matrixCatalogue.h"

bool MatrixCatalogue::isMatrix(string matrixName)
{
    logger.log("MatrixCatalogue::isMatrix");
    if (this->matrices.count(matrixName))
        return true;
    return false;
}
