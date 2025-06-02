#include<bits/stdc++.h>
#include "QueryProcessor.h" 
using namespace std;

int main(){

    system("cls");
    string Query;

    while(1){
        //attributes_of_table.clear();
        cout<<endl<<">> ";

        getline(cin,Query); 
        cout<<endl;

        QueryProcessor qp;
        qp.run(Query);
        
  
        // bool noerrors = ErrorsChecking(Tokens);

        // if(noerrors)
        //     Execute(); 
    }


    return 0;
}