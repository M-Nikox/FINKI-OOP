#include <iostream>
#include <cstring>

using namespace std;

class NBAPlayer{
protected:
    char * name;
    char teamname[40];
    double avg_points;
    double avg_assists;
    double avg_rebounds;
    void copy(const NBAPlayer & other){
        this->name=new char[strlen(other.name)+1];
        strcpy(this->name, other.name);
        strcpy(this->teamname, other.teamname);
        this->avg_points=other.avg_points;
        this->avg_assists=other.avg_assists;
        this->avg_rebounds=other.avg_rebounds;
    }
public:
    NBAPlayer(){
        this->name = new char [5];
        strcpy(this->name, "NONE");
        strcpy(this->teamname, "NONE");
        this->avg_points=-1.0;
        this->avg_assists=-1.0;
        this->avg_rebounds=-1.0;
    }

    NBAPlayer(char *name, char teamname[40], double avg_points, double avg_assists, double avg_rebounds){
        this->name=new char[strlen(name)+1];
        strcpy(this->name, name);
        strcpy(this->teamname, teamname);
        this->avg_points=avg_points;
        this->avg_assists=avg_assists;
        this->avg_rebounds=avg_rebounds;
    }

    NBAPlayer(const NBAPlayer & other){
        copy(other);
    }

    NBAPlayer & operator=(const NBAPlayer & other){
        if (this == &other){
            return *this;
        } else {
            delete [] name;
            copy(other);
            return *this;
        }
    }

    double rating (){
        return (avg_points * 0.45) + (avg_assists * 0.30) + (avg_rebounds * 0.25);
    }

    void print(){
        cout<<name<<" - "<<teamname<<endl;
        cout<<"Points: "<<avg_points<<endl;
        cout<<"Assists: "<<avg_assists<<endl;
        cout<<"Rebounds: "<<avg_rebounds<<endl;
        cout<<"Rating: "<<rating()<<endl;
    }

    ~NBAPlayer(){
        delete [] name;
    }
};

class AllStarPlayer : public NBAPlayer{
private:
    double as_avg_points;
    double as_avg_assists;
    double as_avg_rebounds;
    void copy(const AllStarPlayer & other){
        NBAPlayer::copy(other);
        this->as_avg_points=other.as_avg_points;
        this->as_avg_assists=other.as_avg_assists;
        this->as_avg_rebounds=other.as_avg_rebounds;
    }
public:
    AllStarPlayer(){
        this->as_avg_points=-1.0;
        this->as_avg_assists=-1.0;
        this->as_avg_rebounds=-1.0;
    }

    AllStarPlayer(const AllStarPlayer & other){
        copy(other);
    }

    AllStarPlayer & operator=(const AllStarPlayer & other){
        if (this == &other){
            return *this;
        } else
            copy(other);
        return *this;
    }

    AllStarPlayer(NBAPlayer &player, double as_avg_points, double as_avg_assists, double as_avg_rebounds) : NBAPlayer(player){
        this->as_avg_points=as_avg_points;
        this->as_avg_assists=as_avg_assists;
        this->as_avg_rebounds=as_avg_rebounds;
    }

    AllStarPlayer(char *name, char *teamname, double avg_points, double avg_assists, double avg_rebounds,
                  double as_avg_points, double as_avg_assists, double as_avg_rebounds) : NBAPlayer(name, teamname, avg_points, avg_assists, avg_rebounds){
        this->as_avg_points=as_avg_points;
        this->as_avg_assists=as_avg_assists;
        this->as_avg_rebounds=as_avg_rebounds;
    }

    double AllStarRating(){
        return (as_avg_points * 0.30) + (as_avg_assists * 0.40) + (as_avg_rebounds * 0.30);
    }

    double rating(){
        return (NBAPlayer::rating() + AllStarRating())/2.0;
    }

    void print(){
        NBAPlayer::print();
        cout<<"All Star Rating: "<<AllStarRating()<<endl;
        cout<<"New Rating: "<<rating()<<endl;
    }

    ~AllStarPlayer(){}

};

int main() {

    char name[50];
    char team[40];
    double points;
    double assists;
    double rebounds;
    double allStarPoints;
    double allStarAssists;
    double allStarRebounds;

    NBAPlayer * players = new NBAPlayer[5];
    AllStarPlayer * asPlayers = new AllStarPlayer[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            players[i] = NBAPlayer(name,team,points,assists,rebounds);
            players[i].print();
        }
    }
    else if (n == 2) {

        for (int i=0; i < 5; ++i){
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            players[i] = NBAPlayer(name,team,points,assists,rebounds);
            asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
        }

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            players[i].print();

        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            asPlayers[i].print();

    }
    else if (n == 3) {

        for (int i=0; i < 5; ++i){
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                         allStarPoints,allStarAssists,allStarRebounds);
        }
        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            asPlayers[i].print();

    }

    delete [] players;
    delete [] asPlayers;
}