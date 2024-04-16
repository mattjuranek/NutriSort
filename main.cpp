#include "Food.h"
using namespace cpr;
using json = nlohmann::json;


void setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void setSprite(sf::Sprite &sprite, float x, float y) {
    sprite.setPosition(sf::Vector2f(x, y));
}

void setRect(sf::RectangleShape &rect, float x, float y) {
    rect.setPosition(sf::Vector2f(x, y));
}

void loadSearchWindow() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "NutriSort");

    // Load font file
    sf::Font font;
    if (!font.loadFromFile("../font.ttf"))
    {
        return;
    }

    // Text object for title
    sf::Text title;
    title.setFont(font);
    title.setString("NutriSort");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold);
    title.setPosition(800 / 2 - title.getLocalBounds().width / 2, 50);

    // Text object for search label
    sf::Text searchLabel;
    searchLabel.setFont(font);
    searchLabel.setString("Search Food:");
    searchLabel.setCharacterSize(24);
    searchLabel.setFillColor(sf::Color::Black);
    searchLabel.setPosition(50, 260);

    // Rectangle for search bar
    sf::RectangleShape searchBar(sf::Vector2f(700, 40));
    searchBar.setFillColor(sf::Color::White);
    searchBar.setOutlineColor(sf::Color::Black);
    searchBar.setOutlineThickness(2);
    searchBar.setPosition(50, 300);

    // Text object for "Search Food:"
    sf::Text restrictionLabel;
    restrictionLabel.setFont(font);
    restrictionLabel.setString("Dietary Restriction:");
    restrictionLabel.setCharacterSize(24);
    restrictionLabel.setFillColor(sf::Color::Black);
    restrictionLabel.setPosition(50, 360);

    // Rectangle for second search bar
    sf::RectangleShape restrictionBar(sf::Vector2f(700, 40));
    restrictionBar.setFillColor(sf::Color::White);
    restrictionBar.setOutlineColor(sf::Color::Black);
    restrictionBar.setOutlineThickness(2);
    restrictionBar.setPosition(50, 400);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(250, 214, 140));

        // Draw elements
        window.draw(title);
        window.draw(searchLabel);
        window.draw(restrictionLabel);
        window.draw(restrictionBar);
        window.draw(searchBar);

        // Update window
        window.display();
    }
}

void loadMainWindow()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "NutriSort");

    // Load font file
    sf::Font font;
    if (!font.loadFromFile("../font.ttf"))
    {
        return;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(240, 240, 240));

        // Update window
        window.display();
    }
}


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
