#include "book.h"
#include "util.h"
#include<set>
#include<iomanip>
#include<sstream>
#include<iostream>

using namespace std;

Book::Book(const std::string category, const std::string productName, 
    double price, int qty, std::string isbn, std::string author): Product(category, productName, price, qty)
{
    isbnNumber_ = isbn;
    authorName_ = author;
}

Book::~Book()
{

}

set<string> Book::keywords() const
{
    set<string>returnSet;
    set<string>nameSet;
    
    returnSet = parseStringToWords(authorName_);
    nameSet = parseStringToWords(name_);

    returnSet.insert(nameSet.begin(), nameSet.end());
    returnSet.insert(isbnNumber_);

    return returnSet;
}

std::string Book::displayString() const
{
    stringstream ss;
    ss << fixed << setprecision(2) << price_; // set to decimal limit of actual USD currency
    // ss.str() is price_ as a string
    string display = name_ + "\nAuthor: " + authorName_ + " ISBN: " + isbnNumber_ + "\n"
        + ss.str() + " " + to_string(qty_) + " left.";
    return display;
}

void Book::dump(std::ostream& os) const
{
    stringstream ss;
    ss << fixed << setprecision(2) << price_;
    // ss.str() is price_ as a string
    string display = "book\n" + name_ + "\n" + ss.str() + "\n" + to_string(qty_) + "\n"
        + isbnNumber_ + "\n" + authorName_;
    os << display << endl;
}