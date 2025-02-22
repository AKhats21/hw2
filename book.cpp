#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, 
    int qty, std::string isbn, std::string author) :
    Product(category, name, price, qty), // Initialize base class
    isbn_(isbn),
    author_(author)
{

}

set<string> Book::keywords() const
{
    set<string> key;

    // Insert words from the product name
    set<string> nameWords = parseStringToWords(name_);
    key.insert(nameWords.begin(), nameWords.end());

    // Insert words from the author
    set<string> authorWords = parseStringToWords(author_);
    key.insert(authorWords.begin(), authorWords.end());

    // Insert the ISBN as a keyword
    key.insert(isbn_);

    return key;


}

string Book::displayString() const
{
    string price = std::to_string(price_);
    price = price.substr(0, price.find('.') + 3);

    string productDisplay;
    productDisplay = name_ + "\n";
    productDisplay += "Author: " + author_ + " ISBN: " + isbn_ + "\n";   
    productDisplay += price + " " + to_string(this->getQty()) + " left";

    return productDisplay;

}

void Book::dump(ostream& os) const
{
    string price = std::to_string(price_);
    price = price.substr(0, price.find('.') + 3);
    os << category_ << "\n" << name_ << "\n" << price << "\n" << qty_ << "\n" <<
    isbn_ << "\n" << author_ << endl;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const {
    return false;
}