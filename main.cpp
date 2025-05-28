#include<bits/stdc++.h>
using namespace std;

set<string> keywords = {
    "create","table","primary","key",
    "int","varchar","date","decimal"
    "drop","describe",
    "insert","into","values",
    "help","tables",
    "select","from","where","and","or",
};

vector<string> Tokens;

void DisplayTokens() {
    cout<<"Tokens: "<<endl;
    if(Tokens.size() == 0) {
        cout<<"No tokens found."<<endl;
        return;
    }
    for(string x:Tokens) cout<<x<<endl;
}

void ParseIntoTokens(string Query)
{
    string temp="";

    for(int i=0;i<Query.size();i++)
    {
        char c = Query[i];

        if(c=='"')
        {
            i++;
            while(Query[i]!='"')
            {
                temp+=Query[i];
                i++;
            }
            
            if(temp!="")
                Tokens.push_back(temp);
            temp = "";
        }
        else if(c==' ' || c=='(' || c==')' || c==',' || c==';' || c=='*')
        {
            if(temp!="")
                Tokens.push_back(temp);
            if(c=='*')//for handling special case in select
                Tokens.push_back("*");
            temp = "";
        }
        else if(Query[i]=='!' && Query[i+1]=='=')
        {
            if(temp!="")
                Tokens.push_back(temp);
            temp = "";

            Tokens.push_back("!=");
            i++;
        }
        else if(c=='<' || c=='>'|| c=='=')//we can add other operators if we want to
        {
            if(temp!="")
                Tokens.push_back(temp);
            temp = "";

            Tokens.push_back(string(1,c));
        }
        
        else 
        {
            temp += c; 
        }
    }
    if(temp!="")
        Tokens.push_back(temp);
}

void Execute(){

}

void ToSmallerCase(){

    for(int i = 0;i<Tokens.size();i++){
        string temp = Tokens[i];
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        if(keywords.find(temp) != keywords.end()) Tokens[i] = temp;
    }

}

int main(){

    system("cls");
    string Query;

    while(1){
        Tokens.clear();
        //attributes_of_table.clear();
        cout<<endl<<">> ";

        getline(cin,Query); 
        cout<<endl;
        
        if(Query.back()!=';') 
        {
            cout<<"; missing at the end"<<endl;
            continue;
        }

        
        ParseIntoTokens(Query);
        ToSmallerCase();
        DisplayTokens();
        // bool noerrors = ErrorsChecking(Tokens);

        // if(noerrors)
        //     Execute(); 
    }


    return 0;
}