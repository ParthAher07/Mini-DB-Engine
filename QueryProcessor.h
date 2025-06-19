// #pragma once
#include <bits/stdc++.h>
#include "ErrorHandling.h"
#include "HelpCommands.h"
#include "Functions.h"
using namespace std;

class QueryProcessor
{
private:
    set<string> keywords = {
        "create","table","primary",
        "key","int","varchar",
        "date","decimal","drop","describe",
        "insert","into","values",
        "help","tables","select","from","where",
        "and","or",
    };

    ErrorHandling error_class{"SchemaFile.txt"}; // Assuming the schema file is named "Schema.txt"
    Help help_class; // Assuming HelpCommands is a class that handles help commands
    Util util; // Assuming Util is a class that provides utility functions
    
    public:

    SchemaManager schema;
    TableManager tableManage;
    QueryProcessor() : schema(), tableManage(schema) {}


    vector<string> Tokens;
    // QueryProcessor(){};
    void run(const string &query);
    void ParseIntoTokens(const string &query);
    void ToSmallerCase();
    void DisplayTokens() const;
    void executeQuery();
};

void QueryProcessor::ParseIntoTokens(const string &Query)
{
    string temp = "";

    for (int i = 0; i < Query.size(); i++)
    {
        char c = Query[i];

        if (c == '"')
        {
            i++;
            while (Query[i] != '"')
            {
                temp += Query[i];
                i++;
            }

            if (temp != "")
                Tokens.push_back(temp);
            temp = "";
        }
        else if (c == ' ' || c == '(' || c == ')' || c == ',' || c == ';' || c == '*')
        {
            if (temp != "")
                Tokens.push_back(temp);
            if (c == '*') // for handling special case in select
                Tokens.push_back("*");
            temp = "";
        }
        else if (Query[i] == '!' && Query[i + 1] == '=')
        {
            if (temp != "")
                Tokens.push_back(temp);
            temp = "";

            Tokens.push_back("!=");
            i++;
        }
        else if (c == '<' || c == '>' || c == '=') // we can add other operators if we want to
        {
            if (temp != "")
                Tokens.push_back(temp);
            temp = "";

            Tokens.push_back(string(1, c));
        }

        else
        {
            temp += c;
        }
    }
    if (temp != "")
        Tokens.push_back(temp);
}

void QueryProcessor::ToSmallerCase()
{
    for (int i = 0; i < Tokens.size(); i++)
    {
        string temp = Tokens[i];
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        if (keywords.find(temp) != keywords.end())
            Tokens[i] = temp;
    }
}

void QueryProcessor::DisplayTokens() const
{
    cout << "Tokens: ";
    for (const string &token : Tokens)
    {
        cout << token << "\n";
    }
    cout << endl;
}

void QueryProcessor::executeQuery()
{
    cout << "Executing query..." << endl;
    if (Tokens.empty())
        return;

    if (Tokens[0] == "create" && Tokens[1] == "table")
    {
        schema.CreateTable(Tokens);
    }

    else if (Tokens[0] == "drop" && Tokens[1] == "table")
    {
        schema.DropTable(Tokens);
    }

    else if (Tokens[0] == "describe")
    {
        schema.DescribeTable(Tokens);
    }

    else if (Tokens[0] == "help" && Tokens[1] == "tables")
    {
        help_class.HelpTables();
    }

    else if (Tokens[0] == "help")
    {
        help_class.HelpCommand(Tokens);
    }

    else if (Tokens[0] == "insert" && Tokens[1] == "into")
    {
        int res = tableManage.InsertInto(Tokens);
        res == 1 ? cout << "Tuple inserted successfully" << endl : cout << "Tuple not inserted" << endl;
    }

    else if (Tokens[0] == "select")
    {
        tableManage.Select(Tokens);
    }

    else if (Tokens[0] == "update")
    {
        tableManage.UpdateTable(Tokens);
    }

    else if (Tokens[0] == "delete" && Tokens[1] == "from")
    {
        tableManage.DeleteFrom(Tokens);
    }

    else if (Tokens[0] == "quit")
    {
        cout << "Program terminated successfully." << endl;
        exit(0);
    }
    else
    {
        cout << "INVALID QUERY" << endl;
    }
};

void QueryProcessor::run(const string &Query)
{
    if (Query.back() != ';')
    {
        cout << "; missing at the end" << endl;
    }
    else
    {
        ParseIntoTokens(Query);
        ToSmallerCase();
        DisplayTokens();
    }

    bool noerrors = error_class.ErrorsChecking(Tokens);
    if (noerrors)
    {
        //cout << "No errors found in the query." << endl;
        executeQuery();
    }
    else
    {
        cout << "Query execution failed due to errors." << endl;
    }
}
