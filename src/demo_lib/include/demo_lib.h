#ifndef DEMO_LIB_H
#define DEMO_LIB_H
#include <iostream>
int create_prisoner(void);
int inquiry_prisoner(void);
int free_prisoner(void);

typedef struct 
{
    int ID;
    std::string name;
    int number;
    std::string crime;
    std::string date;
    int term;
    std::string prison;
    std::string cell;
} prisoner;
prisoner basic_prisoner(void);

#endif