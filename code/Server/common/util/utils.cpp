#include "utils.h"
#include <random>
#include <sstream>
#include <iomanip>

using namespace std;

string generateNumber() {
    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 999);

    // Generate a random three-digit number
    int randomNumber = dist(gen);

    // Convert the number to a string with leading zeros
    ostringstream oss;
    oss << setw(3) << setfill('0') << randomNumber;

    return oss.str();
}