#include "Food.h"


Food::Food() {
}

Food::Food(string id, string name, double carbohydrates, double proteins, double fat, double sugars, double sodium) {
    this-> id = id;
    this-> name = name;
    this-> carbohydrates = carbohydrates;
    this-> proteins = proteins;
    this-> fat = fat;
    this-> sugars = sugars;
    this-> sodium = sodium;
}
