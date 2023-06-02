// 1 - 14

#include<iostream>
#include<cstring>
using namespace std;

enum Extension { pdf, txt, exe };
char extensions[3][4] = {"pdf", "txt", "exe"};

class File {
    char* name;
    Extension ext;
    char* owner;
    int size;

    void copy_file(const File& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->ext = other.ext;
        this->owner = new char[strlen(other.owner) + 1];
        strcpy(this->owner, other.owner);
        this->size = other.size;
    }

public:
    File() {
        this->name = new char[5];
        strcpy(this->name, "file");
        this->ext = txt;
        this->owner = new char[6];
        strcpy(this->owner, "owner");
        this->size = 0;
    }

    File(const char* name, const char* owner, const int size, const Extension ext) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->ext = ext;
        this->owner = new char[strlen(owner) + 1];
        strcpy(this->owner, owner);
        this->size = size;
    }

    File(const File& other) {
        copy_file(other);
    }

    File& operator=(const File& other) {
        if(this == &other) {
            return *this;
        }
        delete [] this->name;
        delete [] this->owner;
        copy_file(other);
        return *this;
    }

    void print() {
        cout << "File name: " << this->name << "." << extensions[this->ext] << "\n";
        cout << "File owner: " << this->owner << "\n";
        cout << "File size: " << this->size << "\n";
    }

    bool equals(const File& that) {
        return !strcmp(this->name, that.name) && !strcmp(this->owner, that.owner) && this->ext == that.ext;
    }

    bool equalsType(const File& that) {
        return !strcmp(this->name, that.name) && this->ext == that.ext;
    }

    ~File() {
        delete [] name;
        delete [] owner;
    }
};

class Folder {
    char* name;
    File* files;
    int num;

    void copy_folder(const Folder& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        for(int i = 0; i < other.num; i++) {
            this->files[i] = other.files[i];
        }
        this->num = other.num;
    }

public:
    Folder() {
        this->name = new char[8];
        strcpy(this->name, "folder");
        files = nullptr;
        num = 0;
    }

    Folder(const char* name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        files = nullptr;
        num = 0;
    }

    Folder(const Folder& other) {
        copy_folder(other);
    }

    Folder& operator=(const Folder& other) {
        if(this == &other) {
            return *this;
        }
        delete [] this->name;
        delete [] this->files;
        copy_folder(other);
        return *this;
    }

    void print() {
        cout << "Folder name: " << this->name << "\n";
        for(int i = 0; i < num; i++) {
            files[i].print();
        }
    }

    void add(const File& file) {
        File* tmp = new File[num + 1];
        for(int i = 0; i < num; i++) {
            tmp[i] = files[i];
        }
        tmp[num++] = file;

        delete [] files;
        this->files = new File[num];
        for(int i = 0; i < num; i++) {
            this->files[i] = tmp[i];
        }
        delete [] tmp;
    }

    void remove(const File& file) {
        int idx = -1, ct = 0;
        for(int i = 0; i < num; i++) {
            if(files[i].equals(file)) {
                idx = i;
                ct++;
            }
        }

        if(idx == -1) {
            return;
        }

        File* tmp = new File[num - ct];
        int curr = 0;
        for(int i = 0; i < num; i++) {
            if(files[i].equals(file)) {
                continue;
            }

            tmp[curr++] = files[i];
        }

        delete [] files;
        this->files = new File[curr];
        for(int i = 0; i < curr; i++) {
            this->files[i] = tmp[i];
        }
        delete [] tmp;

        this->num = curr;
    }

    ~Folder() {
        delete [] name;
        delete [] files;
    };
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}