// 1 - 8

#include <iostream>
using namespace std;

struct Laptop {
    char firma[100];
    float golemina;
    int touch;
    int cena;
};

struct ITStore {
    char ime[100];
    char lokacija[100];
    Laptop lp[100];
    int n;

    void print();
};

void ITStore::print() {
  cout << ime << " " << lokacija << "\n";
  for(int i = 0; i < n; i++) {
      cout << lp[i].firma << " ";
      const float golemina = lp[i].golemina;
      cout << golemina << " ";
      cout << lp[i].cena << "\n";
  }
}

void najeftina_ponuda(ITStore * it, int n) {
    int najeftina, setVal = 0, idx = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < it[i].n; j++) {
            if(!it[i].lp[j].touch) continue;

            if(!setVal) {
                najeftina = it[i].lp[j].cena;
                setVal = 1;
                continue;
            }

            if(it[i].lp[j].cena < najeftina) {
                idx = i;
                najeftina = it[i].lp[j].cena;
            }
        }
    }

    cout << "Najeftina ponuda ima prodavnicata:\n" << it[idx].ime << " " << it[idx].lokacija << "\n";
    cout << "Najniskata cena iznesuva: " << najeftina << "\n";
}

int main() {
    ITStore s[100];
    int n;
    cin >> n; //broj na IT prodavnici
    
    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for(int i = 0; i < n; i++){
    	cin >> s[i].ime;
        cin >> s[i].lokacija;
        cin >> s[i].n;
            for(int j = 0; j < s[i].n; j++){
        		cin >> s[i].lp[j].firma;
            	cin >> s[i].lp[j].golemina;
            	cin >> s[i].lp[j].touch;
            	cin >> s[i].lp[j].cena;
        }
    
    }
    
    
    //pecatenje na site prodavnici
    
    for(int i = 0; i<n; i++){
    	s[i].print();
    }
    
    
    //povik na glavnata metoda
    
    najeftina_ponuda(s,n);
    
    return 0;
}