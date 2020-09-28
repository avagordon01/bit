#include "bit.hh"
#include <iostream>
#include <bitset>
#include <random>
#include <gtest/gtest.h>

TEST(bit, basic_functions){
    using T = std::bitset<64>;
    ASSERT_TRUE((T{~0LLU}).all());
    ASSERT_TRUE((T{0LLU}).none());
    ASSERT_FALSE((T{0LLU}).any());
    ASSERT_TRUE((T{1LLU}).any());
    ASSERT_EQ((T{3LLU}).count(), 2);
}

size_t seed = 0xfeed;
size_t num_trials = 1000;
std::mt19937 engine(seed);
std::uniform_int_distribution<uint64_t> input_distribution;

#ifdef TYPE
using T = TYPE;
#else
using T = unsigned long long;
#endif

TEST(bit, fuzz_count){
    constexpr size_t len = std::numeric_limits<T>::digits;
    std::uniform_int_distribution<size_t> set_distribution(0, len - 1);
    for(size_t i = 0; i < num_trials; i++) {
        std::bitset<len> b;
        size_t pos = set_distribution(engine);
        b.set(pos);
        T x = b.to_ullong();
        ASSERT_EQ(bit::countl_zero(x), len - 1 - pos);
        ASSERT_EQ(bit::countr_zero(x), pos);
    }
}
