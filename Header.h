//
// Created by admin on 5/5/2026.
//

#ifndef UNTITLED_HEADER_H
#define UNTITLED_HEADER_H

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include<sstream>
#include<ostream>
#include <istream>
#include "paircontainer.h"

class Tensor {
    friend std::ostream& operator<<(std::ostream& os, const Tensor& other);
    friend std::istream& operator>>(std::istream& is, Tensor& other);

private:
    std::vector<std::string>data;
public:
    using Iterator = typename std::vector<std::string>::iterator;

    Tensor()=default;
    Tensor(const Tensor& other);
    ~Tensor() = default;

    Tensor& operator=(const Tensor& other);
    const std::string& operator[](int index) const;

};

class management {

    friend std::ostream& operator<<(std::ostream& os, const management& other);

private:
    std::vector<std::string> header;
    std::vector<Tensor> tensorlist;
    int rows;

public:
    using Iterator = typename std::vector<std::string>::iterator;
    using TensorIterator = typename std::vector<Tensor>::iterator;

    management() = default;
    ~management() = default;

    void load(const std::string& filename);
    void extract(int begin, int end, std::string path);
    void partition();
    PairContainer<int, double> extractColValues(std::string colName1, std::string colName2);
    void analyzeflows(PairContainer<int, double>& other);

    Iterator begin() { return header.begin(); }
    Iterator end() { return header.end(); }

    TensorIterator tensorBegin() { return tensorlist.begin(); }
    TensorIterator tensorEnd() { return tensorlist.end(); }



};



#endif //UNTITLED_HEADER_H