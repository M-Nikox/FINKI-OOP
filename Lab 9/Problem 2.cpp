#include <iostream>
#include <cstring>

using namespace std;

class Game{
protected:
    char title[100];
public:
    Game(){
        strcpy(this->title, "NONE");
    }
    Game(char title[100]){
        strcpy(this->title, title);
    }

    virtual void displayInfo(){
        cout<<"Game: "<<title<<endl;
    }

    virtual int complexity() = 0;
};

class BoardGame : public Game{
protected:
    int maxPlayers;
public:
    BoardGame(){
        strcpy(this->title, "NONE");
        this->maxPlayers=0;
    }
    BoardGame(char title[100], int maxPlayers) : Game(title){
        strcpy(this->title, title);
        this->maxPlayers=maxPlayers;
    }

    int complexity() override{
        if (maxPlayers > 6){
            return 10;
        }
        else if (maxPlayers > 3 && maxPlayers < 6){
            return 5;
        }
        else if (maxPlayers < 3){
            return 3;
        }
    }

    void displayInfo(){
        cout<<"Game: "<<title<<endl;
        cout<<"Max players: "<<maxPlayers<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }
};

class CardGame : public Game {
protected:
    int numCards;
public:
    CardGame(){
        strcpy(this->title, "NONE");
        this->numCards=0;
    }
    CardGame(char title[100], int numCards) : Game(title){
        strcpy(this->title, title);
        this->numCards=numCards;
    }

    int complexity() override{
        if (numCards > 20){
            return 10;
        }
        else if (numCards > 10 && numCards < 20){
            return 5;
        }
        else if (numCards < 10){
            return 3;
        }
    }

    void displayInfo(){
        cout<<"Game: "<<title<<endl;
        cout<<"Number of cards: "<<numCards<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }
};

class BoardCardGame : public BoardGame, public CardGame{
private:
    char title_BCG[100];
public:
    BoardCardGame(char title[100], int maxPlayers, int numCards) : CardGame(title, numCards), BoardGame(title, maxPlayers){
        strcpy(this->title_BCG, title);
        this->maxPlayers=maxPlayers;
        this->numCards=numCards;
    }
    int complexity() override{
        return ((CardGame::complexity() + BoardGame::complexity())/2);
    }

    void displayInfo() override{
        cout<<"Game: "<<title_BCG<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }
};

Game *mostComplexCardGame(Game **games, int n){
    int max_index;
    for (int i=0; i<n; i++){
        Game *x = dynamic_cast<CardGame*>(games[i]);
        if (x){
            max_index=i;
            break;
        }
    }

    for (int i=0; i<n-1; i++){
        Game *k = dynamic_cast<CardGame*>(games[i]);
        if (k){
            if (games[max_index]->complexity() < games[i]->complexity()){
                max_index=i;
            }
        } else continue;
    }
    return games[max_index];
}

int main() {
    char title[50];
    int maxPlayers;
    int numCards;
    int n;
    int choice;

    cin>>choice;
    if(choice==1)
    {
        cin>>title;
        BoardCardGame boardCardGame(title, 8, 15);
        boardCardGame.displayInfo();
    }
    else {

        cin >> n;

        Game **g = new Game *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> title >> maxPlayers;

                g[i] = new BoardGame(title, maxPlayers);
            } else {
                cin >> title >> numCards;

                g[i] = new CardGame(title, numCards);
            }

        }

        mostComplexCardGame(g,n)->displayInfo();

    }


    return 0;
}