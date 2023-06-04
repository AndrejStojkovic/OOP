// En - 18

#include <iostream>
#include <cstring>
using namespace std;

class ExistingPodcast {
public:
    void message() {
        cout << "The podcast is already in the collection\n";
    }
};

class Podcast {
protected:
    char name[100];
    char url[1000];
    float price;
    int discount;

    void copy_podcast(const Podcast& other) {
        strcpy(this->name, other.name);
        strcpy(this->url, other.url);
        this->price = other.price;
        this->discount = other.discount;
    }

public:
    Podcast() {
        strcpy(this->name, "name");
        strcpy(this->url, "url");
        this->price = 0;
        this->discount = 0;
    }

    Podcast(char* name, char* url, float price, int discount) {
        strcpy(this->name, name);
        strcpy(this->url, url);
        this->price = price;
        this->discount = discount;
    }

    Podcast(const Podcast& other) {
        copy_podcast(other);
    }

    Podcast& operator=(const Podcast& other) {
        if(this == &other) {
            return *this;
        }
        copy_podcast(other);
        return *this;
    }

    bool operator==(const Podcast& other) {
        return !strcmp(this->url, other.url);
    }

    friend ostream& operator<<(ostream& out, Podcast& g) {
        out << "Podcast: " << g.name << "\n";
        out << "URL: " << g.url << "\n";
        out << "regular price: $" << g.price;
        if(g.discount > 0) out << ", bought on discount";
        return out;
    }

    friend istream& operator>>(istream& in, Podcast& g) {
        in.get();
        in.getline(g.name, 100);
        in.getline(g.url, 1000);
        in >> g.price >> g.discount;
        return in;
    }

    virtual float get_price() {
        return discount > 0 ? price - (price * (discount / 100.0)) : price;
    }

    ~Podcast() { }
};

class StreamingPodcast : public Podcast {
    float fee;
    int month;
    int year;

    void copy_stream(const StreamingPodcast& other) {
        this->fee = other.fee;
        this->month = other.month;
        this->year = other.year;
    }

public:
    StreamingPodcast() : Podcast() {
        this->fee = 0;
        this->month = this->year = 0;
    }

    StreamingPodcast(char* name, char* url, float price, int discount, float fee, int month, int year) : Podcast(name, url, price, discount) {
        this->fee = fee;
        this->month = month;
        this->year = year;
    }

    StreamingPodcast(const StreamingPodcast& other) : Podcast(other) {
        copy_stream(other);
    }

    StreamingPodcast& operator=(const StreamingPodcast& other) {
        if(this == &other) {
            return *this;
        }
        copy_stream(other);
        return *this;
    }

    friend ostream& operator<<(ostream& out, StreamingPodcast& g) {
        out << *dynamic_cast<Podcast*>(&g);
        out << ", monthly fee: $" << g.fee << ", purchased: " << g.month << "-" << g.year;
        return out;
    }

    friend istream& operator>>(istream& in, StreamingPodcast& g) {
        in.get();
        in.getline(g.name, 100);
        in.getline(g.url, 1000);
        in >> g.price >> g.discount >> g.fee >> g.month >> g.year;
        return in;
    }

    virtual float get_price() {
        float p = Podcast::get_price();

        int months = 0;
        if (year < 2018){
            months = (12 - this->month) + (2017 - year) * 12 + 5;
        } else {
            months = 5 - this->month;
        }

        p += months * fee;
        return p;
    }

    ~StreamingPodcast() { }
};

class Playlist {
    char name[100];
    Podcast** arr;
    int n;

    void copy_playlist(const Playlist& other) {
        strcpy(this->name, other.name);
        this->arr = new Podcast*[other.n];
        for(int i = 0; i < other.n; i++) {
            this->arr[i] = other.arr[i];
        }
        this->n = other.n;
    }

public:
    Playlist() {
        strcpy(this->name, "name");
        this->arr = nullptr;
        this->n = 0;
    }

    Playlist(char* name) {
        strcpy(this->name, name);
        this->arr = nullptr;
        this->n = 0;
    }

    Playlist(const Playlist& other) {
        copy_playlist(other);
    }

    Playlist& operator=(const Playlist& other) {
        if(this == &other) {
            return *this;
        }
        delete [] arr;
        copy_playlist(other);
        return *this;
    }

    Playlist& operator+=(Podcast& pod) {
        for(int i = 0; i < n; i++) {
            if(*arr[i] == pod) {
                throw ExistingPodcast();
            }
        }

        Podcast** tmp = new Podcast*[n + 1];
        for(int i = 0; i < n; i++) {
            tmp[i] = this->arr[i];
        }

        StreamingPodcast* str = dynamic_cast<StreamingPodcast*>(&pod);

        if(str) {
            tmp[n] = new StreamingPodcast(*str);
        } else {
            tmp[n] = new Podcast(pod);
        }

        delete [] arr;
        this->arr = tmp;
        n++;

        return *this;
    }

    friend ostream& operator<<(ostream& out, Playlist& p) {
        out << "\nPlaylist: " << p.name << "\n";
        for(int i = 0; i < p.n; i++) {
            if(dynamic_cast<StreamingPodcast*>(p.arr[i])) {
                out << *dynamic_cast<StreamingPodcast*>(p.arr[i]);
            } else {
                out << *p.arr[i];
            }
            out << "\n";
        }
        out << "\n";
        return out;
    }

    float total_spent() {
        float s = 0;
        for(int i = 0; i < n; i++) {
            s += arr[i]->get_price();
        }
        return s;
    }

    ~Playlist() {
        delete [] arr;
    }
};

int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Podcast
    char podcast_name[100];
    char podcast_url[1000];
    float podcast_price;
    int podcast_discount;

    // for StreamingPodcast
    float sub_podcast_monthly_fee;
    int sub_podcast_month, sub_podcast_year;

    // for Playlist
    char name[100];
    int num_podcasts_in_playlist;

    if (test_case_num == 1){
        cout<<"Testing class Podcast and operator&lt;&lt; for Podcast"<<std::endl;
        cin.get();
        cin.getline(podcast_name,100);
        cin.getline(podcast_url, 1000);
        //cin.get();
        cin>>podcast_price>>podcast_discount;

        Podcast p(podcast_name, podcast_url, podcast_price, podcast_discount);

        cout<<p;
    }
    else if (test_case_num == 2){
        cout<<"Testing class StreamingPodcast and operator&lt;&lt; for StreamingPodcast"<<std::endl;
        cin.get();
        cin.getline(podcast_name,100);
        cin.getline(podcast_url, 1000);
        //cin.get();
        cin>>podcast_price>>podcast_discount;

        cin>>sub_podcast_monthly_fee;
        cin>>sub_podcast_month>>sub_podcast_year;

        StreamingPodcast sp(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
        cout<<sp;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator&gt;&gt; for Podcast"<<std::endl;
        Podcast p;

        cin>>p;

        cout<<p;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator&gt;&gt; for StreamingPodcast"<<std::endl;
        StreamingPodcast sp;

        cin>>sp;

        cout<<sp;
    }
    else if (test_case_num == 5){
        cout<<"Testing class Playlist and operator+= for Playlist"<<std::endl;
        cin.get();
        cin.getline(name,100);
        Playlist u(name);

        int num_user_podcasts;
        int podcast_type;
        cin >>num_user_podcasts;

        try {

            for (int i=0; i<num_user_podcasts; ++i){

                cin >> podcast_type;

                Podcast *g;
                // 1 - Game, 2 - SubscriptionGame
                if (podcast_type == 1){
                    cin.get();
                    cin.getline(podcast_name, 100);
                    cin.getline(podcast_url, 1000);

                    cin>>podcast_price>>podcast_discount;
                    g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
                }
                else if (podcast_type == 2){
                    cin.get();
                    cin.getline(podcast_name, 100);
                    cin.getline(podcast_url, 1000);

                    cin>>podcast_price>>podcast_discount;

                    cin>>sub_podcast_monthly_fee;
                    cin>>sub_podcast_month>>sub_podcast_year;
                    g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
                }

                //cout<<(*g);

                try {
                    u+=(*g);
                } catch(ExistingPodcast& e) {
                    e.message();
                }
            }
        }catch(ExistingPodcast &ex){
            ex.message();
        }

        cout<<u;

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingPodcast for Playlist"<<std::endl;
        cin.get();
        cin.getline(name,100);
        Playlist u(name);

        int num_podcasts_in_playlist;
        int podcast_type;
        cin >>num_podcasts_in_playlist;

        for (int i=0; i<num_podcasts_in_playlist; ++i){

            cin >> podcast_type;

            Podcast *g;
            // 1 - Game, 2 - SubscriptionGame
            if (podcast_type == 1){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;
                g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
            }
            else if (podcast_type == 2){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;

                cin>>sub_podcast_monthly_fee;
                cin>>sub_podcast_month>>sub_podcast_year;
                g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingPodcast &ex){
                ex.message();
            }
        }

        cout<<u;
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for Playlist"<<std::endl;
        cin.get();
        cin.getline(name,100);
        Playlist u(name);

        int num_podcasts_in_playlist;
        int podcast_type;
        cin >>num_podcasts_in_playlist;

        for (int i=0; i<num_podcasts_in_playlist; ++i){

            cin >> podcast_type;

            Podcast *g;
            // 1 - Game, 2 - SubscriptionGame
            if (podcast_type == 1){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;
                g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
            }
            else if (podcast_type == 2){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;

                cin>>sub_podcast_monthly_fee;
                cin>>sub_podcast_month>>sub_podcast_year;
                g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingPodcast &ex){
                ex.message();
            }
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}