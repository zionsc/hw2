#include "mydatastore.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

MyDataStore::MyDataStore() 
{

}

MyDataStore::~MyDataStore() 
{
    set<Product*>::iterator itr;
    for (itr=product_.begin(); itr!=product_.end(); ++itr) {
        delete *itr;
    }
    set<User*>::iterator itr2;
    for (itr2=userVal_.begin(); itr2!=userVal_.end(); ++itr2) {
        delete *itr2;
    }
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    
    set<Product*> tempSet1;
    set<Product*> tempSet2;
    set<Product*> intersectionSet;
    vector<Product*> tempVec;
   // cout << searchProduct_.size() << "search size" << endl;

    if (terms.size() > 1) {
        if (type == 0) {
           // cout << "type 0" << endl;
            //cout << "type = 0" <<endl;

           // std::map<std::string, std::set<Product*>>::iterator itr__;

            // for (itr__=searchProduct_.begin(); itr__!=searchProduct_.end(); ++itr__) {
            //     cout << itr__->first << endl;
            // }
            //cout << "seperate" <<endl;



            for (size_t i=0; i<terms.size(); ++i) {
                if (i==0) {
                   // cout << "first" << endl;
                   // cout << (searchProduct_.find(terms[0]) == searchProduct_.end()) << "not found" << endl;
                    //cout << terms[0] <<"term 0" <<endl;
                    tempSet1 = searchProduct_[terms[0]];
                    //cout << tempSet1.size() << "frist size" << endl;
                }
                else {
                   // cout << "intersection" << endl;
                   // cout << tempSet1.size() << endl;
                    tempSet1 = setIntersection(tempSet1, searchProduct_[terms[i]]);
                }
                
            }

            //     cout << terms[i] << endl;
            //     if (searchProduct_.find(terms[i]) != searchProduct_.end()) {
            //         tempSet1 = searchProduct_[terms[i]];
            //         cout << "hello print" <<endl;
            //         cnt++;
            //         break;
            //     }
            //     cnt++;
            // }
            // for (size_t i=cnt; i<terms.size(); ++i) {
            //     if (searchProduct_.find(terms[i]) != searchProduct_.end()) {
            //         tempSet2 = searchProduct_[terms[i]];
            //         set<Product*> tempSet3 = tempSet1;
            //         tempSet1 = setIntersection(tempSet3, tempSet2);
            //     }
            // }
        }
        else if (type == 1) {
            // for (size_t i=0; i<terms.size(); ++i) {
            //     if (searchProduct_.find(terms[i]) != searchProduct_.end()) {
            //         cnt++;
            //         tempSet1 = searchProduct_[terms[i]];
            //         break;
            //     }
            //     cnt++;
            // }
            // for (size_t i=cnt; i<terms.size(); ++i) {
            //     if (searchProduct_.find(terms[i]) != searchProduct_.end()) {
            //         tempSet2 = searchProduct_[terms[i]];
            //         set<Product*> tempSet4;
            //         tempSet4 = setUnion(tempSet1, tempSet2);
            //         tempSet1 = tempSet4;
            //     }
            // }
            for (size_t i=0; i<terms.size(); ++i) {
                if (i==0) {
                    tempSet1 = searchProduct_[terms[0]];
                }
                else {
                    tempSet1 = setUnion(tempSet1, searchProduct_[terms[i]]);
                }
                
            }

        }
    }
    else {
        if (terms.size() <= 1) {
            if (searchProduct_.find(terms[0]) != searchProduct_.end()) {
                tempSet1 = searchProduct_[terms[0]];
            }
        }
    }
    set<Product*>::iterator itr3;
    for (itr3=tempSet1.begin(); itr3 != tempSet1.end(); ++itr3) {
        tempVec.push_back(*itr3);
        //cout << (*itr3) -> getName() << endl;
      //  cout << "bottom print" << endl;
    }
   // cout << tempVec.size() <<endl;
    return tempVec;
}

void MyDataStore::addProduct(Product *p) 
{
    product_.insert(p);
    set<string>::iterator itr;
    set<string> list = p->keywords();

 //   cout << list.size() << "size of adding prod" << endl;

    for (itr=list.begin(); itr!=list.end(); ++itr) {
     //   cout << *itr << " keyword" << endl;
        if (searchProduct_.find(*itr) == searchProduct_.end()) { // if not found, add make_pair
            set<Product*> tempProduct;
            // tempProduct.insert(p);
            searchProduct_.insert(make_pair((*itr), tempProduct));
        }
        // else { // add new value to key
            searchProduct_[*itr].insert(p);
        // }
    }
}

void MyDataStore::addUser(User* u) 
{
    string uName = u->getName();
    userVal_.insert(u);
    user_.insert(make_pair(uName, u));
}

void MyDataStore::viewcart(std::string username)
{
  //  cout << "view cart " << username << endl;
    if (cart_.find(username) == cart_.end()) {
        cout << "Invalid username." << endl;
    }
    else {
        vector<Product*> product1 = cart_[username]; // cart_ val is vec of Product*
        for (size_t i=0; i<product1.size(); ++i) {
            cout << "Item: " << i+1 << '\n' <<
            (product1[i])->displayString() << endl;
        }
    }
}

void MyDataStore::buycart(std::string username)
{


    if (user_.find(username) == user_.end() || cart_.find(username) == cart_.end()) {
      cout << "Invalid username" << endl;
      return;
    } 
    else {
        vector<Product*> unboughtProduct = {};
        std::vector<Product*>::iterator itr4;
        for (itr4=cart_[username].begin(); itr4!=cart_[username].end(); ++itr4) {
            double credit = (user_[username])->getBalance();
            int qtyLeft = (*itr4)->getQty();
            double totalPrice = (*itr4)->getPrice();
            if (qtyLeft == 0 || credit < totalPrice) {
                unboughtProduct.push_back(*itr4);
                continue;
            }
            else {
                (user_[username])->deductAmount(totalPrice);
                (*itr4)->subtractQty(1);
            }
        }
        cart_[username] = unboughtProduct;
        // items not bought kept in the cart
    }
}

void MyDataStore::addcart(std::string username, Product *p)
{
    //cout <<"ADDING"<<endl;
    if (user_.find(username) == user_.end()) {
      cout << "Invalid Request" << endl;
      return;
    }

    if (cart_.find(username) != cart_.end()) { // user has cart
        if (p->getQty() != 0) {
           // cout <<"cart found"<<endl;
            cart_[username].push_back(p);

        }
        else {
            cout << "Product is out of stock." << endl;
        }
    }

    else if (user_.find(username) != user_.end()) { // user no cart
        //cout <<"new cart"<<endl;
        if (p->getQty() != 0) {
           // cout <<"adding item"<<endl;
            std::vector<Product*> product3;
            product3.push_back(p);
            cart_.insert(make_pair(username, product3));
            
            //cout << "Successfuly added to the cart!" << endl;
        }
        else {
            cout << "Product is out of stock." << endl;
        }
    }
    
    else {
        cout << "Invalid Request" << endl;
    }
}  

void MyDataStore::dump(std::ostream &ifile) 
{
    ifile << "<products>" << endl;

    for (set<Product*>::iterator itr5=product_.begin(); itr5!=product_.end(); ++itr5) {
        (*itr5)->dump(ifile);
    }

    ifile << "</products>" << endl;

    ifile << "<users>" << endl;

    for (set<User*>::iterator itr6=userVal_.begin(); itr6!=userVal_.end(); ++itr6) {
        (*itr6)->dump(ifile);
    }
    ifile << "</users>" << endl;
}