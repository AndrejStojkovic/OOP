// 2 - 13

#include <iostream>
#include <cstring>
using namespace std;

class Image {
protected:
    char* name;
    char author[50];
    int width;
    int height;

private:
    void copy_image(const Image& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        strcpy(this->author, other.author);
        this->width = other.width;
        this->height = other.height;
    }

public:
    Image() {
        this->name = new char[10];
        strcpy(this->name, "untitled");
        strcpy(this->author, "unknown");
        this->width = this->height = 800;
    }

    Image(char* name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->author, "unknown");
        this->width = this->height = 800;
    }

    Image(char* name, char* author) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->author, author);
        this->width = this->height = 800;
    }

    Image(char* name, char* author, int width, int height) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->author, author);
        this->width = width;
        this->height = height;
    }

    Image(const Image& other) {
        copy_image(other);
    }

    Image& operator=(const Image& other) {
        if(this == &other) {
            return *this;
        }
        delete [] name;
        copy_image(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, Image& img) {
        out << img.name << " " << img.author << " " << img.fileSize() << "\n";
        return out;
    }

    bool operator>(Image& other) {
        return fileSize() > other.fileSize();
    }

    virtual int fileSize() {
        return width * height * 3;
    }

    ~Image() {
        delete [] name;
    }
};

class TransparentImage : public Image {
    bool transparent;

public:
    TransparentImage() : Image() {
        this->transparent = true;
    }

    TransparentImage(char* name, char* author, int width, int height, bool transparent) : Image(name, author, width, height) {
        this->transparent = transparent;
    }

    TransparentImage(const TransparentImage& other) : Image(other) {
        this->transparent = other.transparent;
    }

    TransparentImage& operator=(const TransparentImage& other) {
        if(this == &other) {
            return *this;
        }
        Image::operator=(other);
        this->transparent = other.transparent;
        return *this;
    }

    bool operator>(TransparentImage& other) {
        return fileSize() > other.fileSize();
    }

    int fileSize() {
        return transparent ? width * height * 4 : width * height + (width * height) / 8.0;
    }

    ~TransparentImage() { }
};

class Folder {
    char name[255];
    char author[50];
    Image* images[100];
    int n;

    void copy_folder(const Folder& other) {
        strcpy(this->name, other.name);
        strcpy(this->author, other.author);
        for(int i = 0; i < other.n; i++) {
            this->images[i] = other.images[i];
        }
        this->n = other.n;
    }

public:
    Folder() {
        strcpy(this->name, "unknown");
        strcpy(this->author, "unknown");
        this->n = 0;
    }

    Folder(char* name, char* author) {
        strcpy(this->name, name);
        strcpy(this->author, author);
        this->n = 0;
    }

    Folder(const Folder& other) {
        copy_folder(other);
    }

    Folder& operator=(const Folder& other) {
        if(this == &other) {
            return *this;
        }
        copy_folder(other);
        return *this;
    }

    Folder& operator+=(Image& img) {
        if(n >= 100) {
            return *this;
        }
        images[n++] = &img;
        return *this;
    }

    Image* operator[](int idx) {
        return idx < n ? images[idx] : NULL;
    }

    friend ostream& operator<<(ostream& out, Folder& f) {
        out << f.name << " " << f.author << "\n--\n";
        for(int i = 0; i < f.n; i++) {
            out << *f.images[i];
        }
        out << "--\nFolder size: " << f.folderSize() << "\n";
        return out;
    }

    int folderSize() {
        int s = 0;
        for(int i = 0; i < n; i++) {
            s += images[i]->fileSize();
        }
        return s;
    }

    Image* getMaxFile() {
        int idx = -1;

        for(int i = 0; i < n; i++) {
            if(idx == -1 || images[i]->fileSize() > images[idx]->fileSize()) {
                idx = i;
            }
        }

        if(idx == -1) {
            return NULL;
        }

        return images[idx];
    }

    ~Folder() { }
};

Folder& max_folder_size(Folder* f, int n) {
    int idx = -1;
    for(int i = 0; i < n; i++) {
        if(idx == -1 || f[i].folderSize() > f[idx].folderSize()) {
            idx = i;
        }
    }
    return f[idx];
}

int main() {
    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
