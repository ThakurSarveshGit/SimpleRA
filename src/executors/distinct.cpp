#include "global.h"

/**
 * @brief 
 * SYNTAX: R <- DISTINCT relation_name
 */
bool syntacticParseDISTINCT()
{
    logger.log("syntacticParseDISTINCT");
    if (tokenizedQuery.size() != 4)
    {
        cout << "SYNTAX ERROR" << endl;
        return false;
    }
    parsedQuery.queryType = DISTINCT;
    parsedQuery.distinctResultRelationName = tokenizedQuery[0];
    parsedQuery.distinctRelationName = tokenizedQuery[3];
    return true;
}

bool semanticParseDISTINCT()
{
    logger.log("semanticParseDISTINCT");
    //The resultant table shouldn't exist and the table argument should
    if (tableCatalogue.isTable(parsedQuery.distinctResultRelationName))
    {
        cout << "SEMANTIC ERROR: Resultant relation already exists" << endl;
        return false;
    }

    if (!tableCatalogue.isTable(parsedQuery.distinctRelationName))
    {
        cout << "SEMANTIC ERROR: Relation doesn't exist" << endl;
        return false;
    }
    return true;
}

void executeDISTINCT()
{
    Table table = *tableCatalogue.getTable(parsedQuery.distinctRelationName);
    Table* resultantTable = new Table(parsedQuery.distinctResultRelationName, table.columns);
    Cursor cursor = table.getCursor();
    vector<int> row = cursor.getNext();

    // Get all the rows
    vector<vector<int>> completeTableVector;
    while (!row.empty())
    {
        completeTableVector.push_back(row);
        row = cursor.getNext();
    }

    // Remove duplicates
    vector<vector<int>> resultantVector;
    for (auto & i: completeTableVector){
        auto it = std::find (resultantVector.begin(), resultantVector.end(), i);
        if (it == resultantVector.end())
            resultantVector.push_back(i);
    }

    // Fill in the new Table
    for (auto & i : resultantVector)
        resultantTable->writeRow<int>(i);

    // Store in memory
    if(resultantTable->blockify())
        tableCatalogue.insertTable(resultantTable);
    else{
        cout<<"Empty Table"<<endl;
        resultantTable->unload();
        delete resultantTable;
    }
}