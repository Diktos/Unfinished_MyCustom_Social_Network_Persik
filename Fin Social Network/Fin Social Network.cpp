#include"clases.h"

void zafarbuy(int color) {
    SetConsoleTextAttribute(hld, color);
}
void zafarbuy_bazoy() {
    SetConsoleTextAttribute(hld, 7);
}
void Goto(short x, short y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x,y });
}
void Uk_Flag(short x, short y) { // Вивід прапора 
    Lat Goto(x, y); for (int j = 0; j < 8; j++) { zafarbuy(1); cout << (char)219; zafarbuy_bazoy(); }endll;
    Goto(x, ++y); for (int j = 0; j < 8; j++) { zafarbuy(6); cout << (char)219; zafarbuy_bazoy(); }endll Uk
}
void Name_Net() {
    Goto(58, 0);
    zafarbuy(12); cout << "Pers"; zafarbuy_bazoy();
    Goto(57, 1); zafarbuy(10); cout << "Network"; zafarbuy_bazoy();
}
void static_task() {
    Uk_Flag(0, 0);
    Name_Net();
    Uk_Flag(112, 0);
}

int main()
{
    srand(time(0));
    int selected = 1;
    char selection;
    User newUser=User();
    while (true) { // Y
    start: // Потрібно було для того щоб працював getch_ для esc
        system("cls");
        static_task();
        Goto(53, 2); Uk cout << "Вітаємо у Pers!"; endll endll
            if (selected == 1) { sdwig str_vprawo zafarbuy(14); }
        if (selected != 1) { sdwig } cout << "\tРегестрація\t   "; if (selected != 1) { endll }
        if (selected == 1) { str_vlewo zafarbuy_bazoy(); }
        if (selected == 2) { sdwig str_vprawo zafarbuy(14); }
        if (selected != 2) { sdwig } cout << "\t   Вхід\t\t   "; if (selected != 2) { endll }
        if (selected == 2) { str_vlewo zafarbuy_bazoy(); }
        selection = _getch();
        if (selection == 72 && selected > 1) { selected--; }
        else if (selection == 80 && selected < 2) { selected++; }
        else if (selection == 13) {
            switch (selected) {
            case 1:
                while (true) {
                    cout << "Введіть логін: ";
                    getline(cin, newUser.login);
                    bool loginUnique = true;
                    for (auto& element : Social_Network::Users_SNetwork) {
                        if (element.login == newUser.login) {
                            cout << "Цей логін вже зайнятий, спробуйте інший\n";
                            loginUnique = false;
                            break;
                        }
                    }
                    if (loginUnique) { break; }
                }
                cout << "Введіть пароль: ";
                getline(cin, newUser.password);
                cout << "Введіть дату народження окремими елементами дати через ентер: ";
                cin >> newUser.date_of_birth.day >> newUser.date_of_birth.month >> newUser.date_of_birth.year; cin.ignore();

                while (true) {
                    cout << "Введіть gmail: ";
                    getline(cin, newUser.gmail);
                    bool gmailUnique = true;
                    for (auto& element : Social_Network::Users_SNetwork) {
                        if (element.gmail == newUser.gmail) {
                            cout << "Ця пошта вже зайнята для реєстрації, спробуйте іншу\n";
                            gmailUnique = false;
                            break;
                        }
                    }
                    if (gmailUnique) { break; }
                }
                while (true) {
                    cout << "Введіть номер телефону: ";
                    getline(cin, newUser.phone_number);
                    bool phoneNumberUnique = true;
                    for (auto& element : Social_Network::Users_SNetwork) {
                        if (element.phone_number == newUser.phone_number) {
                            cout << "Цей номер вже зайнятий для реєстрації, спробуйте інший\n";
                            phoneNumberUnique = false;
                            break;
                        }
                    }
                    if (phoneNumberUnique) { break; }
                }
                cout << "Введіть ім'я: ";
                getline(cin, newUser.NAme);
                cout << "Введіть країну: ";
                getline(cin, newUser.country);
                cout << "Регестрація успішно виконана!\n";
                Social_Network::createNewUser(newUser);
                Pause();
                goto profile;
                break;
            case 2:
                bool loginMatch = false;
                while (!loginMatch) {
                    cout << "Введіть логін: ";
                    getline(cin, newUser.login);
                    if (newUser.login == "esc") { goto start; }
                    for (auto& element : Social_Network::Users_SNetwork) {
                        if (element.login == newUser.login) {
                            loginMatch = true;
                            break;
                        }
                    }
                    if (!loginMatch) { cout << "Логін не знайдений, спробуйте ще раз" << endl; }
                }
                bool passwordMatch = false;
                while (!passwordMatch) {
                    cout << "Введіть пароль: ";
                    getline(cin, newUser.password);
                    if (newUser.password == "esc") { goto start; }
                    for (auto& element : Social_Network::Users_SNetwork) {
                        if (element.password == newUser.password) {
                            passwordMatch = true;
                            break;
                        }
                    }
                    if (!passwordMatch) { cout << "Пароль не вірний, спробуйте ще раз\n"; }
                }
                cout << "Вхід успішно виконаний!\n";
                Pause();
                break;
            }
            goto profile;
            break;
        }
    } // Меню для входу або регестрації 

profile:
    User foundUser=User();
    while (true) {
        system("cls");
        static_task();
        Goto(50, 3); Uk cout << "Оберіть подальшу дію"; endll endll
            if (selected == 1) { sdwig str_vprawo zafarbuy(14); }
        if (selected != 1) { sdwig } cout << "\tПерегляд постів\t\t\t   "; if (selected != 1) { endll }
        if (selected == 1) { str_vlewo zafarbuy_bazoy(); }
        if (selected == 2) { sdwig str_vprawo zafarbuy(14); }
        if (selected != 2) { sdwig } cout << "\tПошук користувача за логіном\t   "; if (selected != 2) { endll }
        if (selected == 2) { str_vlewo zafarbuy_bazoy(); }
        if (selected == 3) { sdwig str_vprawo zafarbuy(14); }
        if (selected != 3) { sdwig } cout << "\tДодати пост\t\t\t   "; if (selected != 3) { endll }
        if (selected == 3) { str_vlewo zafarbuy_bazoy(); }
        if (selected == 4) { sdwig str_vprawo zafarbuy(14); }
        if (selected != 4) { sdwig } cout << "\tМій профіль\t\t\t   "; if (selected != 4) { endll }
        if (selected == 4) { str_vlewo zafarbuy_bazoy(); }
        selection = _getch();
        if (selection == 72 && selected > 1) { selected--; }
        else if (selection == 80 && selected < 4) { selected++; }
        else if (selection == 27) { goto start; } // esc
        else if (selection == 13) {
            switch (selected) {
            case 1:
                newUser.Global_display_Post_Info();
                break;
            case 2:
                selected = 1;
                foundUser = Social_Network::findUserByLogin();
                while (true) {
                    system("cls");
                    static_task();
                    Goto(50, 3); Uk cout << "Оберіть подальшу дію"; endll endll
                        /*if (foundUser.login.empty()) { sdwig cout << "Користувач не знайдений" << endl;*/
                        sdwig cout << foundUser.NAme; endll
                        cout << "\t\t\tІз " << foundUser.country; endll
                        cout << "\t\t\tДата народження: " << foundUser.date_of_birth.day << "/" << foundUser.date_of_birth.month << "/" << foundUser.date_of_birth.year << endl;
                    cout << "\t\t\tДрузів " << foundUser.folowed.size(); endll
                        cout << "\t\t\tЛайків: " << foundUser.likes.size();
                    cout << "\t\t\tПостів: " << foundUser.posts.size(); endll
                        if (selected == 1) { zafarbuy(14); }
                    cout << "\t\t\tДодати друга";
                    if (selected == 1) { zafarbuy_bazoy(); }
                    if (selected == 2) { zafarbuy(4); }
                    cout << "\t\t\t" << "Видалити друга";
                    if (selected == 2) { zafarbuy_bazoy(); } endll endll
                        if (selected == 3) { zafarbuy(1); }
                    cout << "\t\t" << "Переглянути пости " << foundUser.login;
                    if (selected == 3) { zafarbuy_bazoy(); }
                    if (selected == 4) { zafarbuy(10); }
                    cout << "\t\t" << "Переглянути репости " << foundUser.login;
                    if (selected == 4) { zafarbuy_bazoy(); }
                    selection = _getch();
                    if (selection == 75 && selected > 1) { selected--; }
                    else if (selection == 77 && selected < 4) { selected++; }
                    else if (selection == 27) { break; } // при нажиманні esc будемо знову на початку 
                    else if (selection == 13) {
                        switch (selected) {
                        case 1:
                            newUser.addFriend(foundUser); endll
                                 break;
                        case 2:
                            newUser.removeFriend(foundUser); endll
                                   break;
                        case 3:
                            foundUser.display_User_Post_Info();
                             break;
                        case 4:
                            foundUser.display_Repost_Info();
                              break;
                        }
                        Pause();
                    }
                }
                break;
            case 3:
                newUser.addPost();
                break;
            case 4:
                goto my_profile;
                break;
            }
            Pause();
        }
    }
my_profile:
    selected = 1;
    while (true) {
        system("cls");
        static_task();
        Goto(50, 3); Uk cout << "Оберіть подальшу дію"; endll endll
            if (selected == 1) { sdwig str_vprawo zafarbuy(14); }
        if (selected != 1) { sdwig } cout << "\tПереглянути інформацію про мій профіль\t\t\t   "; if (selected != 1) { endll }
        if (selected == 1) { str_vlewo zafarbuy_bazoy(); }
        if (selected == 2) { sdwig str_vprawo zafarbuy(14); }
        if (selected != 2) { sdwig } cout << "\tПереглянути інформацію про мої пости\t   "; if (selected != 2) { endll }
        if (selected == 2) { str_vlewo zafarbuy_bazoy(); }
        if (selected == 3) { sdwig str_vprawo zafarbuy(14); }
        if (selected != 3) { sdwig } cout << "\tПереглянути інформацію про мої репости\t\t\t   "; if (selected != 3) { endll }
        if (selected == 3) { str_vlewo zafarbuy_bazoy(); }
        if (selected == 4) { sdwig str_vprawo zafarbuy(14); }
        if (selected != 4) { sdwig } cout << "\tПереглянути інформацію про мої збереження\t\t\t   "; if (selected != 4) { endll }
        if (selected == 4) { str_vlewo zafarbuy_bazoy(); }
        if (selected == 5) { sdwig str_vprawo zafarbuy(14); }
        if (selected != 5) { sdwig } cout << "\tВидалити пост\t\t\t   "; if (selected != 5) { endll }
        if (selected == 5) { str_vlewo zafarbuy_bazoy(); }
        selection = _getch();
        if (selection == 72 && selected > 1) { selected--; }
        else if (selection == 80 && selected < 5) { selected++; }
        else if (selection == 27) { goto profile; } // esc
        else if (selection == 13) {
            switch (selected) {
            case 1:
                newUser.display_User_Info();
                break;
            case 2:
                newUser.Global_display_Post_Info();
                break;
            case 3:
                newUser.display_Repost_Info();
                break;
            case 4:
                newUser.display_Storages_Info();
                break;
            case 5:
                int pid;
                cout << "Введіть айді поста якого хочете видалити: ";
                cin >> pid; 
                newUser.removePost(pid);
                break;
            }
            Pause();
        }
    }
    Social_Network::saveUsersToFile(Social_Network::Users_SNetwork, "C:/Users/Danylo/source/repos/Fin Social Network/Fin Social Network/users.txt");
    Social_Network::savePostsToFile(Social_Network::Posts_SNetwork, "C:/Users/Danylo/source/repos/Fin Social Network/Fin Social Network/posts.txt");
}
