#include <include.h>
#include <iostream>

using namespace std;
int main() {

    menu();
    return 0;
}

int menu() {
    int a = 0;
    cout << "Please enter your choice : \n";
    cout << "0(exit or up), 1(to imprison) , 2(to inquiry prisoner)   ,3(to "
            "free prisoner)"
         << endl;
    cin >> a;
    switch (a) {
    case 0:
        exit(0);
        break;
    case 1:
        imprison();
        break;
    case 2:
        inquiry();
        break;
    case 3:
        free();
        break;
    default:
        cout << "Please enter 1 , 2, 3 or 4" << endl;
        menu();
        break;
    }
}
void end(void) {
    int choice = 0;
begin:
    cout << "0(exit), 1 (up) : " << endl;
    cin >> choice;
    switch (choice) {
    case 0:
        exit(0);
        break;
    case 1:
        menu();
    default:
        goto begin;
        break;
    }
}

void imprison() {
    if (create_prisoner()) {
        cout << "Succeed prisoning !" << endl;
    } else
        cout << "Fail to prison" << endl;
    end();
}
void inquiry() {
    if (inquiry_prisoner()) {
        cout << "Succeed inquirying!" << endl;
    } else
        cout << "Fail to inquiry" << endl;
    end();
}
void free() {
    if (free_prisoner()) {
        cout << "Succeed freeing!" << endl;
    } else
        cout << "Fail to free" << endl;
    end();
}