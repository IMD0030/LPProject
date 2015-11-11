#include <iostream>
#include <allegro5/allegro.h>
#include <string>
#include <sstream>
#include "Utils.h"

using namespace std;

string Utils::NumberToString ( int Number ) {
	ostringstream ss;
    ss << Number;
    return ss.str();
}