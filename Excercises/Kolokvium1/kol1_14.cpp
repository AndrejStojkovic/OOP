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

public:
    File() {
        this->name = new char[2];
        strcpy(this->name, " ");
        ext = txt;
        this->owner = new char[2];
        strcpy(this->owner, " ");
        size = 0;
    }

    File(const char* name, const char* owner, const int size, const Extension ext) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->ext = ext;
        this->owner = new char[strlen(owner) + 1];
        strcpy(this->owner, owner);
        this->size = size;
    }

    File(const File& copy) {
        this->name = new char[strlen(copy.name) + 1];
        strcpy(this->name, copy.name);
        this->ext = copy.ext;
        this->owner = new char[strlen(copy.owner) + 1];
        strcpy(this->owner, copy.owner);
        this->size = copy.size;
    }

    File& operator=(const File& newFile) {
        if(this == &newFile) return *this;

        this->name = new char[strlen(newFile.name) + 1];
        strcpy(this->name, newFile.name);
        this->ext = newFile.ext;
        this->owner = new char[strlen(newFile.owner) + 1];
        strcpy(this->owner, newFile.owner);
        this->size = newFile.size;

        return *this;
    }

    void print() {
        cout << "File name: " << this->name << "." << extensions[this->ext] << "\n";
        cout << "File owner: " << this->owner << "\n";
        cout << "File size: " << this->size << "\n";
    }

    bool equals(const File& that) {
        return strcmp(this->name, that.name) == 0 && strcmp(this->owner, that.owner) == 0 && this->ext == that.ext;
    }

    bool equalsType(const File& that) {
        return strcmp(this->name, that.name) == 0 && this->ext == that.ext;
    }

    char* getName() const { return name; }
    void setName(const char* name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    Extension getExtension() const { return ext; }
    void setExtension(const Extension ext) { this->ext = ext; }

    char* getOwner() const { return owner; }
    void setOwner(const char* owner) {
        this->owner = new char[strlen(owner) + 1];
        strcpy(this->owner, owner);
    }

    int getSize() const { return size; }
    void setSize(const int size) { this->size = size; }

    ~File() {
        delete [] name;
        delete [] owner;
    }
};

class Folder {
    char* name;
    File* files;
    int num;

public:
    Folder() {
        this->name = new char[1];
        strcpy(this->name, " ");
        files = new File[10];
        num = 0;
    }

    Folder(const char* name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        files = new File[10];
        num = 0;
    }

    Folder(const char* name, File* files, const int num) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->files = files;
        this->num = num;
    }

    char* getName() const { return name; }
    void setName(const char* name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    File* getFiles() const { return files; }
    void setFiles(File* files) { this->files = files; }

    int getNum() const { return num; }
    void setNum(const int num) { this->num = num; }

    void print() {
        cout << "Folder name: " << this->name << "\n";
        for(int i = 0; i < num; i++) {
            files[i].print();
        }
    }

    void add(const File& file) {
        files[num++] = file;
    }

    void remove(const File& file) {
        int idx = -1;
        for(int i = 0; i < num; i++) {
            if(files[i].equals(file)) {
                idx = i;
            }
        }

        if(idx == -1) return;

        for(int i = idx; i < num; i++) {
            files[i] = files[i + 1];
        }

        num--;
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