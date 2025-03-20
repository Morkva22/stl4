#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

using CountryMap = map<string, vector<string>>;

void loadDataFromFile(CountryMap& countries, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string country, city;
    while (file >> country >> city) {
        countries[country].push_back(city);
    }
    file.close();
}

void saveDataToFile(const CountryMap& countries, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    for (const auto& [country, cities] : countries) {
        for (const auto& city : cities) {
            file << country << " " << city << endl;
        }
    }
    file.close();
}

void searchCitiesByCountry(const CountryMap& countries, const string& country) {
    auto it = countries.find(country);
    if (it != countries.end()) {
        cout << "Cities in " << country << ":" << endl;
        for (const auto& city : it->second) {
            cout << city << endl;
        }
    } else {
        cout << "Country not found!" << endl;
    }
}

void replaceCityName(CountryMap& countries, const string& country, const string& oldCity, const string& newCity) {
    auto it = countries.find(country);
    if (it != countries.end()) {
        auto& cities = it->second;
        auto cityIt = find(cities.begin(), cities.end(), oldCity);
        if (cityIt != cities.end()) {
            *cityIt = newCity;
            cout << "City replaced successfully!" << endl;
        } else {
            cout << "City not found!" << endl;
        }
    } else {
        cout << "Country not found!" << endl;
    }
}

void addCity(CountryMap& countries, const string& country, const string& city) {
    countries[country].push_back(city);
    cout << "City added successfully!" << endl;
}

void addCountry(CountryMap& countries, const string& country) {
    if (countries.find(country) == countries.end()) {
        countries[country] = {};
        cout << "Country added successfully!" << endl;
    } else {
        cout << "Country already exists!" << endl;
    }
}

void removeCity(CountryMap& countries, const string& country, const string& city) {
    auto it = countries.find(country);
    if (it != countries.end()) {
        auto& cities = it->second;
        auto cityIt = find(cities.begin(), cities.end(), city);
        if (cityIt != cities.end()) {
            cities.erase(cityIt);
            cout << "City removed successfully!" << endl;
        } else {
            cout << "City not found!" << endl;
        }
    } else {
        cout << "Country not found!" << endl;
    }
}

void removeCountry(CountryMap& countries, const string& country) {
    if (countries.erase(country)) {
        cout << "Country removed successfully!" << endl;
    } else {
        cout << "Country not found!" << endl;
    }
}

int countCities(const CountryMap& countries) {
    int count = 0;
    for (const auto& [country, cities] : countries) {
        count += cities.size();
    }
    return count;
}

void displayCountries(const CountryMap& countries) {
    cout << "List of countries:" << endl;
    for (const auto& [country, cities] : countries) {
        cout << country << endl;
    }
}

int main() {
    CountryMap countries;
    string filename = "data.txt";
    int choice;

    do {
        cout << "\n1. Load Data from File\n2. Save Data to File\n3. Search Cities by Country\n4. Replace City Name\n5. Add City\n6. Add Country\n7. Remove City\n8. Remove Country\n9. Count Cities\n10. Display Countries\n11. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                loadDataFromFile(countries, filename);
                break;
            case 2:
                saveDataToFile(countries, filename);
                break;
            case 3: {
                string country;
                cout << "Enter country name: ";
                cin >> country;
                searchCitiesByCountry(countries, country);
                break;
            }
            case 4: {
                string country, oldCity, newCity;
                cout << "Enter country name: ";
                cin >> country;
                cout << "Enter old city name: ";
                cin >> oldCity;
                cout << "Enter new city name: ";
                cin >> newCity;
                replaceCityName(countries, country, oldCity, newCity);
                break;
            }
            case 5: {
                string country, city;
                cout << "Enter country name: ";
                cin >> country;
                cout << "Enter city name: ";
                cin >> city;
                addCity(countries, country, city);
                break;
            }
            case 6: {
                string country;
                cout << "Enter country name: ";
                cin >> country;
                addCountry(countries, country);
                break;
            }
            case 7: {
                string country, city;
                cout << "Enter country name: ";
                cin >> country;
                cout << "Enter city name: ";
                cin >> city;
                removeCity(countries, country, city);
                break;
            }
            case 8: {
                string country;
                cout << "Enter country name: ";
                cin >> country;
                removeCountry(countries, country);
                break;
            }
            case 9:
                cout << "Total number of cities: " << countCities(countries) << endl;
                break;
            case 10:
                displayCountries(countries);
                break;
            case 11:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 11);

    return 0;
}