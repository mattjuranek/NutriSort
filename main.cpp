#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
using namespace std;
using namespace cpr;
using json = nlohmann::json;


int main() {
    string productName;

    cout << "Enter product name: ";
    cin >> productName;

    auto response = Get(Url{"https://us.openfoodfacts.org/cgi/search.pl"}, Parameters{{"search_terms", productName}, {"action", "process"},{"json", "true"}});

    json j = json::parse(response.text);

    return 0;

}
