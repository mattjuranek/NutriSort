#include "Food.h"
#include "unordered_map.h"
#include <map>
#include <algorithm>
using namespace cpr;
using json = nlohmann::json;


bool compareHigh(const pair<string, Food>& a, const pair<string, Food>& b, const string& nutrient) {
    if (nutrient == "proteins") {
        return a.second.proteins > b.second.proteins;
    }
    else if (nutrient == "fats") {
        return a.second.fat > b.second.fat;
    }
    else if (nutrient == "carbohydrates") {
        return a.second.carbohydrates > b.second.carbohydrates;
    }
    else if (nutrient == "sugars") {
        return a.second.sugars > b.second.sugars;
    }
    else if (nutrient == "sodium") {
        return a.second.sodium > b.second.sodium;
    }
    return false;
}

bool compareLow(const pair<string, Food>& a, const pair<string, Food>& b, const string& nutrient) {
    if (nutrient == "proteins") {
        return a.second.proteins < b.second.proteins;
    }
    else if (nutrient == "fats") {
        return a.second.fat < b.second.fat;
    }
    else if (nutrient == "carbohydrates") {
        return a.second.carbohydrates < b.second.carbohydrates;
    }
    else if (nutrient == "sugars") {
        return a.second.sugars < b.second.sugars;
    }
    else if (nutrient == "sodium") {
        return a.second.sodium < b.second.sodium;
    }
    return false;
}

vector<string> sortHigh(const map<string, Food>& foodMap, const string& nutrient) {
    // Convert map to vector of pairs for sorting
    vector<pair<string, Food>> foodItems(foodMap.begin(), foodMap.end());

    // Sort using compareHigh function
    sort(foodItems.begin(), foodItems.end(), [&nutrient](const pair<string, Food>& a, const pair<string, Food>& b) {
        return compareHigh(a, b, nutrient);
    });

    // Add sorted IDs to vector
    vector<string> sortedIDs;
    for (const auto& item : foodItems) {
        sortedIDs.push_back(item.first);
    }

    return sortedIDs;
}

vector<string> sortHighUnordered(::unordered_map<string, Food>& foodMap, const string& nutrient) {
    // Retrieve all items from unordered map, put in vector of pairs for sorting
    vector<pair<string, Food>> foodItems = foodMap.getAll();

    // Sort using the compareHigh function
    sort(foodItems.begin(), foodItems.end(), [&nutrient](const pair<string, Food>& a, const pair<string, Food>& b) {
        return compareHigh(a, b, nutrient);
    });

    // Add sorted IDs to vector
    vector<string> sortedIDs;
    for (const auto& item : foodItems) {
        sortedIDs.push_back(item.first);
    }

    return sortedIDs;
}

vector<string> sortLow(const map<string, Food>& foodMap, const string& nutrient) {
    // Convert map to vector of pairs for sorting
    vector<pair<string, Food>> foodItems(foodMap.begin(), foodMap.end());

    // Sort using compareLow function
    sort(foodItems.begin(), foodItems.end(), [&nutrient](const pair<string, Food>& a, const pair<string, Food>& b) {
        return compareLow(a, b, nutrient);
    });

    // Add sorted IDs to vector
    vector<string> sortedIDs;
    for (const auto& item : foodItems) {
        sortedIDs.push_back(item.first);
    }

    return sortedIDs;
}

vector<string> sortLowUnordered(::unordered_map<string, Food>& foodMap, const string& nutrient) {
    // Retrieve all items from unordered map, put in vector of pairs for sorting
    vector<pair<string, Food>> foodItems = foodMap.getAll();

    // Sort using compareLow function
    sort(foodItems.begin(), foodItems.end(), [&nutrient](const pair<string, Food>& a, const pair<string, Food>& b) {
        return compareLow(a, b, nutrient);
    });

    // Add sorted IDs to vector
    vector<string> sortedIDs;
    for (const auto& item : foodItems) {
        sortedIDs.push_back(item.first);
    }

    return sortedIDs;
}

void loadResultsWindow(tuple<string, string, string> results) {
    string productName = std::get<0>(results);
    string nutrient = std::get<1>(results);
    string sortMethod = std::get<2>(results);
    map<string, Food> orderedFoodMap;
    int maxPages = 1;

    sf::RenderWindow window(sf::VideoMode(800, 600), "NutriSort");

    // Load font files
    sf::Font textFont;
    if (!textFont.loadFromFile("../textFont.ttf")) {
        return;
    }

    auto start = chrono::high_resolution_clock::now();

    // Iterate through response pages (1 to maxPages)
    for (int pageNumber = 1; pageNumber < maxPages + 1; pageNumber++) {
        auto response = Get(Url{"https://us.openfoodfacts.org/cgi/search.pl"}, Parameters{{"search_terms", productName}, {"action", "process"},{"json", "true"}, {"page", to_string(pageNumber)}});

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

                // Add food object to orderedFoodMap
                orderedFoodMap[id] = Food(id, name, carbohydrates, proteins, fat, sugars, sodium);
            }
        }
    }

    // Sort foods by desired nutrient
    vector<string> sortedFoodIDs;

    if (sortMethod == "high") {
        sortedFoodIDs = sortHigh(orderedFoodMap, nutrient);
    }
    else if (sortMethod == "low") {
        sortedFoodIDs = sortLow(orderedFoodMap, nutrient);
    }

    // Stop the timer
    auto stop = chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);

    // Output duration
    cout << "Time to process: " << duration.count() << " seconds" << endl << endl;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(240, 240, 240));

        int i = 0;
        for (auto  id : sortedFoodIDs) {
            const Food& food = orderedFoodMap[id];

            string nameString = to_string(i + 1) + ". " + food.name;
            string proteinString = "Protein: " + to_string(int(food.proteins));
            string carbsString = "Carbohydrates: " + to_string(int(food.carbohydrates));
            string fatsString = "Fats: " + to_string(int(food.fat));
            string sugarsString = "Sugars: " + to_string(int(food.sugars));
            string sodiumString = "Sodium: " + to_string(int(food.sodium));

            // Text object for food name
            sf::Text name;
            name.setFont(textFont);
            name.setString(nameString);
            name.setCharacterSize(20);
            name.setFillColor(sf::Color::Black);
            name.setStyle(sf::Text::Bold);
            name.setPosition(20, 100 * i + 20);
            window.draw(name);

            // Text object for protein
            sf::Text protein;
            protein.setFont(textFont);
            protein.setString(proteinString);
            protein.setCharacterSize(20);
            protein.setFillColor(sf::Color::Black);
            protein.setPosition(50, 100 * i + 50);
            window.draw(protein);

            // Text object for carbs
            sf::Text carbs;
            carbs.setFont(textFont);
            carbs.setString(carbsString);
            carbs.setCharacterSize(20);
            carbs.setFillColor(sf::Color::Black);
            carbs.setPosition(200, 100 * i + 50);
            window.draw(carbs);

            // Text object for fats
            sf::Text fats;
            fats.setFont(textFont);
            fats.setString(fatsString);
            fats.setCharacterSize(20);
            fats.setFillColor(sf::Color::Black);
            fats.setPosition(420, 100 * i + 50);
            window.draw(fats);

            // Text object for sugars
            sf::Text sugars;
            sugars.setFont(textFont);
            sugars.setString(sugarsString);
            sugars.setCharacterSize(20);
            sugars.setFillColor(sf::Color::Black);
            sugars.setPosition(550, 100 * i + 50);
            window.draw(sugars);

            // Text object for sodium
            sf::Text sodium;
            sodium.setFont(textFont);
            sodium.setString(sodiumString);
            sodium.setCharacterSize(20);
            sodium.setFillColor(sf::Color::Black);
            sodium.setPosition(700, 100 * i + 50);
            window.draw(sodium);

            // Text object for line
            sf::Text line;
            line.setFont(textFont);
            line.setString("____________________________________________________________________________________________________");
            line.setCharacterSize(20);
            line.setFillColor(sf::Color::Black);
            line.setPosition(0, 100 * i + 80);
            window.draw(line);

            i++;
        }

        // Update window
        window.display();
    }
}

void loadResultsWindowUnordered(tuple<string, string, string> results) {
    string productName = std::get<0>(results);
    string nutrient = std::get<1>(results);
    string sortMethod = std::get<2>(results);
    ::unordered_map<string, Food> unorderedFoodMap;
    int maxPages = 1;

    sf::RenderWindow window(sf::VideoMode(800, 600), "NutriSort");

    // Load font files
    sf::Font textFont;
    if (!textFont.loadFromFile("../textFont.ttf")) {
        return;
    }

    auto start = chrono::high_resolution_clock::now();

    // Iterate through response pages (1 to maxPages)
    for (int pageNumber = 1; pageNumber < maxPages + 1; pageNumber++) {
        auto response = Get(Url{"https://us.openfoodfacts.org/cgi/search.pl"}, Parameters{{"search_terms", productName}, {"action", "process"},{"json", "true"}, {"page", to_string(pageNumber)}});

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

                // Add food object to unorderedFoodMap
                unorderedFoodMap.insert(id, Food(id, name, carbohydrates, proteins, fat, sugars, sodium));
            }
        }
    }

    // Sort foods by desired nutrient
    vector<string> sortedFoodIDs;

    if (sortMethod == "high") {
        sortedFoodIDs = sortHighUnordered(unorderedFoodMap, nutrient);
    }
    else if (sortMethod == "low") {
        sortedFoodIDs = sortLowUnordered(unorderedFoodMap, nutrient);
    }

    // Stop the timer
    auto stop = chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);

    // Output duration
    cout << "Time to process: " << duration.count() << " seconds" << endl << endl;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(240, 240, 240));

        int i = 0;
        for (auto  id : sortedFoodIDs) {
            const Food& food = unorderedFoodMap[id];

            string nameString = to_string(i + 1) + ". " + food.name;
            string proteinString = "Protein: " + to_string(int(food.proteins));
            string carbsString = "Carbohydrates: " + to_string(int(food.carbohydrates));
            string fatsString = "Fats: " + to_string(int(food.fat));
            string sugarsString = "Sugars: " + to_string(int(food.sugars));
            string sodiumString = "Sodium: " + to_string(int(food.sodium));

            // Text object for food name
            sf::Text name;
            name.setFont(textFont);
            name.setString(nameString);
            name.setCharacterSize(20);
            name.setFillColor(sf::Color::Black);
            name.setStyle(sf::Text::Bold);
            name.setPosition(20, 100 * i + 20);
            window.draw(name);

            // Text object for protein
            sf::Text protein;
            protein.setFont(textFont);
            protein.setString(proteinString);
            protein.setCharacterSize(20);
            protein.setFillColor(sf::Color::Black);
            protein.setPosition(50, 100 * i + 50);
            window.draw(protein);

            // Text object for carbs
            sf::Text carbs;
            carbs.setFont(textFont);
            carbs.setString(carbsString);
            carbs.setCharacterSize(20);
            carbs.setFillColor(sf::Color::Black);
            carbs.setPosition(200, 100 * i + 50);
            window.draw(carbs);

            // Text object for fats
            sf::Text fats;
            fats.setFont(textFont);
            fats.setString(fatsString);
            fats.setCharacterSize(20);
            fats.setFillColor(sf::Color::Black);
            fats.setPosition(420, 100 * i + 50);
            window.draw(fats);

            // Text object for sugars
            sf::Text sugars;
            sugars.setFont(textFont);
            sugars.setString(sugarsString);
            sugars.setCharacterSize(20);
            sugars.setFillColor(sf::Color::Black);
            sugars.setPosition(550, 100 * i + 50);
            window.draw(sugars);

            // Text object for sodium
            sf::Text sodium;
            sodium.setFont(textFont);
            sodium.setString(sodiumString);
            sodium.setCharacterSize(20);
            sodium.setFillColor(sf::Color::Black);
            sodium.setPosition(700, 100 * i + 50);
            window.draw(sodium);

            // Text object for line
            sf::Text line;
            line.setFont(textFont);
            line.setString("____________________________________________________________________________________________________");
            line.setCharacterSize(20);
            line.setFillColor(sf::Color::Black);
            line.setPosition(0, 100 * i + 80);
            window.draw(line);

            i++;
        }

        // Update window
        window.display();
    }
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
    sf::Font textFont;
    if (!textFont.loadFromFile("../textFont.ttf")) {
        return make_tuple(userInput, nutrient, userInput);
    }

    sf::Font titleFont;
    if (!titleFont.loadFromFile("../titleFont.ttf")) {
        return make_tuple(userInput, nutrient, userInput);
    }

    // Text object for title
    sf::Text title;
    title.setFont(titleFont);
    title.setString("NutriSort");
    title.setCharacterSize(66);
    title.setFillColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold);
    title.setPosition(800 / 2 - title.getLocalBounds().width / 2, 50);

    // Text object for user input
    sf::Text userInputText;
    userInputText.setFont(textFont);
    userInputText.setCharacterSize(30);
    userInputText.setStyle(sf::Text::Bold);
    userInputText.setFillColor(sf::Color::Black);
    userInputText.setPosition(50, 220);

    // Text object for search label
    sf::Text searchLabel;
    searchLabel.setFont(textFont);
    searchLabel.setString("Search Food:");
    searchLabel.setCharacterSize(32);
    searchLabel.setFillColor(sf::Color::Black);
    searchLabel.setPosition(50, 180);

    // Text object for "High"
    sf::Text highLabel;
    highLabel.setFont(textFont);
    highLabel.setString("High");
    highLabel.setCharacterSize(24);
    highLabel.setFillColor(sf::Color::Black);
    highLabel.setPosition(500, 450);

    // Text object for "Low"
    sf::Text lowLabel;
    lowLabel.setFont(textFont);
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
    restrictionLabel.setFont(textFont);
    restrictionLabel.setString("Select Nutrient:");
    restrictionLabel.setCharacterSize(32);
    restrictionLabel.setFillColor(sf::Color::Black);
    restrictionLabel.setPosition(50, 300);

    // Text object for protein
    sf::Text proteinLabel;
    proteinLabel.setFont(textFont);
    proteinLabel.setString("Protein");
    proteinLabel.setCharacterSize(20);
    proteinLabel.setFillColor(sf::Color::Black);
    proteinLabel.setPosition(50, 380);

    // Text object for carbs
    sf::Text carbLabel;
    carbLabel.setFont(textFont);
    carbLabel.setString("Carbohydrates");
    carbLabel.setCharacterSize(20);
    carbLabel.setFillColor(sf::Color::Black);
    carbLabel.setPosition(200, 380);

    // Text object for fat
    sf::Text fatLabel;
    fatLabel.setFont(textFont);
    fatLabel.setString("Fat");
    fatLabel.setCharacterSize(20);
    fatLabel.setFillColor(sf::Color::Black);
    fatLabel.setPosition(400, 380);

    // Text object for sugar
    sf::Text sugarLabel;
    sugarLabel.setFont(textFont);
    sugarLabel.setString("Sugar");
    sugarLabel.setCharacterSize(20);
    sugarLabel.setFillColor(sf::Color::Black);
    sugarLabel.setPosition(500, 380);

    // Text object for sodium
    sf::Text sodiumLabel;
    sodiumLabel.setFont(textFont);
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
                    // Open search results window
                    // Return tuple here with string userInput, string nutrient, string sortMethod

                    //TODO: Implement method to select ordered vs unordered map, load the associated window
                    loadResultsWindow(make_tuple(userInput, nutrient, sortMethod));
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
                        if (!nutrientIsSelected || nutrient != "proteins") {
                            proteinLabel.setStyle(sf::Text::Bold);
                            carbLabel.setStyle(sf::Text::Regular);
                            fatLabel.setStyle(sf::Text::Regular);
                            sugarLabel.setStyle(sf::Text::Regular);
                            sodiumLabel.setStyle(sf::Text::Regular);

                            nutrient = "proteins";
                            nutrientIsSelected = true;
                        }
                        else if (nutrient == "proteins") {
                            proteinLabel.setStyle(sf::Text::Regular);
                            nutrient = "";
                            nutrientIsSelected = false;
                        }
                    }

                    // Carbohydrate button
                    else if (carbLabel.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (!nutrientIsSelected || nutrient != "carbohydrates") {
                            proteinLabel.setStyle(sf::Text::Regular);
                            carbLabel.setStyle(sf::Text::Bold);
                            fatLabel.setStyle(sf::Text::Regular);
                            sugarLabel.setStyle(sf::Text::Regular);
                            sodiumLabel.setStyle(sf::Text::Regular);

                            nutrient = "carbohydrates";
                            nutrientIsSelected = true;
                        }
                        else if (nutrient == "carbohydrates") {
                            carbLabel.setStyle(sf::Text::Regular);
                            nutrient = "";
                            nutrientIsSelected = false;
                        }
                    }

                    // Fat button
                    if (fatLabel.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (!nutrientIsSelected || nutrient != "fats") {
                            proteinLabel.setStyle(sf::Text::Regular);
                            carbLabel.setStyle(sf::Text::Regular);
                            fatLabel.setStyle(sf::Text::Bold);
                            sugarLabel.setStyle(sf::Text::Regular);
                            sodiumLabel.setStyle(sf::Text::Regular);

                            nutrient = "fats";
                            nutrientIsSelected = true;
                        }
                        else if (nutrient == "fats") {
                            fatLabel.setStyle(sf::Text::Regular);
                            nutrient = "";
                            nutrientIsSelected = false;
                        }
                    }

                    // Sugar button
                    if (sugarLabel.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (!nutrientIsSelected || nutrient != "sugars") {
                            proteinLabel.setStyle(sf::Text::Regular);
                            carbLabel.setStyle(sf::Text::Regular);
                            fatLabel.setStyle(sf::Text::Regular);
                            sugarLabel.setStyle(sf::Text::Bold);
                            sodiumLabel.setStyle(sf::Text::Regular);

                            nutrient = "sugars";
                            nutrientIsSelected = true;
                        }
                        else if (nutrient == "sugars") {
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

    return make_tuple(userInput, nutrient, userInput);
}


int main() {
    loadSearchWindow();
}