#include "global.h"

/**
 * @brief
 * Returns the type of data struct we are dealing with: TABLE OR MATRIX OR UNKNOWN.
 */
DataType getTypeOfQuery()
{
    if (tokenizedQuery.size() == 3 && tokenizedQuery[2] == "MATRIX"){
        return MATRIX;
    }
    else if (tokenizedQuery.size() == 2){
        return TABLE;
    }

    return UNKNOWN;
}


/**
 * @brief 
 * SYNTAX:
 * 1) LOAD relation_name
 * 2) LOAD MATRIX relation_name
 */
bool syntacticParseLOAD()
{
    logger.log("syntacticParseLOAD");
    if (tokenizedQuery.size() != 2 || tokenizedQuery.size() !=3)
    {
        cout << "SYNTAX ERROR" << endl;
        return false;
    }

    // Keep the load query generalized for Tables or Matrix (or other inputs later on).
    parsedQuery.queryType = LOAD;
    parsedQuery.dataType = getTypeOfQuery();

    if (parsedQuery.dataType == TABLE)
        parsedQuery.loadRelationName = tokenizedQuery[1];
    else if (parsedQuery.dataType == MATRIX)
        parsedQuery.loadRelationName = tokenizedQuery[2];

    return true;
}


bool semanticParseLOAD()
{
    logger.log("semanticParseLOAD");
    if (tableCatalogue.isTable(parsedQuery.loadRelationName) || matrixCatalogue.isMatrix(parsedQuery.loadRelationName))
    {
        cout << "SEMANTIC ERROR: Relation already exists" << endl;
        return false;
    }

    if (!isFileExists(parsedQuery.loadRelationName))
    {
        cout << "SEMANTIC ERROR: Data file doesn't exist" << endl;
        return false;
    }
    return true;
}

void executeLOAD()
{
    logger.log("executeLOAD");

    if (parsedQuery.dataType == TABLE)
    {
        Table *table = new Table(parsedQuery.loadRelationName);
        if (table->load())
        {
            tableCatalogue.insertTable(table);
            cout << "Loaded Table. Column Count: " << table->columnCount << " Row Count: " << table->rowCount << endl;
        }
    }
    else if (parsedQuery.dataType == MATRIX)
    {
        Matrix* matrix = new Matrix(parsedQuery.loadRelationName);
        if (matrix->load())
        {
            matrixCatalogue.insertMatrix(matrix);
            cout << "Loaded Table. Column Count: " << matrix->columnCount << " Row Count: " << matrix->rowCount << endl;
        }
    }

    return;
}