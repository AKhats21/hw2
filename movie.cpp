#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, 
        int qty, std::string genre, std::string rating) :
    Product(category, name, price, qty), // Initialize base class
    genre_(genre),
    rating_(rating)
{

}

set<string> Movie::keywords() const
{
    set<string> key;

    // Insert words from the product name
    set<string> nameWords = parseStringToWords(name_);
    key.insert(nameWords.begin(), nameWords.end());

    // Insert Genre as keyword
    key.insert(convToLower(genre_));

    return key;


}

string Movie::displayString() const
{
    string price = std::to_string(price_);
    price = price.substr(0, price.find('.') + 3);


    string productDisplay;
    productDisplay = name_ + "\n";
    productDisplay += "Genre: " + genre_ + " Rating: " + rating_ + "\n";   
    productDisplay += price + " " + to_string(this->getQty()) + " left";


    return productDisplay;

}

void Movie::dump(ostream& os) const
{
    string price = std::to_string(price_);
    price = price.substr(0, price.find('.') + 3);
    os << category_ << "\n" << name_ << "\n" << price << "\n" << qty_ << "\n" <<
    genre_ << "\n" << rating_ << endl;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const {
    return false;
}
