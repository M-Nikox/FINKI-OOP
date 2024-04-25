#include <iostream>
#include <cstring>

using namespace std;

class InvalidTimeException{
public:
    void print(){
        cout<<"The time is not valid"<<endl;
    }
};

class Race{
protected:
    int year;
    int month;
    float best_time;
    float length;
    char city[40];
public:
    Race(){
        strcpy(this->city,"NONE");
        this->year=0;
        this->month=0;
        this->best_time=0;
        this->length=0;
    }
    Race(char city[40], int year, int month, double best_time, double length) {
        strcpy(this->city, city);
        this->year=year;
        this->month=month;
        this->best_time=best_time;
        this->length=length;
    }

    virtual float heaviness(){
        return best_time/length;
    }

    int getYear() const {
        return year;
    }

    int getMonth() const {
        return month;
    }

    float getBestTime() const {
        return best_time;
    }

    float getLength() const {
        return length;
    }

    const char *getCity() const {
        return city;
    }

};

class CarRace : public Race{
private:
    float *best_times;
    int num_best_times;
    int num_laps;
    static float coef;
public:
    CarRace() : Race(){
        strcpy(this->city,"NONE");
        this->year=0;
        this->month=0;
        this->best_time=0;
        this->length=0;
        this->num_best_times=0;
        this->num_laps=0;
        this->best_times=new float[0];
    }

    CarRace(char city[40], int year, int month, float best_time, float length, const float *best_times, int num_best_times, int num_laps) : Race(city, year, month, best_time, length){
        strcpy(this->city, city);
        this->year=year;
        this->month=month;
        this->best_time=best_time;
        this->length=length;
        this->num_best_times=num_best_times;
        this->num_laps=num_laps;
        this->best_times = new float[num_best_times];
        for (int i=0; i<num_best_times; i++){
            this->best_times[i]=best_times[i];
        }
    }

    CarRace(char city[40], int year, int month, float best_time, float length) : Race(city, year, month, best_time, length){
        strcpy(this->city, city);
        this->year=year;
        this->month=month;
        this->best_time=best_time;
        this->length=length;
    }

    CarRace(Race k, double *best_times, int num_best_times, int num_laps) : Race(k){
        strcpy(this->city, city);
        this->year=year;
        this->month=month;
        this->best_time=best_time;
        this->length=length;
        this->num_best_times=num_best_times;
        this->num_laps=num_laps;
        this->best_times = new float[num_best_times];
        for (int i=0; i<num_best_times; i++){
            this->best_times[i]=best_times[i];
        }
    }

    int setNumberLaps(int n){
        this->num_laps=n;
    }


    float heaviness() override{
        float cur_hv=Race::heaviness();
        float sum=0;
        float avg=0;
        for (int i=0; i<num_best_times; i++){
            sum+=best_times[i];
        }
        avg = sum/num_best_times;
        avg *= coef;
        float curr_heavy = cur_hv + avg;
        if (num_laps > 15){
            return curr_heavy * 1.10;
        } else return curr_heavy;
    }

    CarRace & operator+=(float time){
        if (time < 10){
            throw InvalidTimeException();
        } else {
            float *tmp = new float[num_best_times+1];
            for (int i=0; i<num_best_times; i++){
                tmp[i]=best_times[i];
            }
            tmp[num_best_times]=time;

            delete [] best_times;
            best_times=tmp;
            num_best_times++;
            return *this;
        }
    }

    static void setKoeficient(float coef);
};
float CarRace::coef=0.3;

void CarRace::setKoeficient(float coef) {
    CarRace::coef = coef;
}

ostream &operator<<(ostream &os, Race &race) {
    if (dynamic_cast<CarRace*>(&race)) {
        os << dynamic_cast<CarRace*>(&race)->getCity();
        os << " ";
        os << dynamic_cast<CarRace*>(&race)->getMonth();
        os << ".";
        os << dynamic_cast<CarRace*>(&race)->getYear();
        os << " ";
        os << dynamic_cast<CarRace*>(&race)->heaviness();
        os << endl;
        return os;
    } else
    os << race.getCity() << " " << race.getMonth() << "." << race.getYear() << " " << race.heaviness() << endl;
    return os;
}

int main(){
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int izbor;
    int numberLaps;

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        Race t(city, year, month, bestTime, length);
        cout<<t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        CarRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        cout << mgt;
        CarRace mgt2;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (izbor == 1){
                niza[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje novo najdobro vreme za prvata CarRace
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++){
            CarRace* nn = dynamic_cast<CarRace*>(niza[i]);
            if (nn != 0){
                flag = 0;
                (*nn) += best;
                break;
            }
        }


        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        CarRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float vreme1,vreme2;
        cin>>vreme1>>vreme2;
        try{
            mgt+=vreme1;
            mgt+=vreme2;
        }
        catch(InvalidTimeException e)
        {
            e.print();
        }
        cout<<mgt;
    }

    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (izbor == 1){
                niza[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        CarRace::setKoeficient(0.7);
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }



    return 0;
}