#include "Food.h"
#include "unordered_map.h"
#include <map>
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

tuple<string, string, string> loadSearchWindow() {
    bool lowIsSelected = false;
    bool highIsSelected = false;
    bool nutrientIsSelected = false;
    string sortMethod = "";
    string nutrient = "";
    string userInput = "";

    sf::RenderWindow window(sf::VideoMode(800, 600), "NutriSort");

    // Load background image
    sf::Texture texture;
    if (!texture.loadFromFile("../background.jpg")) {
        return make_tuple(userInput, nutrient, userInput);
    }

    // Create sprite for background image
    sf::Sprite background(texture);

    // Calculate scale factors
    float scaleX = window.getSize().x / float(texture.getSize().x);
    float scaleY = window.getSize().x / float(texture.getSize().y);

    // Set scale of background sprite
    background.setScale(scaleX, scaleY);

    // Load font file
    sf::Font font;
    if (!font.loadFromFile("../font.ttf")) {
        return make_tuple(userInput, nutrient, userInput);
    }

    // Text object for title
    sf::Text title;
    title.setFont(font);
    title.setString("NutriSort");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold);
    title.setPosition(800 / 2 - title.getLocalBounds().width / 2, 50);

    // Text object for user input
    sf::Text userInputText;
    userInputText.setFont(font);
    userInputText.setCharacterSize(30);
    userInputText.setStyle(sf::Text::Bold);
    userInputText.setFillColor(sf::Color::Black);
    userInputText.setPosition(50, 220);

    // Text object for search label
    sf::Text searchLabel;
    searchLabel.setFont(font);
    searchLabel.setString("Search Food:");
    searchLabel.setCharacterSize(32);
    searchLabel.setFillColor(sf::Color::Black);
    searchLabel.setPosition(50, 180);

    // Text object for "High"
    sf::Text highLabel;
    highLabel.setFont(font);
    highLabel.setString("High");
    highLabel.setCharacterSize(24);
    highLabel.setFillColor(sf::Color::Black);
    highLabel.setPosition(500, 450);

    // Text object for "Low"
    sf::Text lowLabel;
    lowLabel.setFont(font);
    lowLabel.setString("Low");
    lowLabel.setCharacterSize(24);
    lowLabel.setFillColor(sf::Color::Black);
    lowLabel.setPosition(250, 450);

    // Rectangle for low select box
    sf::RectangleShape lowBox(sf::Vector2f(20, 20));
    lowBox.setFillColor(sf::Color::White);
    lowBox.setOutlineColor(sf::Color::Black);
    lowBox.setOutlineThickness(1);
    lowBox.setPosition(220, 455);

    // Rectangle for high select box
    sf::RectangleShape highBox(sf::Vector2f(20, 20));
    highBox.setFillColor(sf::Color::White);
    highBox.setOutlineColor(sf::Color::Black);
    highBox.setOutlineThickness(1);
    highBox.setPosition(470, 455);

    // Rectangle for search bar
    sf::RectangleShape searchBar(sf::Vector2f(700, 40));
    searchBar.setFillColor(sf::Color::White);
    searchBar.setOutlineColor(sf::Color::Black);
    searchBar.setOutlineThickness(2);
    searchBar.setPosition(50, 220);

    // Text object for nutrient select
    sf::Text restrictionLabel;
    restrictionLabel.setFont(font);
    restrictionLabel.setString("Select Nutrient:");
    restrictionLabel.setCharacterSize(32);
    restrictionLabel.setFillColor(sf::Color::Black);
    restrictionLabel.setPosition(50, 300);

    // Text object for protein
    sf::Text proteinLabel;
    proteinLabel.setFont(font);
    proteinLabel.setString("Protein");
    proteinLabel.setCharacterSize(20);
    proteinLabel.setFillColor(sf::Color::Black);
    proteinLabel.setPosition(50, 380);

    // Text object for carbs
    sf::Text carbLabel;
    carbLabel.setFont(font);
    carbLabel.setString("Carbohydrates");
    carbLabel.setCharacterSize(20);
    carbLabel.setFillColor(sf::Color::Black);
    carbLabel.setPosition(200, 380);

    // Text object for fat
    sf::Text fatLabel;
    fatLabel.setFont(font);
    fatLabel.setString("Fat");
    fatLabel.setCharacterSize(20);
    fatLabel.setFillColor(sf::Color::Black);
    fatLabel.setPosition(400, 380);

    // Text object for sugar
    sf::Text sugarLabel;
    sugarLabel.setFont(font);
    sugarLabel.setString("Sugar");
    sugarLabel.setCharacterSize(20);
    sugarLabel.setFillColor(sf::Color::Black);
    sugarLabel.setPosition(500, 380);

    // Text object for sodium
    sf::Text sodiumLabel;
    sodiumLabel.setFont(font);
    sodiumLabel.setString("Sodium");
    sodiumLabel.setCharacterSize(20);
    sodiumLabel.setFillColor(sf::Color::Black);
    sodiumLabel.setPosition(650, 380);

    // Event handling
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {

                // If user clicks backspace
                if (event.key.code == sf::Keyboard::Backspace && !userInput.empty()) {

                    // Remove last character of username
                    userInput.pop_back();
                }

                // If user clicks enter while user input is not empty
                if (event.key.code == sf::Keyboard::Enter && !userInput.empty() && nutrientIsSelected && (lowIsSelected || highIsSelected)) {

                    // Close search window
                    //TODO: Open search results window
                    // Return tuple here with string userInput, string nutrient, string sortMethod
                    return make_tuple(userInput, nutrient, sortMethod);
                    window.close();
                }
            }

            // If user enters text
            if (event.type == sf::Event::TextEntered) {

                // Limit size of user input to 30 characters
                if (userInput.size() < 35) {
                    char nameChar  = static_cast<char>(event.text.unicode);

                    // Limit entry to alphabetical characters
                    if (isalpha(nameChar) || nameChar == ' ') {
                        userInput += nameChar;
                    }
                }
            }

            // If user clicks mouse button
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // High button
                    if (highBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (!highIsSelected) {
                            highBox.setFillColor(sf::Color::Black);
                            highIsSelected = true;
                            sortMethod = "high";

                            if (lowIsSelected) {
                                lowBox.setFillColor(sf::Color::White);
                                lowIsSelected = false;
                            }
                        }
                        else {
                            highBox.setFillColor(sf::Color::White);
                            highIsSelected = false;
                            sortMethod = "";
                        }
                    }

                    // Low button
                    if (lowBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (!lowIsSelected) {
                            lowBox.setFillColor(sf::Color::Black);
                            lowIsSelected = true;
                            sortMethod = "low";

                            if (highIsSelected) {
                                highBox.setFillColor(sf::Color::White);
                                highIsSelected = false;
                            }
                        }
                        else {
                            lowBox.setFillColor(sf::Color::White);
                            lowIsSelected = false;
                            sortMethod = "";
                        }
                    }

                    // Protein button
                    if (proteinLabel.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (!nutrientIsSelected || nutrient != "protein") {
                            proteinLabel.setStyle(sf::Text::Bold);
                            carbLabel.setStyle(sf::Text::Regular);
                            fatLabel.setStyle(sf::Text::Regular);
                            sugarLabel.setStyle(sf::Text::Regular);
                            sodiumLabel.setStyle(sf::Text::Regular);

                            nutrient = "protein";
                            nutrientIsSelected = true;
                        }
                        else if (nutrient == "protein") {
                            proteinLabel.setStyle(sf::Text::Regular);
                            nutrient = "";
                            nutrientIsSelected = false;
                        }
                    }

                    // Carbohydrate button
                    else if (carbLabel.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (!nutrientIsSelected || nutrient != "carbohydrate") {
                            proteinLabel.setStyle(sf::Text::Regular);
                            carbLabel.setStyle(sf::Text::Bold);
                            fatLabel.setStyle(sf::Text::Regular);
                            sugarLabel.setStyle(sf::Text::Regular);
                            sodiumLabel.setStyle(sf::Text::Regular);

                            nutrient = "carbohydrate";
                            nutrientIsSelected = true;
                        }
                        else if (nutrient == "carbohydrate") {
                            carbLabel.setStyle(sf::Text::Regular);
                            nutrient = "";
                            nutrientIsSelected = false;
                        }
                    }

                    // Fat button
                    if (fatLabel.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (!nutrientIsSelected || nutrient != "fat") {
                            proteinLabel.setStyle(sf::Text::Regular);
                            carbLabel.setStyle(sf::Text::Regular);
                            fatLabel.setStyle(sf::Text::Bold);
                            sugarLabel.setStyle(sf::Text::Regular);
                            sodiumLabel.setStyle(sf::Text::Regular);

                            nutrient = "fat";
                            nutrientIsSelected = true;
                        }
                        else if (nutrient == "fat") {
                            fatLabel.setStyle(sf::Text::Regular);
                            nutrient = "";
                            nutrientIsSelected = false;
                        }
                    }

                    // Sugar button
                    if (sugarLabel.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (!nutrientIsSelected || nutrient != "sugar") {
                            proteinLabel.setStyle(sf::Text::Regular);
                            carbLabel.setStyle(sf::Text::Regular);
                            fatLabel.setStyle(sf::Text::Regular);
                            sugarLabel.setStyle(sf::Text::Bold);
                            sodiumLabel.setStyle(sf::Text::Regular);

                            nutrient = "sugar";
                            nutrientIsSelected = true;
                        }
                        else if (nutrient == "sugar") {
                            sugarLabel.setStyle(sf::Text::Regular);
                            nutrient = "";
                            nutrientIsSelected = false;
                        }
                    }

                    // Sodium button
                    if (sodiumLabel.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (!nutrientIsSelected || nutrient != "sodium") {
                            proteinLabel.setStyle(sf::Text::Regular);
                            carbLabel.setStyle(sf::Text::Regular);
                            fatLabel.setStyle(sf::Text::Regular);
                            sugarLabel.setStyle(sf::Text::Regular);
                            sodiumLabel.setStyle(sf::Text::Bold);

                            nutrient = "sodium";
                            nutrientIsSelected = true;
                        }
                        else if (nutrient == "sodium") {
                            sodiumLabel.setStyle(sf::Text::Regular);
                            nutrient = "";
                            nutrientIsSelected = false;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color(250, 214, 140));

        // Draw elements
        window.draw(background);
        window.draw(title);
        window.draw(searchBar);
        userInputText.setString(userInput + "|");
        window.draw(userInputText);
        window.draw(searchLabel);
        window.draw(highLabel);
        window.draw(lowLabel);
        window.draw(restrictionLabel);
        window.draw(highBox);
        window.draw(lowBox);
        window.draw(proteinLabel);
        window.draw(carbLabel);
        window.draw(fatLabel);
        window.draw(sugarLabel);
        window.draw(sodiumLabel);

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
    loadSearchWindow();
}

//int main() {
//    string productName;
//    map<string, Food> foodMap;
//    int maxPages = 1;
//
//    cout << "Enter product name: ";
//    cin >> productName;
//
//    auto start = chrono::high_resolution_clock::now();
//
//    // Iterate through response pages (1 to maxPages)
//    for (int pageNumber = 1; pageNumber < maxPages + 1; pageNumber++) {
//        auto response = Get(Url{"https://us.openfoodfacts.org/cgi/search.pl"}, Parameters{{"search_terms", productName}, {"action", "process"},{"json", "true"}, {"page", to_string(pageNumber)}});
//
//        json j = json::parse(response.text);
//
//        if (j.contains("products") && j["products"].is_array()) {
//            for (const auto& product : j["products"]) {
//
//                // Retrieve food information for each product
//                string id = product.value("_id", "N/A");
//                string name = product.value("product_name", "N/A");
//                double carbohydrates = product["nutriments"].value("carbohydrates", 0.0);
//                double proteins = product["nutriments"].value("proteins", 0.0);
//                double fat = product["nutriments"].value("fat", 0.0);
//                double sugars = product["nutriments"].value("sugars", 0.0);
//                double sodium = product["nutriments"].value("sodium", 0.0);
//
//                // Add food object to foodMap
//                foodMap[id] = Food(id, name, carbohydrates, proteins, fat, sugars, sodium);
//            }
//        }
//    }
//
//    // Stop the timer
//    auto stop = chrono::high_resolution_clock::now();
//
//    // Calculate duration
//    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
//
////    // Output duration
////    cout << "Time to process: " << duration.count() << " seconds" << endl;
//
//
////    // Output food information for each product
////    for (auto food : foodMap) {
////        cout << "ID: " << food.first << endl;
////        cout << "Name: " << food.second.name << endl;
////        cout << "Carbohydrates: " << food.second.carbohydrates << endl;
////        cout << "Proteins: " << food.second.proteins << endl;
////        cout << "Fat: " << food.second.fat << endl;
////        cout << "Sugars: " << food.second.sugars << endl;
////        cout << "Sodium: " << food.second.sodium << endl << endl;
////    }
//
//    return 0;
//}
