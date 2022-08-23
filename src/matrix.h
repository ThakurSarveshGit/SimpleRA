//
// Created by marsar on 24/8/22.
//

#ifndef SIMPLERA_MATRIX_H
#define SIMPLERA_MATRIX_H

#include "cursor.h"

/**
 * @brief The Matrix class holds all information related to a loaded matrix. It
 * also implements methods that interact with the parsers, executors, cursors
 * and the buffer manager. There are typically 2 ways a matrix object gets
 * created through the course of the workflow - the first is by using the LOAD MATRIX
 * command and the second is to use assignment statement(s) (CROSS_TRANSPOSE).
 *
 */
class Matrix {

public:
    string sourceFileName = "";
    string matrixName = "";

    Matrix();
    Matrix(string matrixName);
    Matrix(string matrixName, vector<string> columns);

    bool load();
};


#endif //SIMPLERA_MATRIX_H
