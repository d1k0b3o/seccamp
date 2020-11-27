#pragma once

#include<array>
#include<random>
#include<vector>
#include<../include/tfhe++.hpp>

namespace myTFHE{
    using namespace std;

    vector<TLWElvl0> tlwe_Enc(const vector<uint8_t> &m,const secretkey &sk);
    TLWElvl0 tlwe_Enc_lvl0(const uint32_t m,const double alpha,const lwekeylvl0 &key);
    vector<uint8_t> tlwe_Dec(const vector<TLWElvl0> c,const secretkey &sk);
    bool tlwe_Dec_lvl0(const TLWElvl0 &c,const lwekeylvl0 &key);
    bool tlwe_Dec_lvl1(const TLWElvl1 &c, const lwekeylvl1 &key);
    

}// myTFHE

