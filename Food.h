#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;


class Food {
public:
    string id; // _id
    string name; //product_name
    double carbohydrates; // nutriments > carbohydrates
    double proteins; // nutriments > proteins;
    double fat; // nutriments > fat
    double sugars; //nutriments > sugars
    double sodium; // nutriments > sodium
    //TODO: Add other attributes as needed

    Food();
    Food(string id, string name, double carbohydrates, double proteins, double fat, double sugars, double sodium);
};
