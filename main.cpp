#include <cpr/cpr.h>
#include <iostream>
using namespace std;
using namespace cpr;

int main() {
    string productName;

    cin >> productName;

    auto response = Get(Url{"https://us.openfoodfacts.org/cgi/search.pl"}, Parameters{{"search_terms", productName}, {"action", "process"},{"json", "true"}});

    cout << response.text << endl;

    return 0;
}