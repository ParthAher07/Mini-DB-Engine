#include <bits/stdc++.h>
using namespace std;

class Util {
public:
    static string ExtractCol(const string& tuple, int colno);
    static bool isInt(const string& s);
    static vector<string> split(const string& s, char delim);
};

class SchemaManager {
public:
    bool doesTableExists2(const string& tableName);
    void CreateTable(vector<string>& Tokens);
    void delete_last_line();
    void DropTable(vector<string>& Tokens);
    void DescribeTable(vector<string>& Tokens);
    int Count_no_Attributes(const string& TableName);
    void FillingAttributesOfTable(const string& tableName);

    vector<string> attributes_of_table; // Shared for table manager access
};

class TableManager {
    SchemaManager& schema;

    int checkValuesOrder(vector<string>& Tokens);
    vector<int> Find_Indices(vector<string>& Tokens);
    bool is_Where_True(const string& tuple, vector<string>& Tokens, int i);
    void Helper_Select(vector<string>& Tokens, const string& TableNameInQuery, int i);
    vector<int> GetIndices(const string& tableName, map<string, string>& mpp);

public:
    TableManager(SchemaManager& sm) : schema(sm) {}

    int InsertInto(vector<string>& Tokens);
    void Select(vector<string>& Tokens);
    void UpdateTable(vector<string>& Tokens);
    void DeleteFrom(vector<string>& Tokens);
};


// Implementation of Util methods

string Util::ExtractCol(const string& tuple, int colno) {
     //tuple = <103,PA,24-02-2001>, colno=1, will return PA
    int comma=0;
    int i=1;
    while(comma<colno)
    {
        if(tuple[i]==',')
            comma++;
        i++;
    }
    
    
    string pk="";
    while(tuple[i]!=','&& tuple[i]!='>')
    {
        pk+=tuple[i];
        i++;
    }
    //cout<<"pk: "<<pk<<endl;
    return pk;
}

bool Util::isInt(const string& s) {
    for(char c : s)
        if(!isdigit(c))
            return false;
    return true;
}

vector<string> Util::split(const string& s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}