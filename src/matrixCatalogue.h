//
// Created by marsar on 24/8/22.
//

#include "matrix.h"

/**
 * @brief The MatrixCatalogue acts like an index of matrices existing in the
 * system. Everytime a matrix is added(removed) to(from) the system, it needs to
 * be added(removed) to(from) the matrixCatalogue.
 * This is supposed to be based on tableCatalouge.h and supposed to work like that, but for matrices.
 */

#ifndef SIMPLERA_MATRIXCATALOUGE_H
#define SIMPLERA_MATRIXCATALOUGE_H


class MatrixCatalogue {

    unordered_map<string, Matrix*> matrices;

public:
    MatrixCatalogue() {}
    void insertMatrix(Matrix* matrix);
    void deleteMatrix(string matrixName);
    Matrix* getMatrix(string matrixName);
    bool isMatrix(string matrixName);
//    bool isColumnFromMatrix(string columnName, string tableName);
    void print();
    ~MatrixCatalogue();
};


#endif //SIMPLERA_MATRIXCATALOUGE_H
