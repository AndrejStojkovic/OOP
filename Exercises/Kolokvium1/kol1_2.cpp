// 1 - 2

#include <iostream>
using namespace std;
#define MAX 25

class List {
    int* niza;
    int len;

    void copy_list(const List& other) {
        this->niza = new int[other.len];
        for(int i = 0; i < other.len; i++) {
            this->niza[i] = other.niza[i];
        }
        this->len = other.len;
    }

public:
    List() {
        niza = nullptr;
        len = 0;
    }

    List(int* niza, int len) {
        this->niza = new int[len];
        for(int i = 0; i < len; i++) {
            this->niza[i] = niza[i];
        }
        this->len = len;
    }

    List(const List& other) {
        copy_list(other);
    }

    List& operator=(const List& other) {
        if(this == &other) {
            return *this;
        }
        delete [] this->niza;
        copy_list(other);
        return *this;
    }

    int getLen() {
        return len;
    }

    void pecati() {
        cout << len << ": ";
        for(int i = 0; i < len; i++) {
            cout << niza[i] << " ";
        }
        cout << "sum: " << sum() << " average: " << average() << "\n";
    }

    int sum() {
        int s = 0;
        for(int i = 0; i < len; i++) {
            s += niza[i];
        }
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

    void copy_container(const ListContainer& other) {
        this->lists = new List[MAX];
        for(int i = 0; i < other.len; i++)
            this->lists[i] = other.lists[i];
        this->len = other.len;
        this->obidi = other.obidi;
    }

public:
    ListContainer() {
        this->lists = new List[MAX];
        this->len = this->obidi = 0;
    }

    ListContainer(const ListContainer& other) {
        copy_container(other);
    }

    ListContainer& operator=(const ListContainer& other) {
        if(this == &other) {
            return *this;
        }
        delete [] lists;
        copy_container(other);
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
        cout << "Successful attempts: " << len << " Failed attempts: " << (obidi - len) << "\n";
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
        for(int i = 0; i < len; i++) {
            s += lists[i].sum();
        }
        return s;
    }

    double average() {
        int avg = 0;
        for(int i = 0; i < len; i++) {
            avg += lists[i].getLen();
        }
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