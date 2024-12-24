#ifndef DEMO_LIB_H
#define DEMO_LIB_H
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

int free_prisoner(void);
// 定义结构体Prisoner,记录囚犯基本信息
struct Prisoner {
    int ID;
    std::string name;
    std::string crime;
    Prisoner(int ID, std::string name, std::string crime)
        : ID(ID), name(name), crime(crime) {}
};

// 定义囚犯管理系统类，
class PrisonerManagementSystem {
private:
    std::vector<Prisoner> prisoners;
    const std::string filename = "prisoners.txt";
    void loadPrisoners() {
        std::ifstream file(filename);
        if (!file.is_open()) {
            perror("Load failure");
            return;
        }
        int ID;
        std::string name;
        std::string crime;
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            ss >> ID >> std::ws;
            getline(ss, name, ',');
            getline(ss, crime, '\n');
            prisoners.emplace_back(ID, name, crime);
        }
        file.close();
        printf("Succeed loading!\n");
    }
    void savePrisoners() {
        std::ofstream file(filename);
        if (!file.is_open()) {
            perror("Save failure");
            return;
        }
        for (const auto prisoner : prisoners) {
            file << prisoner.ID << " " << prisoner.name << "," << prisoner.crime
                 << std::endl;
        }
        file.close();
        printf("Succeed saving!\n");
    }

public:
    PrisonerManagementSystem() {
        loadPrisoners();
    }
    ~PrisonerManagementSystem() {
        savePrisoners();
    }
    void addPrisoner(int ID, std::string name, std::string crime) {
        prisoners.emplace_back(ID, name, crime);
        printf("Succeed adding!\n");
    }
    void inquiry_prisoner(int ID, std::string name, std::string crime) {
        for (const auto& prisoner : prisoners) {
            if (prisoner.ID == ID) {
                cout << "Prisoner ID : " << prisoner.ID << endl;
                cout << "Prisoner name : " << prisoner.name << endl;
                cout << "Prisoner crime : " << prisoner.crime << endl;
            }
            if (prisoner.name == name) {
                cout << "Prisoner ID : " << prisoner.ID << endl;
                cout << "Prisoner name : " << prisoner.name << endl;
                cout << "Prisoner crime : " << prisoner.crime << endl;
            }
            if (prisoner.crime == crime) {
                cout << "Prisoner ID : " << prisoner.ID << endl;
                cout << "Prisoner name : " << prisoner.name << endl;
                cout << "Prisoner crime : " << prisoner.crime << endl;
            }
        }
    }
};

#endif