#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include "prototypes.h"



void Pause() {
    zafarbuy(8);
    cout << "Натисніть будь-яку клавішу";
    zafarbuy_bazoy();
    _getch();
}
// Конструктор за замовчуванням
Date::Date() : month(0), day(0), year(0) {}
// Конструктор з параметрами
Date::Date(int _month, int _day, int _year) : month(_month), day(_day), year(_year) {}
// Конструктор копіювання
Date::Date(const Date& other) : month(other.month), day(other.day), year(other.year) {}

Date Date::GetCurrent_Date() {
    Date СurrentData;
    unique_ptr<time_t> t = make_unique<time_t>(time(0));
    tm* localTime = localtime(t.get()); //  tm - вона використовується для зберігання інформації про час, розібрану на різні компоненти(сек,хв,нед,роки,пори року)
    СurrentData.year = localTime->tm_year + 1900; // Рік +1900, бо 1900 іде рахунок
    СurrentData.month = localTime->tm_mon + 1; // місяць +1,бо структура повертає починаючи з 0 
    СurrentData.day = localTime->tm_mday; // Від 1 до 31
    return СurrentData;
}





// Конструктор з параметрами
Comment::Comment(string _text, Date _date) : text(_text), date(_date) {}
// Конструктор копіювання
Comment::Comment(const Comment& other) : text(other.text), date(other.date) {}



Post::Post() :comments(), likes(), date(), text(), NAme(), id(Social_Network::id_p) { Social_Network::id_p++; }
// Конструктор з параметрами
Post::Post(Date _date, string _text, string _name, int _id) :date(_date), text(_text), NAme(_name), id(_id) {}
// Конструктор копіювання
Post::Post(const Post& other) : comments(other.comments), likes(other.likes), date(other.date), text(other.text) {}
Post& Post::GetPost_by_Id(int Id) { // Отримання поста за його ID
    for (auto i = Social_Network::Posts_SNetwork.begin(); i != Social_Network::Posts_SNetwork.end(); i++) { if ((*i).id == Id) { return (*i); } }
    Post post = Post(); return post;
} // HZ

void Post::display_Comments_Info() {
    for (const auto& comment : comments) {
        cout << "\nДата публікації: " << comment.date.day << "/" << comment.date.month << "/" << comment.date.year;
        cout << "\nТекст: " << comment.text << endl;
    }
} // Y
// Конструктор з параметрами
User::User(string _login, string _password, Date _date_of_birth, string _gmail, string _phone_number, string _name, string _country) :
    login(_login), password(_password), date_of_birth(_date_of_birth),
    gmail(_gmail), phone_number(_phone_number),
    NAme(_name), country(_country) {}
// Конструктор копіювання
User::User(const User& other) :
    login(other.login), password(other.password), date_of_birth(other.date_of_birth),
    gmail(other.gmail), phone_number(other.phone_number), storages(other.storages),
    NAme(other.NAme), country(other.country), folowers(other.folowers),
    folowed(other.folowed), comments(other.comments), likes(other.likes),
    posts(other.posts), reposts(other.reposts) {}

void User::addFriend(User& Friend) { // Додавання друга
    bool isFriend = false;
    for (User* follower : folowers) {
        if (follower == &Friend) {
            isFriend = true;
            break;
        }
    }
    for (User* followedUser : folowed) {
        if (followedUser == &Friend) {
            isFriend = true;
            break;
        }
    }
    if (isFriend) { zafarbuy(6); cout << "\nЦей користувач вже у вас у друзях" << endl; zafarbuy_bazoy(); }
    else {
        folowers.push_back(&Friend);
        Friend.folowed.push_back(this);
        folowed.push_back(&Friend);
        Friend.folowers.push_back(this);
        zafarbuy(2); cout << "\nДодано до друзів." << endl; zafarbuy_bazoy();
    }
    cout << folowed.size() << ' ' << folowers.size();
} // Y
void User::addComment(int id) {
    string text;
    Date date;
    date = date.GetCurrent_Date();
    getline(cin, text);
    Comment* newComment = new Comment(text, date);
    Post::GetPost_by_Id(id).comments.push_back(*newComment);
    comments.push_back(*newComment);
}

void User::addPost() { // always ID = 0
    string name;
    string text;
    Date date;
    date = date.GetCurrent_Date();
    cout << "Введіть назву для поста: ";
    getline(cin, name);
    cout << "Введіть текст поста: ";
    getline(cin, text);
    int id = Social_Network::id_p;
    Post* newPost = new Post(date, text, name, id);
    Social_Network::Posts_SNetwork.push_back(*newPost);
    posts.push_back(newPost->id);
    zafarbuy(10); cout << "\nНовий пост додано\n"; zafarbuy_bazoy();
    /* cout << endl << " " << Social_Network::id_p << newPost->text << newPost->NAme << endl << newPost->id;*/
    Social_Network::id_p++;
    /*cout << posts.size() << ' ' << Social_Network::Posts_SNetwork.size();*/
}

void User::toggleLike(int id) { // Додавання лайка у пост і у лайки юсера 
    bool alreadyLiked = false;
    for (auto it = likes.begin(); it != likes.end(); ++it) {
        if (*it == this) { // Видалення лайка, бо користувач вже лайкав його(лайк є у списку)
            alreadyLiked = true;
            likes.erase(it);
            zafarbuy(12); cout << "\nЛайк видалено з посту\n"; zafarbuy_bazoy();
            break;
        }
    }
    if (!alreadyLiked) {
        Post::GetPost_by_Id(id).likes.push_back(*this);
        likes.push_back(this);
        zafarbuy(10); cout << "\nЛайк додано до посту\n"; zafarbuy_bazoy();
    }
} // Y
void User::toggleRepost(int id) {
    bool found = false; // Якщо знайдено репост, то видаляємо його
    for (auto it = reposts.begin(); it != reposts.end(); ++it) {
        if (*it == id) {
            found = true;
            zafarbuy(12); cout << "\nРепост видалено\n";  zafarbuy_bazoy();
            reposts.erase(it);
            break;
        }
    }
    if (!found) {
        Post newRepost(Post::GetPost_by_Id(id));
        newRepost.date.GetCurrent_Date();
        reposts.push_back(id);
        zafarbuy(10); cout << "\nДодано новий репост\n"; zafarbuy_bazoy();
    }
}
void User::toggleStorage(int id) {
    bool found = false; // Якщо знайдено збереження, то видаляємо його
    for (auto it = storages.begin(); it != storages.end(); it++) {
        if (*it == id) {
            storages.erase(it);
            found = true;
            zafarbuy(12); cout << "\nВидалено із збережень\n";  zafarbuy_bazoy();
            break;
        }
    }
    if (!found) {
        Post newStorage(Post::GetPost_by_Id(id));
        newStorage.date.GetCurrent_Date();
        storages.push_back(id);
        zafarbuy(10); cout << "\nДодано до збережень\n"; zafarbuy_bazoy();
    }
}


void User::Global_display_Post_Info() {
    int selected = 1;
    char selection;
    auto iD = Social_Network::Posts_SNetwork.begin(); // За допомогою нього ми переміщаємося,бо static id не буде так працювати
    bool Idfound = false;
    for (auto it = Social_Network::Posts_SNetwork.begin(); it != Social_Network::Posts_SNetwork.end(); ++it) { if (it == iD) { Idfound = true; iD = it; break; } } // Шукаємо чи є такий айді поста у користувача
    if (Idfound) {
        Idfound = false;
        while (true) {
            system("cls");
            static_task();
            cout << (*iD).text; endll

                cout << (*iD).NAme;  endll
                if (selected == 1) { zafarbuy(4); }
            Lat  cout << "\t\t" << (char)3; Uk
                if (selected == 1) { zafarbuy_bazoy(); }
            if (selected == 2) { zafarbuy(10); }
            cout << "\t\t\t" << (*iD).comments.size() << " коментарів";
            if (selected == 2) { zafarbuy_bazoy(); }
            if (selected == 3) { zafarbuy(10); }
            cout << "\t\t\tЗберегти";
            if (selected == 3) { zafarbuy_bazoy(); }
            if (selected == 4) { zafarbuy(10); }
            cout << "\t\tРепост"; endll endll
                if (selected == 4) { zafarbuy_bazoy(); }
            sdwig sdwig cout << "\tДата публікації " << (*iD).date.day << "/" << (*iD).date.month << "/" << (*iD).date.year; endll endll
                if (selected == 5) { zafarbuy(10); }
            cout << "\tПодивитися попередній пост";
            if (selected == 5) { zafarbuy_bazoy(); }
            if (selected == 6) { zafarbuy(10); }
            sdwig cout << "\t\tПодивитися наступний пост"; endll
                if (selected == 6) { zafarbuy_bazoy(); }

            selection = _getch();
            if (selection == 75 && selected > 1) { selected--; }
            else if (selection == 77 && selected < 6) { selected++; }
            else if (selection == 27) { break; } // при нажиманні esc будемо знову на початку 
            else if (selection == 13) {
                switch (selected) {
                case 1:
                    toggleLike((*iD).id);
                    break;
                case 2:
                    (*iD).display_Comments_Info();
                    addComment((*iD).id);
                    break;
                case 3:
                    toggleStorage((*iD).id);
                    break;

                case 4:
                    toggleRepost((*iD).id);
                    break;
                case 5:
                    while (true) {
                        if (iD != Social_Network::Posts_SNetwork.begin()) { iD--; }
                        for (auto it = Social_Network::Posts_SNetwork.begin(); it != Social_Network::Posts_SNetwork.end(); ++it) {
                            if (it == iD) { Idfound = true; iD = it; break; }
                        }
                        if (Idfound) { Idfound = false; break; }
                    }
                    break;
                case 6:
                    while (true) {
                        if (iD != prev(Social_Network::Posts_SNetwork.end())) { iD++; }
                        for (auto it = iD; it != Social_Network::Posts_SNetwork.end(); ++it) {
                            if (it == iD) { Idfound = true; iD = it; break; }
                        }
                        if (Idfound) { Idfound = false; break; }
                    }
                    break;
                }
                Pause();
            }
        }
    }
    if (!Idfound) { zafarbuy(4); cout << "\nНаданий момент немаэ постів\n"; zafarbuy_bazoy(); }
}

void User::display_User_Post_Info() {
    int selected = 1;
    char selection;
    int iD = 0; // За допомогою нього ми переміщаємося,бо static id не буде так працювати
    bool Postsfound = false;
    bool Idfound = false;
    for (auto it = posts.begin(); it != posts.end(); ++it) { if (*it == iD) { Postsfound = true; iD = *it; break; } } // Шукаємо чи є такий айді поста у користувача
    if (Postsfound) {
        while (true) {
            system("cls");
            static_task();
            sdwig cout << Post::GetPost_by_Id(iD).NAme;  endll
                cout << Post::GetPost_by_Id(iD).text; endll
                if (selected == 1) { zafarbuy(4); }
            Lat  cout << "\t\t" << (char)3; Uk
                if (selected == 1) { zafarbuy_bazoy(); }
            if (selected == 2) { zafarbuy(10); }
            cout << "\t\t\t" << Post::GetPost_by_Id(iD).comments.size() << " коментарів";
            if (selected == 2) { zafarbuy_bazoy(); }
            if (selected == 3) { zafarbuy(10); }
            cout << "\t\t\tЗберегти";
            if (selected == 3) { zafarbuy_bazoy(); }
            if (selected == 4) { zafarbuy(10); }
            cout << "\t\tРепост"; endll endll
                if (selected == 4) { zafarbuy_bazoy(); }
            sdwig sdwig cout << "\tДата публікації " << Post::GetPost_by_Id(iD).date.day << "/" << Post::GetPost_by_Id(iD).date.month << "/" << Post::GetPost_by_Id(iD).date.year; endll endll
                if (selected == 5) { zafarbuy(10); }
            cout << "\tПодивитися попередній пост";
            if (selected == 5) { zafarbuy_bazoy(); }
            if (selected == 6) { zafarbuy(10); }
            sdwig cout << "\t\tПодивитися наступний пост"; endll
                if (selected == 6) { zafarbuy_bazoy(); }

            selection = _getch();
            if (selection == 75 && selected > 1) { selected--; }
            else if (selection == 77 && selected < 6) { selected++; }
            else if (selection == 27) { break; } // при нажиманні esc будемо знову на початку 
            else if (selection == 13) {
                switch (selected) {
                case 1:
                    User::toggleLike(iD);
                    break;
                case 2:
                    Post::GetPost_by_Id(iD).display_Comments_Info();
                    addComment(iD);
                    break;
                case 3:
                    User::toggleStorage(iD);
                    break;
                case 4:
                    User::toggleRepost(iD);
                    break;
                case 5:
                    while (true) {
                        if (iD == 0) { zafarbuy(2); cout << "\nЦе перший пост користувача, далі нікуди\n"; zafarbuy_bazoy(); break; }
                        iD--;
                        for (auto it = posts.begin(); it != posts.end(); ++it) {
                            if (*it == iD) { Idfound = true; iD = *it; break; }
                        }
                        if (Idfound) { Idfound = false; break; }
                    }
                    break;
                case 6:
                    while (true) {
                        if (iD == Social_Network::id_p) { zafarbuy(2); cout << "\nЦе останній пост користувача\n"; zafarbuy_bazoy(); break; }
                        iD++;
                        for (auto it = posts.begin(); it != posts.end(); ++it) {
                            if (*it == iD) { Idfound = true; iD = *it; break; }
                        }
                        if (Idfound) { Idfound = false; break; }
                    }
                    break;
                }
                Pause();
            }
        }
    }
    if (!Postsfound) { zafarbuy(4); cout << "\nУ користувача немає постів\n"; zafarbuy_bazoy(); }
}

void User::display_User_Info() {
    Date date;
    date = date.GetCurrent_Date();
    cout << "Користувач: " << NAme << " із " << country << endl;
    cout << "Дата регестрації: " << date.day << "/" << date.month << "/" << date.year << endl;
    cout << "Дата народження: " << date_of_birth.day << "/" << date_of_birth.month << "/" << date_of_birth.year << endl;
    cout << "Електронна пошта: " << gmail << endl;
    cout << "Номер телефону: " << phone_number << endl;

}

void User::display_Repost_Info() { // Виведення інформації про репостu
    int selected = 1;
    char selection;
    int iD = 0; // За допомогою нього ми переміщаємося,бо static id не буде так працювати
    bool Postsfound = false;
    bool Idfound = false;
    for (auto it = reposts.begin(); it != reposts.end(); ++it) { if (*it == iD) { Postsfound = true; iD = *it; break; } } // Шукаємо чи є такий айді поста у користувача
    if (Postsfound) {
        while (true) {
            system("cls");
            static_task();
            sdwig cout << Post::GetPost_by_Id(iD).NAme;  endll
                cout << Post::GetPost_by_Id(iD).text; endll
                if (selected == 1) { zafarbuy(4); }
            Lat  cout << "\t\t" << Post::GetPost_by_Id(iD).likes.size() << ' ' << (char)3; Uk
                if (selected == 1) { zafarbuy_bazoy(); }
            if (selected == 2) { zafarbuy(10); }
            cout << "\t\t\t" << Post::GetPost_by_Id(iD).comments.size() << " коментарів";
            if (selected == 2) { zafarbuy_bazoy(); }
            if (selected == 3) { zafarbuy(10); }
            cout << "\t\t\tЗберегти";
            if (selected == 3) { zafarbuy_bazoy(); }
            if (selected == 4) { zafarbuy(10); }
            cout << "\t\tРепост"; endll endll
                if (selected == 4) { zafarbuy_bazoy(); }
            sdwig sdwig cout << "\tДата публікації " << Post::GetPost_by_Id(iD).date.day << "/" << Post::GetPost_by_Id(iD).date.month << "/" << Post::GetPost_by_Id(iD).date.year; endll endll
                if (selected == 5) { zafarbuy(10); }
            cout << "\tПодивитися попередній репост";
            if (selected == 5) { zafarbuy_bazoy(); }
            if (selected == 6) { zafarbuy(10); }
            sdwig cout << "\t\tПодивитися наступний репост"; endll
                if (selected == 6) { zafarbuy_bazoy(); }

            selection = _getch();
            if (selection == 75 && selected > 1) { selected--; }
            else if (selection == 77 && selected < 6) { selected++; }
            else if (selection == 27) { break; } // при нажиманні esc будемо знову на початку 
            else if (selection == 13) {
                switch (selected) {
                case 1:
                    User::toggleLike(iD);
                    break;
                case 2:
                    Post::GetPost_by_Id(iD).display_Comments_Info();
                    addComment(iD);
                    break;
                case 3:
                    User::toggleStorage(iD);
                    break;

                case 4:
                    User::toggleRepost(iD);
                    break;
                case 5:
                    while (true) {
                        if (iD == 0) { zafarbuy(2); cout << "\nЦе перший репост користувача, далі нікуди\n"; zafarbuy_bazoy(); break; }
                        iD--;
                        for (auto it = reposts.begin(); it != reposts.end(); ++it) {
                            if (*it == iD) { Idfound = true; iD = *it; break; }
                        }
                        if (Idfound) { Idfound = false; break; }
                    }
                    break;
                case 6:
                    while (true) {
                        if (iD == Social_Network::id_p) { zafarbuy(2); cout << "\nЦе останній репост користувача\n"; zafarbuy_bazoy(); break; }
                        iD++;
                        for (auto it = reposts.begin(); it != reposts.end(); ++it) {
                            if (*it == iD) { Idfound = true; iD = *it; break; }
                        }
                        if (Idfound) { Idfound = false; break; }
                    }
                    break;
                }
                Pause();
            }
        }
    }
    if (!Postsfound) { zafarbuy(4); cout << "\nУ користувача немає репостів\n"; zafarbuy_bazoy(); }
}

void User::display_Storages_Info() {
    int selected = 1;
    char selection;
    int iD = 0; // За допомогою нього ми переміщаємося,бо static id не буде так працювати
    bool Postsfound = false;
    bool Idfound = false;
    for (auto it = storages.begin(); it != storages.end(); ++it) { if (*it == iD) { Postsfound = true; iD = *it; break; } } // Шукаємо чи є такий айді поста у користувача
    if (Postsfound) {
        while (true) {
            system("cls");
            static_task();
            sdwig cout << Post::GetPost_by_Id(iD).NAme;  endll
                cout << Post::GetPost_by_Id(iD).text; endll
                if (selected == 1) { zafarbuy(4); }
            Lat  cout << "\t\t" << Post::GetPost_by_Id(iD).likes.size() << ' ' << (char)3; Uk
                if (selected == 1) { zafarbuy_bazoy(); }
            if (selected == 2) { zafarbuy(10); }
            cout << "\t\t\t" << Post::GetPost_by_Id(iD).comments.size() << " коментарів";
            if (selected == 2) { zafarbuy_bazoy(); }
            if (selected == 3) { zafarbuy(10); }
            cout << "\t\t\tЗберегти";
            if (selected == 3) { zafarbuy_bazoy(); }
            if (selected == 4) { zafarbuy(10); }
            cout << "\t\tРепост"; endll endll
                if (selected == 4) { zafarbuy_bazoy(); }
            sdwig sdwig cout << "\tДата публікації " << Post::GetPost_by_Id(iD).date.day << "/" << Post::GetPost_by_Id(iD).date.month << "/" << Post::GetPost_by_Id(iD).date.year; endll endll
                if (selected == 5) { zafarbuy(10); }
            cout << "\tПодивитися попередній пост";
            if (selected == 5) { zafarbuy_bazoy(); }
            if (selected == 6) { zafarbuy(10); }
            sdwig cout << "\t\tПодивитися наступний пост"; endll
                if (selected == 6) { zafarbuy_bazoy(); }

            selection = _getch();
            if (selection == 75 && selected > 1) { selected--; }
            else if (selection == 77 && selected < 6) { selected++; }
            else if (selection == 27) { break; } // при нажиманні esc будемо знову на початку 
            else if (selection == 13) {
                switch (selected) {
                case 1:
                    toggleLike(iD);
                    break;
                case 2:
                    Post::GetPost_by_Id(iD).display_Comments_Info();
                    addComment(iD);
                    break;
                case 3:
                    toggleStorage(iD);
                    break;

                case 4:
                    toggleRepost(iD);
                    break;
                case 5:
                    while (true) {
                        if (iD == 0) { zafarbuy(2); cout << "\nЦе останній пост користувача, далі нікуди\n"; zafarbuy_bazoy(); break; }
                        iD--;
                        for (auto it = storages.begin(); it != storages.end(); ++it) {
                            if (*it == iD) { Idfound = true; iD = *it; break; }
                        }
                        if (Idfound) { Idfound = false; break; }
                    }
                    break;
                case 6:
                    while (true) {
                        if (iD == Social_Network::id_p) { zafarbuy(2); cout << "\nЦе останній збережений пост користувача\n"; zafarbuy_bazoy(); break; }
                        iD++;
                        for (auto it = storages.begin(); it != storages.end(); ++it) {
                            if (*it == iD) { Idfound = true; iD = *it; break; }
                        }
                        if (Idfound) { Idfound = false; break; }
                    }
                    break;
                }
                Pause();
            }
        }
    }
    if (!Postsfound) { zafarbuy(4); cout << "\nУ користувача немає збережених відео\n"; zafarbuy_bazoy(); }
}


void User::removeFriend(User& Friend) {
    bool isFriend = false;
    if (isFriend) { cout << "\nЦей користувач " << endl; }
    for (auto it = folowers.begin(); it != folowers.end(); ++it) {
        if (*it == &Friend) {
            folowers.erase(it); // у newUser видалити читача
            isFriend = true;
            break;
        }
    }
    for (auto it = Friend.folowed.begin(); it != Friend.folowed.end(); ++it) {
        if (*it == this) {
            Friend.folowed.erase(it);
            break;
        }
    }
    for (auto it = folowed.begin(); it != folowed.end(); ++it) {
        if (*it == &Friend) { // у newUser видалити за тим за ким слідкує він
            folowed.erase(it);
            isFriend = true;
            break;
        }
    }
    for (auto it = Friend.folowers.begin(); it != Friend.folowers.end(); ++it) {
        if (*it == this) {
            Friend.folowers.erase(it);
            break;
        }
    }

    if (isFriend == true) {
        zafarbuy(2); cout << "\nВидалено із друзів" << endl; zafarbuy_bazoy();
    }
    else {
        zafarbuy(6); cout << "\nЦей користувач не є вашим другом." << endl; zafarbuy_bazoy();
    }
}
void User::removePost(int id) { // Знаходження поста у списку користувача і його видалення
    bool found = false;
    for (auto it = posts.begin(); it != posts.end(); ++it)
    {
        if (*it == id) {
            posts.erase(it);
            found = true;
            zafarbuy(14); cout << "\nПост видалено\n"; zafarbuy_bazoy();
            break;
        }
    }
    if (!found) {
        zafarbuy(6); cout << "\nПоста з таким айді не знайдено\n"; zafarbuy_bazoy();
    }
}




//Конструктор копіювання
void Social_Network::createNewUser(User user) {
    Users_SNetwork.push_back(user);
}
User Social_Network::findUserByLogin() { // Для пошуку користувача за ім'ям у мережі 
    string searching_login; endll
        getline(cin, searching_login);
    for (User& user : Users_SNetwork) {
        if (user.login == searching_login) {
            return user;
        }
    }// Y
    return User(); // Користувача не знайдено у мережі
}
void Social_Network::saveUsersToFile(const deque<User>& users, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        char* str = new char[100];
        int u_size = users.size();
        _itoa(u_size, str, 10);
        file.write(str, 100);
        for (const User& user : users) {
            char* str = new char[100];
            file.write(user.login.c_str(), 100);
            file.write(user.password.c_str(), 100);
            _itoa(user.date_of_birth.month, str, 10);
            file.write(str, 100);
            _itoa(user.date_of_birth.day, str, 10);
            file.write(str, 100);
            _itoa(user.date_of_birth.year, str, 10);
            file.write(str, 100);
            file.write(user.gmail.c_str(), 100);
            file.write(user.phone_number.c_str(), 100);
            file.write(user.NAme.c_str(), 100);
            file.write(user.country.c_str(), 100);

            int s_size = user.storages.size();
            _itoa(s_size, str, 10);
            file.write(str, 100);
            for (auto j = user.storages.begin(); j != user.storages.end(); ++j)
            {
                int stor = *j;
                _itoa(stor, str, 10);
                file.write(str, 100);
            }

            int fo_size = user.folowers.size();
            _itoa(fo_size, str, 10);
            file.write(str, 100);
            for (auto jj = user.folowers.begin(); jj != user.folowers.begin(); ++jj)
            {
                file.write((*jj)->login.c_str(), 100);

            }

            int f_size = user.folowed.size();
            _itoa(f_size, str, 10);
            file.write(str, 100);
            for (auto jjj = user.folowed.begin(); jjj != user.folowed.begin(); ++jjj)
            {
                file.write((*jjj)->login.c_str(), 100);

            }

            int com_s = user.comments.size();
            _itoa(com_s, str, 10);
            file.write(str, 100);
            for (auto k = user.comments.begin(); k != user.comments.end(); ++k)
            {
                file.write(k->text.c_str(), 100);

                _itoa(k->date.month, str, 10);
                file.write(str, 100);
                _itoa(k->date.day, str, 10);
                file.write(str, 100);
                _itoa(k->date.year, str, 10);
                file.write(str, 100);
            }

            int l_size = user.likes.size();
            _itoa(l_size, str, 10);
            file.write(str, 100);
            for (auto i = user.likes.begin(); i != user.likes.begin(); ++i)
            {
                file.write((*i)->login.c_str(), 100);

            }

            int p_size = user.posts.size();
            _itoa(p_size, str, 10);
            file.write(str, 100);
            for (auto j = user.posts.begin(); j != user.posts.end(); ++j)
            {
                int post = *j;
                _itoa(post, str, 10);
                file.write(str, 100);
            }

            int r_size = user.reposts.size();
            _itoa(r_size, str, 10);
            file.write(str, 100);
            for (auto j = user.reposts.begin(); j != user.reposts.end(); ++j)
            {
                int repost = *j;
                _itoa(repost, str, 10);
                file.write(str, 100);
            }

        }
        file.close();
        cout << "Користувачі успішно збережені у файл\n";
    }
    else {
        cout << "Не вдалося відкрити файл для збереження користувачів\n";
    }
}
void Social_Network::savePostsToFile(const deque<Post>& posts, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        char* str = new char[100];
        int p_size = posts.size();
        _itoa(p_size, str, 10);
        file.write(str, 100);
        for (const Post& post : posts) {
            char* str = new char[100];
            _itoa(post.id, str, 10);
            file.write(str, 100);
            file.write(post.NAme.c_str(), 100);
            file.write(post.text.c_str(), 100);
            _itoa(post.date.month, str, 10);
            file.write(str, 100);
            _itoa(post.date.day, str, 10);
            file.write(str, 100);
            _itoa(post.date.year, str, 10);
            file.write(str, 100);

            _itoa(post.comments.size(), str, 10);
            file.write(str, 100);
            for (const Comment& comment : post.comments) {
                file.write(comment.text.c_str(), 100);
                _itoa(comment.date.month, str, 10);
                file.write(str, 100);
                _itoa(comment.date.day, str, 10);
                file.write(str, 100);
                _itoa(comment.date.year, str, 10);
                file.write(str, 100);
            }
            _itoa(post.likes.size(), str, 10);
            file.write(str, 100);
            for (const User& like : post.likes) {
                file.write(like.login.c_str(), 100);
            }
        }
    }
    else {
        cout << "Не вдалося відкрити файл для збереження постів\n";
    }
}

void Social_Network::readUsersFromFile(deque<User>& users, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        User user = User();
        char* str = new char[100];
        file.read(str, 100);
        int users_size = atoi(str);
        for (int i = 0; i < users_size; i++)
        {
            char* str = new char[100];
            User user = User();
            file.read(str, 100);
            user.login = str;
            file.read(str, 100);
            user.password = str;
            file.read(str, 100);
            int s = atoi(str);
            user.date_of_birth.month = s;
            file.read(str, 100);
            s = atoi(str);
            user.date_of_birth.day = s;
            file.read(str, 100);
            s = atoi(str);
            user.date_of_birth.year = s;
            file.read(str, 100);
            user.gmail = str;
            file.read(str, 100);
            user.phone_number = str;
            file.read(str, 100);
            user.NAme = str;
            file.read(str, 100);
            user.country = str;
            file.read(str, 100);
            int size_storages = atoi(str);
            for (int i = 0; i < size_storages; i++)
            {
                file.read(str, 100);
                int storage_posta_id = atoi(str);
                user.storages.push_back(storage_posta_id);
            }
            file.read(str, 100);
            int folower_size = atoi(str);
            for (int i = 0; i < folower_size; i++)
            {
                User* folower = new User();
                file.read(str, 100);
                folower->login = str;
                user.folowers.push_back(folower);
            }
            file.read(str, 100);
            int folowed_size = atoi(str);
            for (int i = 0; i < folowed_size; i++)
            {
                User* folowed = new User();
                file.read(str, 100);
                folowed->login = str;
                user.folowed.push_back(folowed);
            }
            file.read(str, 100);
            int coments_size = atoi(str);
            for (int i = 0; i < coments_size; i++)
            {
                Comment com = Comment();
                file.read(str, 100);
                com.text = str;
                s = atoi(str);
                com.date.month = s;
                file.read(str, 100);
                s = atoi(str);
                com.date.day = s;
                file.read(str, 100);
                s = atoi(str); 
                com.date.year = s;
                user.comments.push_back(com);
            }
            file.read(str, 100);
            int likes_size = atoi(str);
            for (int i = 0; i < likes_size; i++)
            {
                User* like = new User();
                file.read(str, 100);
                like->login.push_back(*str);
                user.likes.push_back(like);
            }
            file.read(str, 100);
            int posts_size = atoi(str);
            for (int i = 0; i < posts_size; i++)
            {
                file.read(str, 100);
                int posta_id = atoi(str);
                user.posts.push_back(posta_id);
            }
            file.read(str, 100);
            int size_reposts = atoi(str);
            for (int i = 0; i < size_reposts; i++)
            {
                file.read(str, 100);
                int reposts_ce_posta_id = atoi(str);
                user.reposts.push_back(reposts_ce_posta_id);
            }
            Social_Network::Users_SNetwork.push_back(user);
        }
        file.close();
        cout << "Користувачі успішно завантажені з файлу\n";
    }
    else {
        cout << "Не вдалося відкрити файл для читання користувачів\n";
    }
}

void Social_Network::readPostsFromFile(deque<Post>& posts, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        char* str = new char[100];
        file.read(str, 100);
        int size_p = atoi(str);
        for (int i = 0; i < size_p; i++)
        {
            char* str = new char[100];
            Post post = Post();
            file.read(str, 100);
            int s = atoi(str);
            post.id = s;
            file.read(str, 100);
            post.NAme = str;
            file.read(str, 100);
            post.text = str;
            file.read(str, 100);
            s = atoi(str);
            post.date.month = s;
            file.read(str, 100);
            s = atoi(str);
            post.date.day = s;
            file.read(str, 100);
            s = atoi(str);
            post.date.year = s;
            file.read(str, 100);
            int com_size = atoi(str);
            for (int i = 0; i < com_size; i++)
            {
                Comment c = Comment();
                file.read(str, 100);
                c.text = str;
                file.read(str, 100);
                s = atoi(str);
                c.date.month = s;
                file.read(str, 100);
                s = atoi(str);
                c.date.day = s;
                file.read(str, 100);
                s = atoi(str);
                c.date.year = s;
                post.comments.push_back(c);
            }
            file.read(str, 100);
            int likes_size = atoi(str);
            for (int i = 0; i < likes_size; i++)
            {
                User* like = new User();
                file.read(str, 100);
                like->login = str;
                post.likes.push_back(*like);
            }
            Social_Network::Posts_SNetwork.push_back(post);
        }
        file.close();
        cout << "Пости успішно завантажені з файлу\n";
        
    }
    else {
        cout << "Не вдалося відкрити файл для читання постів\n";
    }
}