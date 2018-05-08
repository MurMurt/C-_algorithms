//
// Created by murt on 17.04.18.
//

#include <iostream>
#include "HashTable.h"

size_t HashTable::hash1( const std::string &str, size_t M )
{
    size_t hash = 0;
    for( int i = 0; i < str.size(); ++i ) {
        hash = ( hash * A_COEFFICIENT + str[i] ) % M;
    }
    return hash;
}

size_t HashTable::hash2( const std::string &str, size_t M )
{
    return 2 * hash1( str, M ) + 1;
}

bool HashTable::Add( const std::string& str )
{
    if( ( double )elementsCount / capacity >= ALPHA) {
        rehash();
        std::cout << "___REHASHED___" << std::endl;
    }

    size_t hashValue = hash1( str, capacity );
    size_t hashValue2 = hash2( str, capacity );
    int firstDeletedIndex = -1;

    int i = 0;
    while( hashTable[hashValue] != nullptr && i < capacity ) {
        // Проверка на вхождение
        if( hashTable[hashValue]->data == str && !hashTable[hashValue]->isDeleted ) {
            return false;
        }
        // Нахождение первого удаленного элемента
        if( hashTable[hashValue]->isDeleted && firstDeletedIndex < 0 ) {
            firstDeletedIndex = hashValue;
        }
        //Вычисление нового значения хеша
        hashValue = ( hashValue + hashValue2 ) % capacity;
        ++i;
    }
    if( firstDeletedIndex > 0 ) {
        hashTable[hashValue]->data = str;
        hashTable[hashValue]->isDeleted = false;
    } else {
        hashTable[hashValue] = new TableElement(str);
    }
    ++elementsCount;
    return true;
}

void HashTable::rehash()
{
    size_t newCapacity = capacity * 2;
    std::vector<TableElement*> newHashTable(newCapacity, nullptr);
    for( int i = 0; i < capacity; ++i ) {
        if( hashTable[i] != nullptr && !hashTable[i]->isDeleted ) {
            size_t hashValue = hash1(hashTable[i]->data, newCapacity);
            size_t hashValue2 = hash2(hashTable[i]->data, newCapacity);

            int j = 0;
            while( newHashTable[hashValue] != nullptr && j < newCapacity ) {
                hashValue = ( hashValue + hashValue2 ) % newCapacity;
                ++j;
            }
            newHashTable[hashValue] = new TableElement(hashTable[i]->data);
        }
    }
    hashTable = newHashTable;
    capacity = newCapacity;
}

bool HashTable::Has( const std::string& str )
{
    size_t hashValue = hash1(str, capacity);
    size_t hashValue2 = hash2(str, capacity);

    int i = 0;
    while( hashTable[hashValue] != nullptr && i < capacity ) {
        if( hashTable[hashValue]->data == str && !hashTable[hashValue]->isDeleted ) {
            return true;
        }
        hashValue = ( hashValue + hashValue2 ) % capacity;
        ++i;
    }
    return false;
}

bool HashTable::Remove( const std::string& str )
{
    size_t hashValue = hash1(str, capacity);
    size_t hashValue2 = hash2(str, capacity);

    int i = 0;
    while( hashTable[hashValue] != nullptr && i < capacity ) {
        if( hashTable[hashValue]->data == str && !hashTable[hashValue]->isDeleted ) {
            hashTable[hashValue]->isDeleted = true;
            return true;
        }
        hashValue = ( hashValue + hashValue2 ) % capacity;
        ++i;
    }
    return false;

}