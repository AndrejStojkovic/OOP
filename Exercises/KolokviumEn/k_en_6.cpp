// En - 6

#include <iostream>
#include <cstring>
using namespace std;

class Camera {
protected:
    char manufacturer[20];
    char model[20];
    int year;
    float resolution;

private:
    void copy_camera(const Camera& other) {
        strcpy(this->manufacturer, other.manufacturer);
        strcpy(this->model, other.model);
        this->year = other.year;
        this->resolution = other.resolution;
    }

public:
    Camera() {
        strcpy(this->manufacturer, "unknown");
        strcpy(this->model, "unknown");
        this->year = 0;
        this->resolution = 0;
    }

    Camera(char* manufacturer, char* model, int year, float resolution) {
        strcpy(this->manufacturer, manufacturer);
        strcpy(this->model, model);
        this->year = year;
        this->resolution = resolution;
    }

    Camera(const Camera& other) {
        copy_camera(other);
    }

    Camera& operator=(const Camera& other) {
        if(this == &other) {
            return *this;
        }

        copy_camera(other);
        return *this;
    }

    friend bool operator<(Camera& a, Camera& b) {
        return a.price() < b.price();
    }

    virtual float price() = 0;
    virtual float rentalPrice(int days) = 0;

    char* getModel() {
        return model;
    }

    ~Camera() { }
};

class PhotoCamera : public Camera {
    bool raw;

public:
    PhotoCamera() : Camera() {
        this->raw = false;
    }

    PhotoCamera(char* manufacturer, char* model, int year, float resolution, bool raw) : Camera(manufacturer, model, year, resolution) {
        this->raw = raw;
    }

    PhotoCamera(const PhotoCamera& other) : Camera(other) {
        this->raw = other.raw;
    }

    PhotoCamera& operator=(const PhotoCamera& other) {
        if(this == &other) {
            return *this;
        }

        Camera::operator=(other);
        this->raw = other.raw;
        return *this;
    }

    float price() {
        float s = 100 + (resolution * 20);
        if(raw) { s += 50; }
        return s;
    }

    float rentalPrice(int days) {
        float s = (price() * 0.01) * days;
        if(days > 7) { s -= (0.2 * s); }
        return s;
    }

    ~PhotoCamera() { }
};

class VideoCamera : public Camera {
    int length;

public:
    VideoCamera() : Camera() {
        this->length = 0;
    }

    VideoCamera(char* manufacturer, char* model, int year, float resolution, int length) : Camera(manufacturer, model, year, resolution) {
        this->length = length;
    }

    VideoCamera(const VideoCamera& other) : Camera(other) {
        this->length = other.length;
    }

    VideoCamera& operator=(const VideoCamera& other) {
        if(this == &other) {
            return *this;
        }

        Camera::operator=(other);
        this->length = other.length;
        return *this;
    }

    float price() {
        float s = (resolution * 80);
        if(length > 3600) { s *= 1.4; }
        return s;
    }

    float rentalPrice(int days) {
        float s = (price() * 0.01) * days;
        if(days > 7) { s -= (0.2 * s); }
        return s;
    }

    ~VideoCamera() { }
};

class FilmCamera : public Camera {
    int fps;

public:
    FilmCamera() : Camera() {
        this->fps = 0;
    }

    FilmCamera(char* manufacturer, char* model, int year, float resolution, int fps) : Camera(manufacturer, model, year, resolution) {
        this->fps = fps;
    }

    FilmCamera(const FilmCamera& other) : Camera(other) {
        this->fps = other.fps;
    }

    FilmCamera& operator=(const FilmCamera& other) {
        if(this == &other) {
            return *this;
        }

        Camera::operator=(other);
        this->fps = other.fps;
        return *this;
    }

    float price() {
        float s = 50000;
        if(fps > 30) {
            int m = fps % 30;
            s += (5000 * m);
        }
        return s;
    }

    float rentalPrice(int days) {
        float s = 500 * days;
        if(fps > 60) { s *= 2; }
        return s;
    }

    ~FilmCamera() { }
};

float production(Camera** c, int n, int days) {
    float s = 0;

    for(int i = 0; i < n; i++) {
        s += c[i]->rentalPrice(days);
    }

    return s;
}

char* mostExpensiveCamera(Camera** c, int n) {
    int idx = -1;

    for(int i = 0; i < n; i++) {
        if(idx == -1 || c[idx]->price() < c[i]->price()) {
            idx = i;
        }
    }

    if(idx == -1) {
        return "error";
    }

    return c[idx]->getModel();
}

int main(int argc, char *argv[])
{
    // Variables for reading input
    char model[20], producer[20];
    int year, length, fps, n;
    float resolution;
    bool raw;

    int t;

    // Array of cameras
    Camera *c [10];

    // Read number of cameras
    cin>>n;

    for(int i = 0; i < n; ++i){

        // Camera type: 1 - Photo, 2 - Video, 3 - Film
        cin>>t;

        if (t==1){
            cin >> producer >> model >> year >> resolution;
            cin >> raw;
            c[i] = new PhotoCamera(producer, model, year, resolution, raw);
        }
        else if (t==2){
            cin >> producer >> model >> year >> resolution;
            cin >> length;
            c[i] = new VideoCamera(producer, model, year, resolution, length);
        }
        else if (t==3){
            cin >> producer >> model >> year >> resolution;
            cin >> fps;
            c[i] = new FilmCamera(producer, model, year, resolution, fps);
        }
    }


    // Production days
    int days;
    cin >> days;


    cout << "Price of production is: " << production(c, n, days) << "\n";
    cout << "Most expensive camera used in production is: " << mostExpensiveCamera(c, n);


    return 0;
}