#pragma once
#include<array>
#include<random>
#include<vector>
#include<../include/params.hpp>
#include<../include/common.hpp>
#include<../include/key.hpp>

namespace myTFHE{
    using namespace std;

    vector<TLWElvl0> tlweEnc(const vector<uint8_t> &m,const secretkey &sk);
    TLWElvl0 tlweEnclvl0(const uint32_t m,const double alpha,const lwekeylvl0 &key);
    vector<uint8_t> tlweDec(const vector<TLWElvl0> c,const secretkey &sk);
    bool tlweDeclvl0(const TLWElvl0 &c,const lwekeylvl0 &key);
    

}// myTFHE

