#pragma onece

#include<array>
#include<random>
#include<vector>
#include<../RANDEN/randen.h>
//#include<../SPQLIOS/spqlios-fft.h>
#include<../include/tfhe++.hpp>

namespace myTFHE{
    using namespace std;

    TRLWElvl1 trlweEncZerolvl1(const double abk,const lwekeylvl1 &key);
    TRLWElvl1 trlweEnclvl1(const array<uint32_t,DEF_N> &myu,const double abk,const lwekeylvl1 &key);

}// myTFHE

