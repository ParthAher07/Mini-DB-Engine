# pragma once
#include <bits/stdc++.h>
using namespace std;

class QueryProcessor; // Forward declaration to allow access to QueryProcessor

class ErrorHandling {

private:
    string schemaFileName;

    bool doesTableExists(string tableName) const;
    bool validateCreate(const vector<string>& Tokens) const;
    bool validateDrop(const vector<string>& Tokens) const;
    bool validateDescribe(const vector<string>& Tokens) const;
    bool validateInsert(const vector<string>& Tokens) const;
    bool validateDelete(const vector<string>& Tokens) const;
    bool validateUpdate(const vector<string>& Tokens) const;

    ErrorHandling(string fileName);
    bool ErrorsChecking(vector<string>& Tokens) const;

    friend class QueryProcessor; // Allow QueryProcessor to access private members if needed
};


ErrorHandling::ErrorHandling(string fileName) : schemaFileName(fileName) {}

bool ErrorHandling::doesTableExists(string tableName) const {
    fstream SchemaFile(schemaFileName);
    if (!SchemaFile)
        return false;

    string line;
    while (!SchemaFile.eof()) {
        getline(SchemaFile, line);
        if (!line.empty() && line[0] == '*') {
            string name = line.substr(1, line.size() - 2);
            if (name == tableName) {
                SchemaFile.close();
                return true;
            }
        }
    }
    SchemaFile.close();
    return false;
}

bool ErrorHandling::validateCreate(const vector<string>& Tokens) const {
    if (doesTableExists(Tokens[2])) {
        cout << "table <" << Tokens[2] << "> already exists" << endl;
        cout << "Table not created" << endl;
        return false;
    }

    int Tsize = Tokens.size();
    if (Tsize < 3 || Tokens[Tsize - 3] != "primary" || Tokens[Tsize - 2] != "key") {
        cout << "Defining PK is mandatory" << endl;
        cout << "Table not created" << endl;
        return false;
    }

    return true;
}

bool ErrorHandling::validateDrop(const vector<string>& Tokens) const {
    if (!doesTableExists(Tokens[2])) {
        cout << "table <" << Tokens[2] << "> doesn't exists" << endl;
        cout << "Table not dropped" << endl;
        return false;
    }
    return true;
}

bool ErrorHandling::validateDescribe(const vector<string>& Tokens) const {
    if (!doesTableExists(Tokens[1])) {
        cout << "table <" << Tokens[1] << "> doesn't exists" << endl;
        cout << "Table cannot be described" << endl;
        return false;
    }
    return true;
}

bool ErrorHandling::validateInsert(const vector<string>& Tokens) const {
    if (!doesTableExists(Tokens[2])) {
        cout << "table <" << Tokens[2] << "> doesn't exists" << endl;
        cout << "Tuple not inserted" << endl;
        return false;
    }
    return true;
}

bool ErrorHandling::validateDelete(const vector<string>& Tokens) const {
    if (!doesTableExists(Tokens[2])) {
        cout << "table <" << Tokens[2] << "> doesn't exists" << endl;
        cout << "0 rows affected" << endl;
        return false;
    }
    return true;
}

bool ErrorHandling::validateUpdate(const vector<string>& Tokens) const {
    if (!doesTableExists(Tokens[1])) {
        cout << "table <" << Tokens[1] << "> doesn't exists" << endl;
        cout << "0 rows affected" << endl;
        return false;
    }
    return true;
}

bool ErrorHandling::ErrorsChecking(vector<string>& Tokens) const {
    if (Tokens.empty())
        return false;

    const string& cmd = Tokens[0];

    if (cmd == "create" && Tokens[1] == "table")
        return validateCreate(Tokens);

    else if (cmd == "drop" && Tokens[1] == "table")
        return validateDrop(Tokens);

    else if (cmd == "describe")
        return validateDescribe(Tokens);

    else if (cmd == "insert" && Tokens[1] == "into")
        return validateInsert(Tokens);

    else if (cmd == "delete" && Tokens[1] == "from")
        return validateDelete(Tokens);

    else if (cmd == "update")
        return validateUpdate(Tokens);

    else if (cmd == "select" || (cmd == "help") || (cmd == "quit"))
        return true;

    return true;
}
