#include<iostream>
#include<cstring>
using namespace std;

class UserAlreadyExistsException {
private:
    char *user_name;
public:
    UserAlreadyExistsException(char *user_name){
        this->user_name=new char[strlen(user_name)+1];
        strcpy(this->user_name, user_name);
    }
    void message(){
        cout<<"User with username "<<user_name<<" already exists!"<<endl;
    }
};

class UserNotFoundException {
private:
    char *user;
public:
    UserNotFoundException(char *user){
        this->user=new char[strlen(user)+1];
        strcpy(this->user, user);
    }
    void message(){
        cout<<"User with username "<<user<<" was not found!"<<endl;
    }
};

class FriendsLimitExceededException {
private: int num;
public:
    FriendsLimitExceededException(int num){
        this->num=num;
    }
    void message(){
        cout<<"Can't have more than "<<num<<" friends."<<endl;
    }
};



class User {
private:
    char username[50];
    int age;
    int friends;
    static int limit;
public:
    User(char *username = "", int age = 18) : age(age) {
        strcpy(this->username, username);
        friends = 0;
    }

    friend ostream &operator<<(ostream &os, const User &user) {
        os << "Username: " << user.username << " Age: " << user.age << " # of friends: " << user.friends;
        return os;
    }

    User &operator++() {
            ++friends;
            if (friends > limit){
                --friends;
                throw FriendsLimitExceededException(limit);
            } else
            return *this;
        }

    friend class SocialNetwork;


    static void setLimit(int friends);
};
int User::limit=3;

void User::setLimit(int friends) {
    User::limit=friends;
}

class SocialNetwork {
private:
    User *users;
    int n;
public:
    SocialNetwork() {
        n = 0;
        users = new User[n];
    }

    SocialNetwork &operator+=(User &u) {
        if (!strcmp(u.username, users->username)){
            throw UserAlreadyExistsException(u.username);
        }
        User *tmp = new User[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = users[i];
        }
        tmp[n++] = u;
        delete[] users;
        users = tmp;
        return *this;
    }

    void friendRequest(char *firstUsername, char *secondUsername) {
        int flag=0;
        for (int i = 0; i < n; i++) {
            if (strcmp(users[i].username, firstUsername) == 0) {
                for (int j = 0; j < n; j++) {
                    if (strcmp(users[j].username, secondUsername) == 0) {
                        ++users[i];
                        ++users[j];
                        flag++;
                        return;
                    }
                }
            }
        }
        if (flag==0){
            throw UserNotFoundException(secondUsername);
        }
    }

    friend ostream &operator<<(ostream &os, const SocialNetwork &network) {
        os << "Users: " << endl;
        for (int i=0;i<network.n;i++) {
            os << network. users[i] << endl;
        }
        return os;
    }
};

int main() {
    SocialNetwork sn;
    int n;
    cin >> n;
    for (int i=0;i<n;i++){
        char username[50]; int age;
        cin >> username >> age;
        User u(username, age);
        try{
            sn += u;
        }
        catch (UserAlreadyExistsException u){
            u.message();
        }
    }

    cout << "Registration of users " << endl;
    cout << sn << endl;
    cout << "Friend requests " << endl;

    int friendships;
    cin>>friendships;
    for (int i=0;i<friendships;i++){
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try{
            sn.friendRequest(username1, username2);
        }
        catch (FriendsLimitExceededException e){
            e.message();
        }
        catch (UserNotFoundException k){
            k.message();
        }
    }

    cout << sn << endl;

    cout << "CHANGE STATIC VALUE" << endl;

    int maxFriends;
    cin >> maxFriends;
    cin >> friendships;
    User::setLimit(maxFriends);
    for (int i=0;i<friendships;i++){
        char username1[50], username2[50];
        cin >> username1 >> username2;
        sn.friendRequest(username1, username2);
    }
    cout << sn;
    return 0;
}