#include "movie.h"
#include "util.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <set>

using namespace std;

Movie::Movie(const std::string category, const std::string productName,
            double price, int qty, std::string genre, std::string rating):
                Product(category, productName, price, qty)
{
    mRating_ = rating;
    mGenre_ = genre;
}

Movie::~Movie()
{

}

set<string> Movie::keywords() const
{
    set<string>returnSet;
    set<string>genreSet;
    
    returnSet = parseStringToWords(mGenre_);
    genreSet = parseStringToWords(name_);

    returnSet.insert(genreSet.begin(), genreSet.end());
    return returnSet;
}

string Movie::displayString() const
{
    stringstream ss;
    ss << fixed << setprecision(2) << price_; // set to decimal limit of actual USD currency
    // ss.str() is price_ as a string
    string display = name_ + "\nGenre: " + mGenre_ + " Rating: " + mRating_ + "\n"
        + ss.str() + " " + to_string(qty_) + " left.";
    return display;
}

void Movie::dump(std::ostream& os) const
{
    stringstream ss;
    ss << fixed << setprecision(2) << price_;
    // ss.str() is price_ as a string
    string display = "movie\n" + name_ + "\n" + ss.str() + "\n" + to_string(qty_) + "\n"
        + mGenre_ + "\n" + mRating_;
    os << display << endl;
}