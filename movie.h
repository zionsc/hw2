#ifndef MOVIE_H
#define MOVIE_H

#include <set>
#include <string>
#include "product.h"

class Movie: public Product
{
    public:
        Movie(const std::string category, const std::string productName,
            double price, int qty, std::string genre, std::string rating);

        ~Movie();

        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;

    private:
        std::string mGenre_;
        std::string mRating_;
};

#endif