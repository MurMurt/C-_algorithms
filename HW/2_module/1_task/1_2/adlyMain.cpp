//
// Created by murt on 18.04.18.
//

#include <iostream>
#include <assert.h>
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
    size_t capacity;
    size_t elementsCount;
    std::vector<TableElement*> hashTable;

    size_t hash1( const std::string& str, size_t M );
    size_t hash2( const std::string& str, size_t M );
    void rehash();
};


int main() {
    HashTable hashTable;

    char command = 0;
    std::string key;
    while( std::cin >> command >> key ) {
        switch( command ) {
            case '?':
                std::cout << ( hashTable.Has( key ) ? "OK" : "FAIL" ) << std::endl;
                break;
            case '+':
                std::cout << ( hashTable.Add( key ) ? "OK" : "FAIL" ) << std::endl;
                break;
            case '-':
                std::cout << ( hashTable.Remove( key ) ? "OK" : "FAIL" ) << std::endl;
                break;
            default:
                assert( false );
        }
    }
    return 0;
}

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