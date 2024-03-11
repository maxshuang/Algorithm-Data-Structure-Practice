#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "hash_table.h"

TEST_CASE("Test HashTable Delete", "[hash table]")
{
    SECTION("Test deleting a key that exists in the hash table")
    {
        HashTable hashTable;
        hashTable.Put(1, 4);
        hashTable.Put(2, 5);
        hashTable.Put(3, 6);

        hashTable.Delete(2);

        REQUIRE(hashTable.Get(2) == -1);
        REQUIRE(hashTable.Get(1) == 4);
        REQUIRE(hashTable.Get(3) == 6);
    }

    SECTION("Test deleting a key that does not exist in the hash table")
    {
        HashTable hashTable;
        hashTable.Put(1, 4);
        hashTable.Put(2, 5);
        hashTable.Put(3, 6);

        hashTable.Delete(4);

        REQUIRE(hashTable.Get(4) == -1);
        REQUIRE(hashTable.Get(1) == 4);
        REQUIRE(hashTable.Get(2) == 5);
        REQUIRE(hashTable.Get(3) == 6);
    }

    SECTION("Test deleting a key from an empty hash table")
    {
        HashTable hashTable;

        hashTable.Delete(1);

        REQUIRE(hashTable.Get(1) == -1);
    }
}

TEST_CASE("Test rehash for hash table", "[rehash]")
{
    SECTION("add many elements to the hash table")
    {
        HashTable hashTable;
        for (int i = 0; i < 8; ++i)
        {
            hashTable.Put(i, i);
        }

        REQUIRE(hashTable.Size() == 8);
        REQUIRE((hashTable.LoadFactor() - 8.0 / 13) < 0.01);

        for (int i = 8; i < 11; ++i)
        {
            hashTable.Put(i, i);
        }
        // should be trigger rehash
        REQUIRE(hashTable.Size() == 11);
        REQUIRE((hashTable.LoadFactor() - 11.0 / 26) < 0.01);

        for (int i = 0; i < 11; ++i)
        {
            REQUIRE(hashTable.Get(i) == i);
        }
        REQUIRE(hashTable.Get(12) == -1);
        REQUIRE(hashTable.Get(13) == -1);
    }

    SECTION("delete many elements to the hash table")
    {
        HashTable hashTable;
        for (int i = 0; i < 11; ++i)
        {
            hashTable.Put(i, i);
        }
        // should be trigger rehash
        REQUIRE(hashTable.Size() == 11);
        REQUIRE((hashTable.LoadFactor() - 11.0 / 26) < 0.01);

        for (int i = 0; i < 9; ++i)
        {
            hashTable.Delete(i);
        }
        REQUIRE(hashTable.Size() == 2);
        REQUIRE((hashTable.LoadFactor() - 2.0 / 13) < 0.01);

        for (int i = 0; i < 9; ++i)
        {
            REQUIRE(hashTable.Get(i) == -1);
        }
        REQUIRE(hashTable.Get(9) == 9);
        REQUIRE(hashTable.Get(10) == 10);
    }
}

TEST_CASE("Test getPrime", "[getPrime]")
{
    SECTION("Test getting prime number for small input")
    {
        REQUIRE(getPrime(3) == std::vector<int>{2,3});
        REQUIRE(getPrime(5) == std::vector<int>{2,3,5});
        REQUIRE(getPrime(10) == std::vector<int>{2,3,5,7});
        REQUIRE(getPrime(15) == std::vector<int>{2,3,5,7,11,13});
    }

    SECTION("Test getting prime number for large input")
    {
        std::vector<int> prime1=getPrime(100);
        for(int i: prime1) {
            REQUIRE(isPrime(i));
        }
        std::vector<int> prime2=getPrime(100000);
        for(int i: prime2) {
            REQUIRE(isPrime(i));
        }
    }
}

TEST_CASE("Test findNextPrime", "[findNextPrime]")
{
    SECTION("Test finding next prime number for small input")
    {
        REQUIRE(findNextPrime(5) == 7);
        REQUIRE(findNextPrime(10) == 11);
        REQUIRE(findNextPrime(15) == 17);
    }

    SECTION("Test finding next prime number for large input")
    {
        REQUIRE(findNextPrime(100) == 101);
        REQUIRE(findNextPrime(1000) == 1009);
        REQUIRE(findNextPrime(10000) == 10007);
    }
}
