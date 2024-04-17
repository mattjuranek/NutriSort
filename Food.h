#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
using namespace std;


class Food {
public:
    string id;
    string name;
    double carbohydrates;
    double proteins;
    double fat;
    double sugars;
    double sodium;

    Food();
    Food(string id, string name, double carbohydrates, double proteins, double fat, double sugars, double sodium);
};
