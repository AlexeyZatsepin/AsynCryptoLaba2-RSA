#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/common_factor.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

#include <algorithm>
#include <time.h>

#define uint_t uint256_t

using namespace boost::multiprecision;

namespace Generator{
    boost::mt19937 rng;
    boost::uniform_int<> one_to_six(0, 255);
    boost::variate_generator<boost::mt19937, boost::uniform_int<>> dice(rng, one_to_six);
    int next(){
//        std::srand((unsigned)i);
        return std::rand() % 2;
    }

    uint_t generate(int N){
        uint_t n = 0;
        for (auto i=0;i < N/8;i++){
            auto t = dice();
            auto temp = t << i;
            n = n | temp;
        }
        return n;
    }

}