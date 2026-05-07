//
// Created by admin on 5/5/2026.
//

#ifndef UNTITLED_PAIRCONTAINER_H
#define UNTITLED_PAIRCONTAINER_H

/*
 * paircontainer.h
 *
 *  Created on: Mar. 27, 2025
 *      Author: umroot
 */

#include <iostream>
#include <vector>
#include <utility> // For std::pair
#include <string>

 // Template class for a simple container holding std::pair<T1, T2>
template <typename K, typename V>
class PairContainer { //key value pair database;
    friend class management;
private:

    std::vector<std::pair<K, V>> data;  // Vector of pairs

public:

    // Add a key-value pair to the container
    void insert(const K& key, const V& value) {
        data.emplace_back(key, value); // invoke on vector method emplace_back();
    }




    // Define an iterator using std::vector<std::pair<T1, T2>>::iterator
    using Iterator = typename std::vector<std::pair<K, V>>::iterator;
    using Const_Iterator = typename std::vector<std::pair<K, V>>::const_iterator;



    Iterator begin() { return data.begin(); }  //overloading function;
    Iterator end() { return data.end(); }

    V average(); // traversing every element in the vector which is an object of pair<k,v>
    //pair<k, v> has functions of first() and second();
    void display();

    // Friend function to overload the << operator
    friend std::ostream& operator<<(std::ostream& os, const PairContainer<K, V>& container) {
        //use a const_iterator since container is const

        for (Const_Iterator it = container.data.begin();
            it != container.data.end(); ++it) {
            os << it->first << ", " << it->second << "\n";
        }
        return os;
    }

    // Overload the index operator for non-const access
    std::pair<K, V>& operator[](size_t index) {
        return data[index];
    }

    // Overload the index operator for const access
    const std::pair<K, V>& operator[](size_t index) const {
        return data[index];
    }

    friend std::istream& operator>>(std::istream& is, PairContainer<K, V>& container) {


        while (!is.eof()) {
            K key;
            V value;

            is >> key >> value;

            container.insert(key, value);
        }
        return is;
    }



};



template <typename K, typename V>
V PairContainer<K, V>::average() {
    if (data.empty()) { // vector.empty();
        throw std::runtime_error("Cannot compute average of empty data.");
    }

    V sum{};  // default initialized

    using Const_Iterator = typename std::vector<std::pair<K, V>>::const_iterator;
    for (Const_Iterator it = data.begin(); it != data.end(); ++it) {
        sum += it->second;
    }

    return sum / static_cast<V>(data.size());  //vector.size();
}



//template <typename T1, typename T2>
//void PairContainer<T1, T2>::display() {
//    for (const auto& pair : data) {
//        std::cout << "(" << pair.first << ", " << pair.second << ")\n";
//    }
//}


//template <typename T1, typename T2>
//void PairContainer<T1,T2>::display(){
//	for(const auto& pair: data) {
//
//		std::cout << pair.first <<" " << pair.second <<std::endl;
//	}
//}

template <typename T1, typename T2>
void PairContainer<T1, T2>::display() {

    using myIteratorType = typename std::vector<std::pair<T1, T2>>::iterator;

    for (myIteratorType it = begin(); it != end(); ++it) {
        std::cout << "(" << it->first << ", " << it->second << ")\n";
    }
}



#endif //UNTITLED_PAIRCONTAINER_H