#ifndef CLOTHING_H
#define CLOTHING_H

#include <set>
#include <string>
#include "product.h"

class Clothing: public Product 
{
    public:
        Clothing(const std::string category, const std::string productName,
            double price, int qty, std::string size, std::string brand);

        ~Clothing();

        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;

    private:
        std::string cSize_;
        std::string cBrand_;
};


#endif