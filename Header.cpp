//
// Created by admin on 5/5/2026.
//

#include "Header.h"
#include<fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
#include "paircontainer.h"



///////////////////////////////////////////////////////////////////
/// TENSOR OPERATOR OVERLOADING
///////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Tensor& other)
{
    for (size_t i = 0; i < other.data.size(); ++i)
    {
        os << other.data[i];
        if (i < other.data.size() - 1)
        {
            os << ",";

        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, Tensor& other)
{
    std::string word;
    while (getline(is, word, ',')) {
		other.data.push_back(word);
    }
	return is;

}

Tensor& Tensor::operator=(const Tensor& other)
{
    if (this != &other)
    {
        data.clear();

        for (size_t i = 0; i < other.data.size(); ++i) {
            data.push_back(other.data[i]);
        }
    }
    return *this;

}
const std::string& Tensor::operator[](int index) const
{
    return data[index];
}
///////////////////////////////////////////////////////////////////
/// CONSTRUCTORS OF TENSOR
///////////////////////////////////////////////////////////////////
Tensor::Tensor(const Tensor& other) :data(other.data)
{}


///////////////////////////////////////////////////////////////////
/// END OF TENSOR

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
/// MANAGEMENT OPERATOR OVERLOADING
///////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const management& other)
{
    for (size_t i = 0; i < other.header.size(); ++i)
    {
        os << other.header[i];
        os << std::endl;
    }

    os << "DATA VALUES: " << std::endl;

    for (size_t i = 0; i < other.tensorlist.size(); ++i)
    {
        os << "LINE:" << i << " [";
        os << other.tensorlist[i];
		os << "]";
        os << std::endl;
        os << std::endl;
    }
    return os;
}



///////////////////////////////////////////////////////////////////
/// OTHER FUNCTION
///////////////////////////////////////////////////////////////////

void management::load(const std::string& filename)
{

	std::ifstream file(filename);
    if (!file)
    {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;

    std::getline(file, line);

    std::stringstream ss(line);
    std::string temporary;

    while (std::getline(ss, temporary, ',')) {
		header.push_back(temporary);
    }
    ++rows;

    while (std::getline(file, line)) {
		ss.clear(); //removes the eof flag and any error flags that may have been set
		ss.str(""); //clears the content of the stringstream
		ss.str(line); //sets the content of the stringstream to the new line read from the file

        Tensor t;
        ss >> t;
        tensorlist.push_back(t);
        ++rows;

    }

}

void management::extract(int begin, int end, std::string path)
{
    if (end > rows-1)
    {
        end = rows - 1;
    }

    if (begin > rows - 1 || begin == end || begin < 0) {
        return;
    }

    std::ofstream file;
    file.open(path);
    if (!file) {
		throw std::runtime_error("Could not open file: " + path);

    }
    for (size_t i = 0; i < header.size(); ++i) {
        file << header[i];
        if (i < header.size() - 1)
        {
            file << ",";
		}
    }

    file << std::endl;

    for (size_t i = 0; i < tensorlist.size(); i++)
    {
		if (i >= begin && i < end) {
            file << tensorlist[i] << std::endl;
        }
    }
    file.close();
}

void management::partition()
{
    int userChoice;
    std::cout << "Enter number of partitions: ";
    std::cin >> userChoice;
    int dataRows = rows - 1;
    int numberofFiles = rows / userChoice;

    int start = 0;
    int end = userChoice;

    for (int i = 0; i <= numberofFiles; i++) {
        extract(start, end, "shard_" + std::to_string(i) + ".txt");
        start = start + userChoice;
        end = end + userChoice;
    }

}

PairContainer<int, double> management::extractColValues(std::string colName1, std::string colName2)

{
    auto it1 = std::find(header.begin(), header.end(), colName1);
    auto it2 = std::find(header.begin(), header.end(), colName2);

    if (it1 == header.end() || it2 == header.end())
        throw std::runtime_error("Column names not found");

    int idx1 = std::distance(header.begin(), it1);
    int idx2 = std::distance(header.begin(), it2);

    PairContainer<int, double> container;

    for (const auto& element : tensorlist)
    {
		container.insert(std::stoi((element)[idx1]), std::stod((element)[idx2]));
    }
    return container;

}


void management::analyzeflows(PairContainer<int, double>& other)
{
    auto start = std::chrono::high_resolution_clock::now();

    double total = 0.0;

    for (const auto& pair : other.data) {
        total += pair.second;
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    std::cout << "Total flow: " << total << " sec" << std::endl;
    std::cout << "Time taken to analyze: " << elapsed.count() << " seconds" << std::endl;
}