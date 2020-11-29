#include<array>
#include<vector>
#include<random>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>
#include<../include/common.hpp>
#include<../RANDEN/randen.h>

namespace myTFHE{
    
    TRLWElvl1 gen_testvector();
    //BootStrappingKeyFFTlvl01 gen_bootstrapping_key(lwekeylvl0 *keylvl0,lwekeylvl1 *keylvl1);
    BootStrappingKeyFFTlvl01 gen_bootstrapping_key(lwekeylvl0 &lvl0, lwekeylvl1 &lvl1);
    TRGSWFFTlvl1 gen_bootstrapping_key2(uint32_t lvl0, lwekeylvl1 &lvl1);
    void gen_bootstrapping_key3(BootStrappingKeyFFTlvl01 &res_bk,array<int32_t,DEF_n> &tmp,lwekeylvl1 &lvl1);


    void Poly_Mul_By_X_i(Polynomiallvl1 &res, const Polynomiallvl1 &rot, const uint32_t til);
    TRLWElvl1 Blind_Rotate(TRLWElvl1 &res_trlwe,const TRLWElvl1 &testvector, const TLWElvl0 &tlwe, const BootStrappingKeyFFTlvl01 &bk);

} // myTFHE