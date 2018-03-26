//Jakub Taczała 226495, Martyna Gottschling 226448, GRUPA:5
//Lista 2 - jednomaszynowy problem PRG
//Algorytm Schrage i alogrytm Schrage z przerwaniami

#include <iostream>
#include <string>
#include <fstream>

#include <ctime>

#include <cstdio>
#include <vector>
#include <queue>
#include <deque>

#include <algorithm>    // std::swap
using namespace std;

//----------STRUKTURA----------
int nr_param=3;
struct job{
    int r;
    int p;
    int q;
};

//----------LADOWANIE PLIKU----------
void name_file_to_open(string& name){
    cout<<"Nazwa pliku do otwarcia: ";
    cin>>name;
}

int load(string& name, int& row, int& column, vector<job>& jobs){
    ifstream file;
/*
    file.open(name.c_str(), ios::in);
    if(!file.good()) {
	cout<<"Błąd otwarcia pliku "<<name<<endl; 
	file.close(); 
	return false;
    }

    file>>row>>column;
    while(true){
	job tmp;
	file>>tmp.r>>tmp.p>>tmp.q;
	if(file.good() )
		jobs.push_back(tmp);
	else break;
    }
*/
    file.open(name.c_str(), ios::in);
    if(file.good()){
        file>>row>>column;
        for(int i=0; i<row; i++){
            job tmp;
	        file>>tmp.r>>tmp.p>>tmp.q;
            jobs.push_back(tmp);
        }
    }
    else cout<<"Błąd otwarcia pliku "<<name<<endl;
    
    file.close();
    return true;
}

bool check(int& row, int& column, vector<job>& jobs){
    //if(jobs.size()==row) return true;
    if(nr_param==column) return true;
    else{
	cout<<"!!!---Blad pliku---!!!"<<endl;
	cout<<"Wlasciwosci pliku: ";
	cout<<"\twiersze:"<<row;
        cout<<"\tparametry:"<<column<<endl;

	cout<<"Wczytano: \t";
	cout<<"\twiersze:"<<jobs.size();
        cout<<"\tparametry:"<<nr_param<<endl;
	return false;
    }
}

void save(string name, double result){
    //ofstream file("time.txt", ios::app);
    ofstream file("result.txt", ios::app);
    file<<name<<" & "<<result<<endl;
    
    file.close();
}
//----------WYSWIETLANIE----------
void show(vector<job>& jobs){
    cout<<"---"<<endl;
    cout<<jobs.size()<<" "<<nr_param;
    for(int i=0; i<jobs.size(); i++){
	cout<<endl;
	cout<<jobs[i].r<<" "<<jobs[i].p<<" "<<jobs[i].q<<" ";
    }
    cout<<endl;
    cout<<"---"<<endl;
}

//----------FUNKCJA CELU----------
int max(int& row, int tab[]){
    int max=0;

    for(int i=0; i<row; i++)
        if(max<tab[i]) max=tab[i];
    return max;
}


int C_MAX(vector<job>& jobs){
    int tmp=0;
    int size=jobs.size();
    int tab_tmp[size];

    for(int i=0; i<jobs.size(); i++){
        if(tmp>jobs[i].r) tmp+=jobs[i].p;
        else tmp=jobs[i].r+jobs[i].p;
        tab_tmp[i]=tmp+jobs[i].q;
    }
    return max(size, tab_tmp);
}

//----------BUBBLE SORTR----------
int bubble_sortR(vector<job>& v){
    int n=v.size();
    int tmp=0;

    do{
        for(int i=0; i<(n-1); i++){
            if(v[i].r>v[i+1].r){
		        tmp=i+1;
		        swap(v[i],v[tmp]);
            }
        }
        n--;
    }while(n>1);
    return C_MAX(v);
}

void b_sortR(deque<job>& v){
    int n=v.size();
    int tmp=0;

    do{
        for(int i=0; i<(n-1); i++){
            if(v[i].r>v[i+1].r){
		tmp=i+1;
		swap(v[i],v[tmp]);
            }
        }
        n--;
    }while(n>1);
}

//----------BUBBLE SORTQ----------
int bubble_sortQ(vector<job>& v){
    int n=v.size();
    int tmp=0;

    do{
        for(int i=0; i<(n-1); i++){
            if(v[i].q<v[i+1].q){
		tmp=i+1;
		swap(v[i],v[tmp]);
            }
        }
        n--;
    }while(n>1);
    return C_MAX(v);
}

void b_sortQ(deque<job>& v){
    int n=v.size();
    int tmp=0;

    do{
        for(int i=0; i<(n-1); i++){
            if(v[i].q<v[i+1].q){
		tmp=i+1;
		swap(v[i],v[tmp]);
            }
        }
        n--;
    }while(n>1);
}
//---------- 2-opt ----------
int two_opt(vector<job>& v){
	int result_old=C_MAX(v);
	int result_new=0;
	
	for(int i=0;i<v.size();i++){
		for(int j=i+1;j<v.size();j++){
			swap(v[i],v[j]);				
			result_new=C_MAX(v);
			if(result_new<result_old){
				i=0;
				j=1;
				result_old=result_new;
			}
			else{
				swap(v[j],v[i]);
			}

		}	
	}	
return	result_old;
}


//---------- Schrage ----------
int Schrage(vector<job>& v){
    int tmp=0;		//aktualny czas
    int cmax=0;

    deque<job> jobs_N; //zbior zadan niegotowych
    deque<job> jobs_G; //zbior zadan gotowych
    vector<job> Schrage; //permutacja czesciowa

    for(int i=0; i<v.size(); i++)
	jobs_N.push_back(v[i]); //zapis wszystkich zadan jako niegotowe

    b_sortR(jobs_N); //sortowanie rosnaco po r
    //front = zadanie o najmniejszym czasie przygotowania

    //dopoki mamy jakies zadania niegotowe lub gotowe
    while( (jobs_N.empty()!=true) || (jobs_G.empty()!=true) ){
        //dopoki mamy zadania niegotowe i ich czas przygotowania minal
	    while( (jobs_N.empty()!=true) && (jobs_N.front().r<=tmp) ){
		    jobs_G.push_back(jobs_N.front()); //dodawanie zad gotowego do realizacji
		    jobs_N.pop_front(); //usuwanie zad z niegotowych
	    }
	    b_sortQ(jobs_G); //sortowanie malejaco po q
        //front = zadanie o najwiekszym czasie dostarczenia

	    if( jobs_G.empty() ){ //jesli nie ma zadnego gotowego
		    tmp=jobs_N.front().r; //przesuwamy sie w czasie
	    }   //aktualny czas to czas najblizszego przygotowanego

	    else{ //jesli mamy zad gotowe
		    Schrage.push_back(jobs_G.front()); //dodajemy je do permutacji
		    jobs_G.pop_front();
		    tmp+=Schrage.back().p; //przesywamy sie w czasie o czas realizacji zad

		    if(tmp + Schrage.back().q > cmax)
			   cmax=tmp + Schrage.back().q; //uaktualnienie najpozniejszego czasu dostarczenia
	    }

    }
    v.clear();
    v=Schrage; //ostateczna permutacja
    Schrage.clear();
    return cmax;
}

//---------- Schrage z przerwaniami----------
int SchrageP(vector<job>& v){
    int tmp=0;		//aktualny czas
    int cmax=0;

    deque<job> jobs_N; //zbior zadan niegotowych
    deque<job> jobs_G; //zbior zadan gotowych
    deque<job> jobs_P; //lista przerwan
    vector<job> Schrage;

    for(int i=0; i<v.size(); i++)
	jobs_N.push_back(v[i]);

    b_sortR(jobs_N); //sortowanie rosnaco po r
    //front = zadanie o najmniejszym czasie przygotowania

    //dopoki mamy jakies zadania niegotowe lub gotowe
    while( (jobs_N.empty()!=true) || (jobs_G.empty()!=true) ){
        //dopoki mamy zadania niegotowe i ich czas przygotowania minal
	    while( (jobs_N.empty()!=true) && (jobs_N.front().r<=tmp) ){
		    jobs_G.push_back(jobs_N.front()); //dodawanie zad gotowego do realizacji
		    jobs_N.pop_front(); //usuwanie zad z niegotowych
	    }
	    b_sortQ(jobs_G); //sortowanie malejaco po q
        //front = zadanie o najwiekszym czasie dostarczenia

	    if( jobs_G.empty() ){ //jesli nie ma zadnego gotowego
		    tmp=jobs_N.front().r; //przesuwamy sie w czasie
	    }   //aktualny czas to czas najblizszego przygotowanego

	    else{ //jesli mamy zad gotowe
            jobs_P.clear(); //pusta lista przerwan

            for(int i=0; i<jobs_N.size();i++)
                if( (jobs_G.front().p+tmp>jobs_N[i].r) && (jobs_G.front().q>jobs_N[i].q) )
                    jobs_P.push_back(jobs_N[i]);

            if(jobs_P.empty()){
		        Schrage.push_back(jobs_G.front());
		        jobs_G.pop_front();
		        tmp+=Schrage.back().p;
                

		        if(tmp + Schrage.back().q > cmax)
			        cmax=tmp + Schrage.back().q;
            }

            else{

                job p1=jobs_G.front();
                jobs_G.pop_front();
                job p2=p1;


                p1.p = jobs_P.front().r - tmp;
                p2.p -= p1.p;
                jobs_G.push_back(p2);
	            b_sortQ(jobs_G); //sortowanie malejaco po q
                //front = zadanie o najwiekszym czasie dostarczenia

                Schrage.push_back(p1);
                tmp += Schrage.back().p;

                if(tmp + Schrage.back().q > cmax)
                    cmax=tmp + Schrage.back().q;

            }


	    }

    }
    v.clear();
    v=Schrage; //ostateczna permutacja
    Schrage.clear();
    return cmax;
}

//----------MAIN----------
int main(){
    int lp=14;
    string nazwa[lp];
    nazwa[0]="in6.txt";
    nazwa[1]="in10.txt";
    nazwa[2]="in20.txt";
    nazwa[3]="in20_2.txt";
    nazwa[4]="in50.txt";
    nazwa[5]="in50_2.txt";
    nazwa[6]="in50_3.txt";
    nazwa[7]="in100.txt";
    nazwa[8]="in100_2.txt";
    nazwa[9]="in100_3.txt";
    nazwa[10]="in100_4.txt";
    nazwa[11]="in200.txt";
    nazwa[12]="in200_2.txt";
    nazwa[13]="in500.txt";

    for(int i=0;i<lp;i++){

    vector <job> jobs;
    string name=nazwa[i];
    int row, column=0;

    //name_file_to_open(name);
    load(name,row,column,jobs);
    if(check(row,column,jobs)==false) return 0;

    //show(jobs);
    //cout<<name<<endl;
    //cout<<C_MAX(jobs)<<endl;
    //show(jobs);
    //cout<<C_MAX(jobs)<<endl;
    //two_opt(jobs);
    //cout<<C_MAX(jobs)<<endl;

    int result=SchrageP(jobs);
    cout<<name<<endl;
    cout<<result<<endl;
    save(name,result);
    }
}
