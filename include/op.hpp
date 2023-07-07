#ifndef OP_HPP
#define OP_HPP
#include <string.h>
#include <iostream>
using namespace std;

bool isDouble(const string &str);   
bool isChar(char c);
int precedencia(const string& op);
string lerTipoString(const string& str);

#endif