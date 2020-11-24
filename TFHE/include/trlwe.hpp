#pragma onece

#include<array>
#include<random>
#include<vector>
#include<../RANDEN/randen.h>
//#include<../SPQLIOS/spqlios-fft.h>
#include<../include/tfhe++.hpp>

namespace myTFHE{
    using namespace std;

    TRLWElvl1 trlwe_Enc_Zero_lvl1(const double abk,const lwekeylvl1 &key);
    TRLWElvl1 trlwe_Enc_lvl1(const array<uint32_t,DEF_N> &myu,const double abk,const lwekeylvl1 &key);
    array<bool,DEF_N> trlwe_Dec_lvl1(const TRLWElvl1 &c,const lwekeylvl1 &key);
    
    // void SampleExtractIndex(array<T,N+1> &tlwe,const array<array<T,N>,2> &trlwe, const int index);
    // void SampleExtractIndexlvl1(TLWElvl1 &tlwe, const TRLWE &trlwe, const int index);

}// myTFHE

