#include <demo_lib.h>
#include <include.h>
#include <iostream>

using namespace std;
int main() {
    PrisonerManagementSystem pms;
    menu(pms);
    return 0;
}

void menu(PrisonerManagementSystem& pms) {
    int a = 0;
    cout << "Please enter your choice : \n";
    cout << "0(exit), 1(to imprison) , 2(to inquiry prisoner)   ,3(to "
            "free prisoner)"
         << endl;
    cin >> a;
    switch (a) {
    case 0:
        return;
        break;
    case 1:
        imprison(pms);
        break;
    case 2:
        inquiry(pms);
        break;
    case 3:
        free(pms);
        break;
    default:
        cout << "Please enter 1 , 2, 3 or 4" << endl;

        break;
    }
}
void end(PrisonerManagementSystem& pms) {
    int choice = 0;
begin:
    cout << "0(exit), 1 (back) : " << endl;
    cin >> choice;
    switch (choice) {
    case 0:
        return;
        break;
    case 1:
        menu(pms);
    default:
        goto begin;
        break;
    }
}

void imprison(PrisonerManagementSystem& pms) {
    int ID;
    string name;
    string crime;
    cout << "Prisoner ID : " << endl;
    cin >> ID;
    cout << "Prisoner name : " << endl;
    cin >> name;
    cout << "Prisoner crime :" << endl;
    cin >> crime;
    pms.addPrisoner(ID, name, crime);
    end(pms);
}
void inquiry(PrisonerManagementSystem& pms) {
    int ID;
    string name;
    string crime;
    char ch;
    
    cout << "Prisoner ID(press Enter to skip) : " << endl;
    cin >> ID;
    cout << "Prisoner name(press Enter to skip) : " << endl;
    cin >> name;
    cout << "Prisoner crime(press Enter to skip) :" << endl;
    cin >> crime;
    pms.inquiry_prisoner(ID,name,crime);
    end(pms);
}
void free(PrisonerManagementSystem& pms) {

    end(pms);
}