#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "util.h"
#include <map>
#include <vector>
#include <set>
#include <string>

class MyDataStore: public DataStore 
{
    public:
        MyDataStore();
        ~MyDataStore();

    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);
    virtual void addProduct(Product *p);
    virtual void addUser(User *u);

    virtual void dump(std::ostream &ifile);
    void viewcart(std::string username);
    void buycart(std::string username);
    void addcart(std::string username, Product *p);

    private:
        std::set<Product*> product_;
        std::map<std::string, User*> user_;
        std::map<std::string, std::vector<Product*>> cart_;

        std::map<std::string, std::set<Product*>> searchProduct_;
        std::set<User*> userVal_;
};

#endif