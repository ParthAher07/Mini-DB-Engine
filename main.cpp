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
    for(string x:Tokens) cout<<x<<endl;
}


void ParseIntoTokens(string Query) {

}

void Execute(){

}

void ToSmallerCase(){
   
}

int main(){

    system("cls");
    string Query;

    while(1){
        Tokens.clear();
        attributes_of_table.clear();
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
        //DisplayTokens();
        bool noerrors = ErrorsChecking(Tokens);

        if(noerrors)
            Execute(); 
    }


    return 0;
}