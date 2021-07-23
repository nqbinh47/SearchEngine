#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#include <dirent.h>
#include <iostream>
#include <fcntl.h> //_O_WTEXT
#include <io.h>    //_setmode()
#include <string>
#include <locale>
#include <codecvt> //possible C++11?
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <windows.h>
using namespace std;
int64_t hash_fr_term(const string &term);
#endif // LIB_H_INCLUDED