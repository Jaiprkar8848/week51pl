#include<bits/stdc++.h>
using namespace std;
#define N 20

int main(){
    vector<int> jp(N);
    // creating object 
    ifstream jpFile("file1.txt");

    // file can't opened
    if(jpFile.is_open()==0){
        cout<<"Some error in opening"<<endl;
        return 0;
    }
    
    string x;
    int i=0;
    // reading file line by line 
    while(getline(jpFile,x))
        jp[i++]=stoi(x);

    for(i=0;i<10;i++)
        cout<<jp[i]<<" ";
    
    jpFile.close();
}