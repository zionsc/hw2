#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>
#include <vector>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2) // A & B
{
    std::set<T> intersection;

 //std::cout << s1.size() << " " << s2.size() << "size " << std::endl;
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), 
    std::inserter(intersection, intersection.begin()));

    // std::cout << s1.size() << " " << s2.size() << "size " << std::endl;

    
    // typename std::set<T>::iterator itr;
    // for (itr=s1.begin(); itr!=s1.end(); ++itr) {
    //     if (s2.find(*itr) != s2.end()) { // if not found in s2, returns end index
    //         intersection.insert(*itr);
    //     }
    // }
    

    return intersection;



}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2) // A U B
{

    std::vector<T> vec;

    vec.reserve(s1.size() + s2.size());
    std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(vec));

    return std::set<T>(vec.begin(), vec.end());


    
    // std::set<T> setUnion;
    // typename std::set<T>::iterator itr;
    // for (itr=s1.begin(); itr!=s1.end(); ++itr) {
    //     setUnion.insert(*itr);
    // }
    
    // typename std::set<T>::iterator itr_;
    // for (itr_=s2.begin(); itr_!=s2.end(); +itr_) {
    //     if (setUnion.find(*itr_) == setUnion.end()) {
    //         setUnion.insert(*itr_);
    //     }
    //     else if (setUnion.find(*itr_) != setUnion.end()) { // if found somewhere in the set already w/ union
    //         continue;
    //     }
    // }
    // return setUnion;
    

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
