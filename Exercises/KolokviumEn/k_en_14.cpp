// En - 14

#include <iostream>
#include <cstring>
using namespace std;

class RatingMissingException { };

class Person {
    char *name;
    int year;

    void copy_person(const Person &other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->year = other.year;
    }

public:
    Person() {
        this->name = new char[10];
        strcpy(this->name, "John Doe");
        this->year = 0;
    }

    Person(char* name, int year) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->year = year;
    }

    Person(const Person& other) {
        copy_person(other);
    }

    Person& operator=(const Person& other) {
        if(this == &other) {
            return *this;
        }
        delete [] name;
        copy_person(other);
        return *this;
    }

    char* getName() {
        return name;
    }

    int getYear() {
        return year;
    }

    ~Person() {
        delete [] name;
    }
};

class Song {
protected:
    char* title;
    Person p[10];
    int n;
    int* ratings;
    int len;

private:
    void copy_song(const Song& other) {
        this->title = new char[strlen(other.title) + 1];
        strcpy(this->title, other.title);
        this->n = other.n;
        for(int i = 0; i < other.n; i++) {
            this->p[i] = other.p[i];
        }
        this->ratings = new int[other.len];
        for(int i = 0; i < other.len; i++) {
            this->ratings[i] = other.ratings[i];
        }
        this->len = other.len;
    }

public:
    Song() {
        this->title = new char[5];
        strcpy(this->title, "name");
        this->n = 0;
        this->ratings = nullptr;
        this->len = 0;
    }

    Song(char* title, Person* p, int n, int* ratings, int len) {
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
        this->n = n;
        for(int i = 0; i < n; i++) {
            this->p[i] = p[i];
        }
        this->ratings = new int[len];
        for(int i = 0; i < len; i++) {
            this->ratings[i] = ratings[i];
        }
        this->len = len;
    }

    Song(const Song& other) {
        copy_song(other);
    }

    Song& operator=(const Song& other) {
        if(this == &other) {
            return *this;
        }
        delete [] title;
        delete [] ratings;
        copy_song(other);
    }

    virtual float getTotalRating() {
        if(len <= 0) {
            throw RatingMissingException();
        }

        float a = 0, b = 11;
        for(int i = 0; i < len; i++) {
            if(ratings[i] > a) {
                a = ratings[i];
            }
            if(ratings[i] < b) {
                b = ratings[i];
            }
        }

        return (a + b) / 2;
    }

    virtual void print() {
        for(int i = 0; i < n; i++) {
            cout << p[i].getName() << " (" << p[i].getYear() << ")";
            if(i != n - 1) {
                cout << ",";
            }
        }
        cout << ":" << title << "\n";
    }

    Person getPerformer(int idx) {
        if(idx < 0 || idx >= n) {
            return Person();
        }

        return p[idx];
    }

    int getN() {
        return n;
    }

    ~Song() {
        delete [] title;
        delete [] ratings;
    }
};

class Movie {
protected:
    char* title;
    int rating;

private:
    void copy_movie(const Movie& other) {
        this->title = new char[strlen(other.title) + 1];
        strcpy(this->title, other.title);
        this->rating = other.rating;
    }

public:
    Movie() {
        this->title = new char[6];
        strcpy(this->title, "title");
        this->rating = 0;
    }

    Movie(char* title, int rating) {
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
        this->rating = rating;
    }

    Movie(const Movie& other) {
        copy_movie(other);
    }

    Movie& operator=(const Movie& other) {
        if(this == &other) {
            return *this;
        }
        delete [] title;
        copy_movie(other);
        return *this;
    }

    float getMoviePopularity() {
        return rating;
    }

    char* getMovieTitle() {
        return title;
    }

    ~Movie() {
        delete [] title;
    }
};

class MovieSong : public Song, public Movie {
    int popularity;

public:
    MovieSong() : Song(), Movie() {
        this->popularity = 0;
    }

    MovieSong(char* song_title, Person* p, int n, int* ratings, int len, char* movie_title, int rating, int popularity) :
    Song(song_title, p, n, ratings, len), Movie(movie_title, rating) {
        this->popularity = popularity;
    }

    MovieSong(const MovieSong& other) : Song(other), Movie(other) {
        this->popularity = other.popularity;
    }

    MovieSong& operator=(const MovieSong& other) {
        if(this == &other) {
            return *this;
        }
        Song::operator=(other);
        Movie::operator=(other);
        this->popularity = other.popularity;
        return *this;
    }

    float getTotalRating() {
        return Song::getTotalRating() * (popularity / getMoviePopularity());
    }

    void print() {
        Song::print();
        cout << "Movie:" << getMovieTitle() << "\n";
    }

    ~MovieSong() { }
};

double averageRating(Song** songs, int n) {
    double s = 0;
    int ct = 0;

    for(int i = 0; i < n; i++) {
        if(dynamic_cast<MovieSong*>(songs[i])) {
            MovieSong ms = *dynamic_cast<MovieSong*>(songs[i]);
            try {
                s += ms.getTotalRating();
            } catch(RatingMissingException& e) {
                s += 5;
            }
            ct++;
        }
    }

    return s / ct;
}

void printSongs(char* performer, Song** songs, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < songs[i]->getN(); j++) {
            if(!strcmp(performer, songs[i]->getPerformer(j).getName())) {
                songs[i]->print();
                break;
            }
        }
    }
}

int main() {

    Person performers[10];
    int year, numberOfPerformers, ratings[20], rating, numberOfRatings, type, popularity, songPopularity;
    char name[40], title[30], perfomer[30], title2[30];

    cin >> type;

    if (type == 1) //test class MovieSong
    {
        cout << "-----TEST MovieSong-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++) {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++) {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> title >> popularity >> songPopularity;


        MovieSong ok(title, performers, numberOfPerformers, ratings, numberOfRatings, title, popularity, songPopularity);
        cout << "Object of class MovieSong is created";

    } else if (type == 2) // function print in song
    {
        cout << "-----TEST print-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }

        Song k(title, performers, numberOfPerformers, ratings, numberOfRatings);
        k.print();

    } else if (type == 3) // function getTotalRating
    {
        cout << "-----TEST getTotalRating-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }

        Song k(title, performers, numberOfPerformers, ratings, numberOfRatings);
        cout << "Total rating: " << k.getTotalRating() << endl;

    } else if (type == 4) //funkcija getTotalRating vo MovieSong
    {
        cout << "-----TEST getTotalRating-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> title >> popularity >> songPopularity;

        MovieSong fp(title, performers, numberOfPerformers, ratings, numberOfRatings, title, popularity, songPopularity);
        cout << "Total rating: " << fp.getTotalRating() << endl;

    } else if (type == 5) //funkcija print vo MovieSong
    {
        cout << "-----TEST print -----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> title2 >> popularity >> songPopularity;

        MovieSong fp(title, performers, numberOfPerformers, ratings, numberOfRatings, title2, popularity, songPopularity);
        fp.print();

    } else if (type == 6) //all classes
    {
        cout << "-----TEST Song and MovieSong-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> title >> popularity >> songPopularity;

        Song *p = new MovieSong(title, performers, numberOfPerformers, ratings, numberOfRatings, title, popularity, songPopularity);
        p->print();
        cout << "Total rating: " << p->getTotalRating() << endl;
        delete p;


    } else if (type == 7) // function average rating
    {
        cout << "-----TEST average rating-----" << endl;
        int k, opt;
        cin >> k;
        Song **pesni = new Song*[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Song 2 MovieSong
            cin >> title >> numberOfPerformers;
            for (int i = 0; i < numberOfPerformers; i++)
            {
                cin >> name >> year;
                performers[i] = Person(name, year);
            }
            cin >> numberOfRatings;
            for (int i = 0; i < numberOfRatings; i++)
            {
                cin >> rating;
                ratings[i] = rating;
            }
            if (opt == 1) {
                pesni[j] = new Song(title, performers, numberOfPerformers, ratings, numberOfRatings);
            } else {
                cin >> title >> popularity >> songPopularity;
                pesni[j] = new MovieSong(title, performers, numberOfPerformers, ratings, numberOfRatings, title, popularity, songPopularity);
            }
        }

        cout << "Average rating of the songs is " << averageRating(pesni, k);
        for (int j = 0; j < k; j++) delete pesni[j];
        delete [] pesni;

    } else if (type == 8) // function print songs
    {
        cout << "-----TEST print songs-----" << endl;
        int k, opt;
        cin >> k;
        Song **pesni = new Song*[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Song 2 MovieSong
            cin >> title >> numberOfPerformers;
            for (int i = 0; i < numberOfPerformers; i++)
            {
                cin >> name >> year;
                performers[i] = Person(name, year);
            }
            cin >> numberOfRatings;
            for (int i = 0; i < numberOfRatings; i++)
            {
                cin >> rating;
                ratings[i] = rating;
            }
            if (opt == 1) {
                pesni[j] = new Song(title, performers, numberOfPerformers, ratings, numberOfRatings);
            } else {
                cin >> title2 >> popularity >> songPopularity;
                pesni[j] = new MovieSong(title, performers, numberOfPerformers, ratings, numberOfRatings, title2, popularity, songPopularity);
            }
        }
        cin >> perfomer;
        cout << "Songs of " << perfomer << " are:" << endl;
        printSongs(perfomer, pesni, k);
        for (int j = 0; j < k; j++) delete pesni[j];
        delete [] pesni;

    }


    return 0;
}
