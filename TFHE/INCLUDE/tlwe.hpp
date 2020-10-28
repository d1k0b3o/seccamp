#pragma once
#include<array>
#include<random>
#include<vector>
#include</home/hagarikuo/seccamp/TFHE/INCLUDE/params.hpp>
#include</home/hagarikuo/seccamp/TFHE/INCLUDE/common.hpp>
#include</home/hagarikuo/seccamp/TFHE/INCLUDE/key.hpp>

namespace myTFHE{
    using namespace std;

    vector<TLWElvl0> tlweEnc(const vector<uint8_t> &m,const secretkey &sk);
    TLWElvl0 tlweEnclvl0(const uint32_t m,const double alpha,const lwekeylvl0 &key);
    

}// myTFHE
