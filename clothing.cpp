#include "clothing.h"
#include "util.h"
#include <iomanip>
#include <set>
#include <string>
#include <sstream>

using namespace std;

Clothing::Clothing(const std::string category, const std::string productName,
        double price, int qty, std::string size, std::string brand):
            Product(category, productName, price, qty)
{
    cSize_ = size;
    cBrand_ = brand;
}

Clothing::~Clothing()
{

}

set<string> Clothing::keywords() const
{
    set<string>returnSet;
    set<string>brandSet;
    
    returnSet = parseStringToWords(cBrand_);
    brandSet = parseStringToWords(name_);

    returnSet.insert(brandSet.begin(), brandSet.end());
    return returnSet;
}

string Clothing::displayString() const
{

    stringstream ss;
    ss << fixed << setprecision(2) << price_; // set to decimal limit of actual USD currency
    // ss.str() is price_ as a string
    string display = name_ + "\nSize: " + cSize_ + " Brand: " + cBrand_ + "\n"
        + ss.str() + " " + to_string(qty_) + " left.";
    return display;
}

void Clothing::dump(std::ostream& os) const
{
    stringstream ss;
    ss << fixed << setprecision(2) << price_;
    // ss.str() is price_ as a string
    string display = "clothing\n" + name_ + "\n" + ss.str() + "\n" + to_string(qty_) + "\n"
        + cSize_ + "\n" + cBrand_;
    os << display << endl;
}