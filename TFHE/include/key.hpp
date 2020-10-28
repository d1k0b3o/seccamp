#pragma once
#include</home/hagarikuo/seccamp/TFHE/include/params.hpp>
#include<array>
#include<vector>
#include<random>
#include</home/hagarikuo/seccamp/TFHE/RANDEN/randen.h>

namespace myTFHE{
using namespace std;

struct lwekey{
    lwekeylvl0 lvl0;
    lwekey(){
        // 乱数生成
        randen::Randen<uint64_t> engine;

        // bainaryの一様分布を生成
        uniform_int_distribution<uint32_t> binary(0,1);
        
        // 鍵生成 lvl0,
        for(uint32_t &i : lvl0) i=binary(engine);
    }
};

struct secretkey{
    lwekey key;
    lweparams params;
    secretkey(){
        lwekey KEY;
        key = KEY;
    }

};

}// myTFHE
