// 1 - 2

#include <iostream>
using namespace std;

#define MAX 50

class List {
    int* niza;
    int len;

public:
    List() {
        niza = nullptr;
        len = 0;
    }

    List(const int* niza, int len) {
        this->niza = new int[len];
        for(int i = 0; i < len; i++)
            this->niza[i] = niza[i];
        this->len = len;
    }

    List(const List& cpy) {
        this->niza = new int[cpy.len];
        for(int i = 0; i < cpy.len; i++)
            this->niza[i] = cpy.niza[i];
        this->len = cpy.len;
    }

    List& operator=(const List& that) {
        if(this == &that) return *this;

        delete [] this->niza;
        this->niza = new int[that.len];

        for(int i = 0; i < that.len; i++)
            this->niza[i] = that.niza[i];

        this->len = that.len;

        return *this;
    }

    int* getNiza() {
        return niza;
    }

    void setNiza(int* niza) {
        this->niza = niza;
    }

    int getLen() {
        return len;
    }

    void setLen(int len) {
        this->len = len;
    }

    void pecati() {
        cout << len << ": ";
        for(int i = 0; i < len; i++)
            cout << niza[i] << " ";

        cout << "sum: " << sum() << " average: " << average() << "\n";
    }

    int sum() {
        int s = 0;
        for(int i = 0; i < len; i++) s += niza[i];
        return s;
    }

    double average() {
        return (double)sum() / len;
    }

    ~List() {
        delete [] niza;
    }
};

class ListContainer {
    List* lists;
    int len;
    int obidi;

public:
    ListContainer() {
        lists = new List[MAX];
        len = obidi = 0;
    }

    ListContainer(List* lists, int len, int obidi) {
        this->lists = new List[MAX];
        for(int i = 0; i < len; i++)
            this->lists[i] = lists[i];
        this->len = len;
        this->obidi = obidi;
    }

    ListContainer(const ListContainer& cpy) {
        this->lists = new List[MAX];
        for(int i = 0; i < cpy.len; i++)
            this->lists[i] = cpy.lists[i];
        this->len = cpy.len;
        this->obidi = cpy.obidi;
    }

    ListContainer& operator=(const ListContainer& that) {
        if(this == &that) return *this;

        delete [] lists;
        this->lists = new List[MAX];

        for(int i = 0; i < that.len; i++)
            this->lists[i] = that.lists[i];

        this->len = that.len;
        this->obidi = that.obidi;

        return *this;
    }

    void print() {
        if(len <= 0) {
            cout << "The list is empty\n";
            return;
        }

        for(int i = 0; i < len; i++) {
            cout << "List number: " << (i + 1) << " List info: ";
            lists[i].pecati();
        }

        cout << "Sum: " << sum() << " Average: " << average() << "\n";
        cout << "Successful attempts: " << len << " Failed attempts: " << obidi - len << "\n";
    }

    void addNewList(List l) {
        obidi++;

        for(int i = 0; i < len; i++) {
            if(lists[i].sum() == l.sum()) {
                return;
            }
        }

        lists[len++] = l;
    }

    int sum() {
        int s = 0;
        for(int i = 0; i < len; i++) s += lists[i].sum();
        return s;
    }

    double average() {
        int avg = 0;
        for(int i = 0; i < len; i++) avg += lists[i].getLen();
        return (double)sum() / avg;
    }

    ~ListContainer() {
        delete [] lists;
    }
};

int main()
{

    ListContainer lc;
    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        int n;
        int niza[100];

        cin >> n;

        for (int j = 0; j < n; j++)
        {
            cin >> niza[j];

        }

        List l = List(niza, n);

        lc.addNewList(l);
    }


    int testCase;
    cin >> testCase;

    if (testCase == 1)
    {
        cout << "Test case for operator =" << endl;
        ListContainer lc1;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1 = lc;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1.sum();
        lc1.average();

    }
    else
    {
        lc.print();
    }
}