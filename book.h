#ifndef BOOK_H
#define BOOK_H // prevent multiple inclusion

#include <set>
#include <string>
#include "product.h"

class Book: public Product 
{
    public:
        Book(const std::string category, const std::string productName, 
        double price, int qty, std::string isbn, std::string author);
        ~Book();

        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;

    private:
        std:: string isbnNumber_;
        std::string authorName_;
};  


#endif