#define SIZE_TAB 100

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void name_file_to_open(string& name){
    cout<<"Nazwa pliku do otwarcia: ";
    cin>>name;
}
void load(string& name, int& row, int& column, int tab_1[SIZE_TAB][SIZE_TAB]){
    ifstream file;

    file.open(name.c_str(), ios::in);
    if(file.good()){
        file>>row>>column;

        for(int i=0; i<row; i++)
	    for(int j=0; j<column; j++)
	        file>>tab_1[i][j];
    }
    else cout<<"Błąd otwarcia pliku "<<name<<endl;
    
    file.close();
}

void save(string name, int result){
    ofstream file("result.txt", ios::app);
    file<<name<<" ANS: "<<result<<endl;
    
    file.close();
}

void show(int& row, int& column, int tab_1[SIZE_TAB][SIZE_TAB]){
    cout<<row<<" "<<column;
    for(int i=0; i<row; i++){
	cout<<endl;
	for(int j=0; j<column; j++)
	    cout<<tab_1[i][j]<<" ";
    }
    cout<<endl;
}

int max(int& row, int tab[]){
    int max=0;

    for(int i=0; i<row; i++)
        if(max<tab[i]) max=tab[i];
    return max;
}

void swap(int& what, int& with_what, int& column, int tab[SIZE_TAB][SIZE_TAB]){
    int tmp=0;

        for(int j=0; j<column; j++){   
            tmp=tab[what][j];
            tab[what][j]=tab[with_what][j];
            tab[with_what][j]=tmp;
        }
}

void bubble_sortR(int& row, int& column, int tab[SIZE_TAB][SIZE_TAB]){
    int n=row;
    int tmp=0;

    do{
        for(int i=0; i<(n-1); i++){
            if(tab[i][0]>tab[i+1][0]){
		tmp=i+1;
                swap(i, tmp, column, tab);
            }
        }
        n--;
    }while(n>1);
}

int C_MAX(int& row,int tab_1[SIZE_TAB][SIZE_TAB]){
    int tmp=0;
    int tab_tmp[row];

    for(int i=0; i<row; i++){
        if(tmp>tab_1[i][0]) tmp+=tab_1[i][1];
        else tmp=tab_1[i][0]+tab_1[i][1];
        tab_tmp[i]=tmp+tab_1[i][2];

//	cout<<"test "<<tmp<<" "<<tab_tmp[i]<<endl;
    }
//      cout<<"wynik "<<max(row, tab_tmp);
    return max(row, tab_tmp);
}

int main(){
    string name;
    int row, column;
    int tab_1[SIZE_TAB][SIZE_TAB];
    
    name_file_to_open(name);
    
    load(name, row, column, tab_1);
    
//  show(row, column, tab_1);

    bubble_sortR(row, column, tab_1);

//  show(row, column, tab_1);

    save(name, C_MAX(row, tab_1));
    
}
