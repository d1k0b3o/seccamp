#pragma onece

#include<array>
#include<random>
#include<vector>
#include<limits>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>
#include<../include/mulfft.hpp>
#include<../include/common.hpp>

namespace myTFHE{

    TRGSWlvl1 trgsw_Enc_lvl1(int32_t p, double abk, lwekeylvl1 &key);
    TRGSWFFTlvl1 trgsw_fft_Enc_lvl1(int32_t p, double abk, lwekeylvl1 &key);

    void trgsw_External_Product_lvl1(TRLWElvl1 &res, const TRLWElvl1 &trlwe, const TRGSWFFTlvl1 &trgswfft);
}

