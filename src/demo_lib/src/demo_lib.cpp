#include <demo_lib.h>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>

using namespace std;
prisoner basic_prisoner(void) {
    prisoner sb;
    cout << "prisoner ID : " << endl;
    cin >> sb.ID;

    cout << "prisoner name : " << endl;
    cin >> sb.name;

    cout << "prisoner number : " << endl;
    cin >> sb.number;

    cout << "prisoner crime : " << endl;
    cin >> sb.crime;

    cout << "date of prison(be like 19420303) : " << endl;
    cin >> sb.date;

    cout << "prison term(please exchange per year) : " << endl;
    cin >> sb.term;

    cout << "which prison : " << endl;
    cin >> sb.prison;

    cout << "which cell : " << endl;
    cin >> sb.cell;
    return sb;
}
int create_prisoner(void) {
    prisoner sb = basic_prisoner();
    const char* str = sb.prison.c_str();
    ofstream ofs(str);
    if (!ofs.is_open()) {
        cout << "Open failed" << endl;
        exit(0);
    }
    ofs << sb.ID << "," << sb.name << "," << sb.crime << "," << sb.date << ","
        << sb.term << "," << sb.prison << "," << sb.cell << "\n";

    return 1;
}

int inquiry_prisoner(void) {
    return 1;
}
int free_prisoner(void) {
    return 1;
}