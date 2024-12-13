#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <deque>
#include<string>
#include <ctime>
#include<functional>
#include<fstream>
using namespace std;
#define str_vprawo SetConsoleTextAttribute(hld,9);cout<< ">>>"; SetConsoleTextAttribute(hld,7); // Для красивого відображення
#define str_vlewo SetConsoleTextAttribute(hld,9);cout<< "<<<"<<endl; SetConsoleTextAttribute(hld,7); // Для красивого відображення
#define Uk SetConsoleOutputCP(1251);SetConsoleCP(1251);
#define Lat SetConsoleOutputCP(437);SetConsoleCP(437);
#define sdwig cout<<"\t\t\t\t\t";
HANDLE hld = GetStdHandle(STD_OUTPUT_HANDLE);
#define endll cout<<endl;

void Uk_Flag(short x, short y); // Y
void Name_Net(); // Y
void static_task(); // Y
void zafarbuy(int color); // Y
void zafarbuy_bazoy(); // Y
void Goto(short x, short y); // Y
void Pause(); // Y
class Date { // Клас для дати 
public:
    int month; int day; int year; 
    Date();
    Date(int _month, int _day, int _year);
    Date(const Date& other);
    bool operator==(Date& other) {
        return (month == other.month) && (day == other.day) && (year == other.year);
    }
    Date GetCurrent_Date();
}; // Y
class Comment {
public:
    string text;
    Date date;
    // Конструктор за замовчуванням КОМЕНТИ
    Comment() :text(), date() {}
    Comment(string _text, Date _date);
    Comment(const Comment& other);
}; // Y
class User { 
public:
    string password;
    Date date_of_birth;
    string gmail;
    string phone_number;
    string login;
    string NAme;
    string country;
    deque<int>storages; // Зберігання користувача
    deque<User*>folowers; // Слідкувачі за користувачем 
    deque<User*>folowed; // Слідкування користувача 
    deque<Comment>comments; // Коментарі користувача 
    deque<User*>likes; // Лайки які маэ користувач 
    deque<int>posts; // Пости 
    deque<int>reposts; // Репости 
    // Конструктор за замовчуванням ДЛЯ КОРИСТУВАЧА
    User() :login(), password(), date_of_birth(),
        gmail(), phone_number(), storages(),
        NAme(), country(), folowers(),
        folowed(), comments(), likes(),
        posts(), reposts() {}
    User(string _login, string _password, Date _date_of_birth, string _gmail, string _phone_number, string _name, string _country);
    User(const User& other);

    void addComment(int id); 
    void addPost();
    void addFriend(User &Friend);// sourse
    void toggleLike(int id); // Перемикання лайків
    void toggleRepost(int id);
    void toggleStorage(int id);
  
    void display_User_Info();
    void display_User_Post_Info(); // Лише пости користувача
    void Global_display_Post_Info(); // Всієї мережі
    void display_Repost_Info();
    void display_Storages_Info();

    void removeFriend(User& Friend);
    void removePost(int id);
}; 

class Post {
public:
    string text;
    string NAme;
    deque<Comment>comments;
    deque<User>likes;
    int id;
    Date date;
    // Конструктор за замовчуванням ПОСТИ
    Post();
    Post(Date _date, string _text, string _name,int id);
    Post(const Post& other);
    static Post& GetPost_by_Id(int Id);
    void display_Comments_Info();
};
// це виходить айді лише для певного юсера


class Social_Network {
public:
    static deque<User>Users_SNetwork;
    static deque<Post>Posts_SNetwork;
    static int id_p; // Айді постів глобальне 
    // Конструктор за замовчуванням
    Social_Network() { }
    static void createNewUser(User user);
    static void createNewPost(Post post);
    static User findUserByLogin();
    static void saveUsersToFile(const deque<User>& users, const string& filename);
    static void savePostsToFile(const deque<Post>& posts, const string& filename);
    static void readUsersFromFile(deque<User>& users, const string& filename);
    static void readPostsFromFile(deque<Post>& posts, const string& filename);
};

deque<User> Social_Network::Users_SNetwork = {}; // Так треба,щоб працювало бо статік 
deque<Post> Social_Network::Posts_SNetwork = {};
int Social_Network::id_p = 0;