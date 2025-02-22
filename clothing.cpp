#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, 
    double price, int qty, std::string size, std::string brand) :
    Product(category, name, price, qty), // Initialize base class
    size_(size),
    brand_(brand)
{

}

set<string> Clothing::keywords() const
{
    set<string> key;

    // Insert words from the product name
    set<string> nameWords = parseStringToWords(name_);
    key.insert(nameWords.begin(), nameWords.end());

    // Insert words from the brand
    set<string> brandWords = parseStringToWords(brand_);
    key.insert(brandWords.begin(), brandWords.end());


    return key;

}

string Clothing::displayString() const
{
    string price = std::to_string(price_);
    price = price.substr(0, price.find('.') + 3);


    string productDisplay;
    productDisplay = name_ + "\n";
    productDisplay += "Size: " + size_ + " Brand: " + brand_ + "\n";   
    productDisplay += price + " " + to_string(this->getQty()) + " left";


    return productDisplay;

}

void Clothing::dump(ostream& os) const
{
    string price = std::to_string(price_);
    price = price.substr(0, price.find('.') + 3);
    os << category_ << "\n" << name_ << "\n" << price << "\n" << qty_ << "\n"<<
    size_ << "\n" << brand_ << endl;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const {
    return false;
}