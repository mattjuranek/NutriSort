#include "Food.h"
using namespace cpr;
using json = nlohmann::json;


int main() {
    string productName;
    map<string, Food> foodMap;

    cout << "Enter product name: ";
    cin >> productName;

    auto response = Get(Url{"https://us.openfoodfacts.org/cgi/search.pl"}, Parameters{{"search_terms", productName}, {"action", "process"},{"json", "true"}});

    json j = json::parse(response.text);

    if (j.contains("products") && j["products"].is_array()) {
        for (const auto& product : j["products"]) {

            // Retrieve food information for each product
            string id = product.value("_id", "N/A");
            string name = product.value("product_name", "N/A");
            double carbohydrates = product["nutriments"].value("carbohydrates", 0.0);
            double proteins = product["nutriments"].value("proteins", 0.0);
            double fat = product["nutriments"].value("fat", 0.0);
            double sugars = product["nutriments"].value("sugars", 0.0);
            double sodium = product["nutriments"].value("sodium", 0.0);

            // Add food object to foodMap
            foodMap[id] = Food(id, name, carbohydrates, proteins, fat, sugars, sodium);
        }
    }

    for (auto food : foodMap) {
        cout << "ID: " << food.first << endl;
        cout << "Name: " << food.second.name << endl;
        cout << "Carbohydrates: " << food.second.carbohydrates << endl;
        cout << "Proteins: " << food.second.proteins << endl;
        cout << "Fat: " << food.second.fat << endl;
        cout << "Sugars: " << food.second.sugars << endl;
        cout << "Sodium: " << food.second.sodium << endl << endl;
    }


    return 0;
}
