//
// Created by murt on 17.04.18.
//

#ifndef INC_1_2_HASHTABLE_H
#define INC_1_2_HASHTABLE_H

#include <string>
#include <vector>

struct TableElement {
    bool isDeleted;
    std::string data;

    TableElement(const std::string& str): data(str), isDeleted(false)
    {
    };
};

class HashTable {
public:
    HashTable(): capacity(INIT_SIZE), elementsCount(0), hashTable(INIT_SIZE, nullptr)
    {
    };

    bool Add( const std::string& str );
    bool Has( const std::string& str );
    bool Remove( const std::string& str );


private:
    const size_t INIT_SIZE = 8;
    const size_t A_COEFFICIENT = 47;
    const double ALPHA = 0.75;

    size_t hash1( const std::string& str, size_t M );
    size_t hash2( const std::string& str, size_t M );
    void rehash();

    size_t capacity;
    size_t elementsCount;
    std::vector<TableElement*> hashTable;

};

#endif //INC_1_2_HASHTABLE_H
