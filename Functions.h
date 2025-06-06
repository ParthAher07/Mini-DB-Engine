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


// Implementation of SchemaManager methods


bool SchemaManager::doesTableExists2(const string& tableName)
{
    fstream SchemaFile;
    SchemaFile.open("SchemaFile.txt");
    if(SchemaFile)
    {
        string line;
        while(!SchemaFile.eof())
        {
            getline(SchemaFile,line);
            if(line[0]=='*')  // *TableName*
            {
                string name = line.substr(1,line.size()-2);
                if(name==tableName)
                {
                    SchemaFile.close();
                    return true;
                }
            }
        }
    }
    else
        cout<<"Schema File doesn't exists"<<endl;
    return false;
}


void SchemaManager::CreateTable(vector<string>&Tokens)
{
    //If control comes here means, table with specified name doesn't exists
    //So, Append the name of table and its attribute to schema file
    {
        fstream SchemaFile;
        SchemaFile.open("SchemaFile.txt");

        SchemaFile << "*" << Tokens[2] << "*" << endl << "<<" << endl;
        SchemaFile << "pk: " << Tokens.back() << endl;

        int i = 3;
        while(i<Tokens.size()-3)
        {
            SchemaFile << Tokens[i] << " ";

            if(Tokens[i+1]=="varchar")
                {SchemaFile << Tokens[i+1] << " " << Tokens[i+2];  i+=3;}

            else if(Tokens[i+1]=="decimal")
                {SchemaFile << Tokens[i+1] << " " << Tokens[i+2] <<  " " << Tokens[i+3]; i+=4;}

            else
            {
                SchemaFile << Tokens[i+1];
                i+=2;
            }
            if(Tokens[i]=="check")
            {
                SchemaFile <<" " << Tokens[i] << " " ;
                SchemaFile << Tokens[i+1] << " " << Tokens[i+2] << " " << Tokens[i+3] ;
                i+=4;
                while(Tokens[i]=="AND" || Tokens[i]=="OR")
                {
                    SchemaFile <<" " << Tokens[i] << " " ;
                    SchemaFile << Tokens[i+1] << " " << Tokens[i+2] << " " << Tokens[i+3] ;
                    i+=4;
                }
            }
            SchemaFile << endl;

        }
        SchemaFile << ">>" << endl <<endl;
        SchemaFile.close();

        cout << "Table Created Successfully"<<endl;
        
    }
        
}

void SchemaManager::delete_last_line()
{   
    ifstream fileIn( "SchemaFile.txt" );                  // Open for reading

    stringstream buffer;                                  // Store contents in a std::string
    buffer << fileIn.rdbuf();
    string contents = buffer.str();

    fileIn.close();
    contents.pop_back();                                  // Remove last character

    ofstream fileOut( "SchemaFile.txt");                  // Open for writing (while also clearing file)
    fileOut << contents;                                  // Output contents with removed character
    fileOut.close(); 
}

void SchemaManager::DropTable(vector<string>& Tokens)
{
    //drop table Students;
    fstream SchemaFile;
    SchemaFile.open("SchemaFile.txt",ios::in);
    
    fstream temp;
    temp.open("temp.txt",ios::out);
    
    string line;
    while(!SchemaFile.eof())
    {
        getline(SchemaFile,line);
        if(line[0]=='*' && line.substr(1,line.size()-2)==Tokens[2])// *Teacher*
        {
            while(line!=">>")
                getline(SchemaFile,line);

            getline(SchemaFile,line);
            getline(SchemaFile,line);
            
        }
        temp << line << endl;
    }
    
    cout<<"<"<<Tokens[2]<<"> Dropped Successfully"<<endl;
    
    temp.close();
    SchemaFile.close();
    remove("SchemaFile.txt");
    rename("temp.txt","SchemaFile.txt");

    char tableName[30];
    strcpy(tableName, (Tokens[2]+".txt").c_str());
    remove(tableName);
   
    delete_last_line();
}

void SchemaManager::DescribeTable(vector<string>& Tokens)
{
    fstream SchemaFile;
    SchemaFile.open("SchemaFile.txt",ios::in);

    string line;
    while(!SchemaFile.eof())
    {
        getline(SchemaFile,line);
        if(line[0]=='*' && line.substr(1,line.size()-2)==Tokens[1])// *Teacher*
        {
            getline(SchemaFile,line);
            while(1)
            {
                getline(SchemaFile,line);
                if(line==">>")
                    break;
                cout<<line<<endl;
            }
            break;
        }    
    }     
}

int SchemaManager::Count_no_Attributes(const string& TableName)
{
    //This function returns the number of attributes of the table-tableName
    fstream SchemaFile;
    SchemaFile.open("SchemaFile.txt",ios::in);
    int attributes=0;

    if(SchemaFile)
    {
        string line;
        while(!SchemaFile.eof())
        {
            getline(SchemaFile,line);
            if(line[0]=='*')
            {
                string name = line.substr(1,line.size()-2);
                if(name==TableName)
                {
                    getline(SchemaFile,line);//<<
                    getline(SchemaFile,line);//pk:

                    while(line!=">>")
                    {
                        attributes++;
                        getline(SchemaFile,line);
                    }
                    return attributes-1;
                }
            }
        }
    }
    else
    cout<<"Schema File not found"<<endl;

    return 0;
}

void SchemaManager::FillingAttributesOfTable(const string& tableName)
{
    attributes_of_table.clear();
    fstream SchemaFile;
    SchemaFile.open("SchemaFile.txt",ios::in);
    string line;
    while(!SchemaFile.eof())
    {
        getline(SchemaFile,line);
        if(line[0]=='*')
        {
            string name = line.substr(1,line.size()-2);
            if(name==tableName)
            {
                getline(SchemaFile,line);//<<
                getline(SchemaFile,line);//pk: 

                while(line!=">>")
                {
                    getline(SchemaFile,line);
                    if(line==">>")break;

                    string temp="";
                    int i=0;
                    while(line[i]!=' ')
                    {
                        temp += line[i];
                        i++;
                    }
                    attributes_of_table.push_back(temp);
                }

                SchemaFile.close();
                break;
            }
        }
    }
}


// Implementation of TableManager methods

