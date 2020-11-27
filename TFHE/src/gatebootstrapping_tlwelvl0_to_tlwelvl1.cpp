/*
    gen testvector(,key)

    Blind_Rotate()

*/

#include<array>
#include<vector>
#include<random>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>
#include<../include/common.hpp>
#include<../RANDEN/randen.h>

namespace myTFHE{
    using namespace std;

    // gen testvector() return TRLWElvl1

    TRLWElvl1 gen_testvector(){

        // plain message(DEF_myu)
        array<uint32_t,DEF_N> myu;
        for(int i=0;i<DEF_N;i++) myu[i]=DEF_myu;

        // a[x]=0, b[x]=myu[x]
        TRLWElvl1 res_trlwe;
        for(int i=0;i<DEF_N;i++){
            res_trlwe[0][i]=0;
        }
        res_trlwe[1]=myu;

        return res_trlwe;
    }
    // //
    // template<typename T=uint32_t, uint32_t N=DEF_N, uint32_t n=DEF_n, double abk=DEF_abk>
    // BootStrappingKeyFFTlvl01 gen_bootstrapping_key(const array<T,n> &)


    // gen bootstrapping_key(lvekey lvl0, lwekey lvl1) return bk;
//    template<tpyename T = uint32_t, uint32_t N=DEF_N,uint32_t n=DEF_n>
    BootStrappingKeyFFTlvl01 gen_bootstrapping_key(secretkey &sk){

        // TRGSW encrypt key.lvl0 bit-by-bit
        BootStrappingKeyFFTlvl01 bk;

        for(int i=0;i<DEF_n;i++){
            int32_t Keylvl0 = static_cast<typename make_signed<uint32_t>::type>(sk.key.lvl0[i]);

            bk[i] = trgsw_fft_Enc_lvl1(Keylvl0,DEF_abk,sk.key.lvl1);
        }

        return bk;
    }

    void Poly_Mul_By_X_i(Polynomiallvl1 &res, const Polynomiallvl1 &rot, const uint32_t til){
        if(til < DEF_N){
            for(int i=0;i<(DEF_N - til);i++)
                res[i+til] = rot[i];
            for(int i=(DEF_N-til);i<DEF_N;i++)
                res[i+til-DEF_N] = -rot[i];
        }else{
            uint32_t l=til-DEF_N;
            for(int i=0;i<(DEF_N - l);i++)
                res[i+l] = -rot[i];
            for(int i=(DEF_N - l);i<DEF_N;i++)
                res[i+l-DEF_N] = rot[i];
        }
    }

    // Blind_Rotate (TRLWElvl1 *testvector, TLWElvl0 *tlwe, vector<TRGSWFFTlvl1> *bk) return trlwe
    TRLWElvl1 Blind_Rotate(TRLWElvl1 &res_trlwe,const TRLWElvl1 &testvector, const TLWElvl0 &tlwe, const BootStrappingKeyFFTlvl01 &bk){
        
        // b_til  tlwe bの丸め
        uint32_t b_til = 2*DEF_N - (tlwe[DEF_n] +(1 << (31 - DEF_Nbit -1)) >> (32 - DEF_Nbit -1));
        
        TRLWElvl1 trlwe0;
        for(int i=0;i<DEF_N;i++){
            trlwe0[0][i] = 0;
            trlwe0[1][i] = 0;
        }

        // Rotate   trlwe0 = X^(b_til) * testvector 
        Poly_Mul_By_X_i(trlwe0[0],testvector[0],b_til);
        Poly_Mul_By_X_i(trlwe0[1],testvector[1],b_til);

        // 
        for(int i=0;i<DEF_n;i++){
            TRLWElvl1 trlwe1 = trlwe0;
            // a_til tlwe aの丸め
            uint32_t a_til = (tlwe[0] +(1 << (31 - DEF_Nbit -1)) >> (32 - DEF_Nbit -1));

            // Rotate trlwe1 = X^(a_til) * trlwe0
            Poly_Mul_By_X_i(trlwe1[0],trlwe0[0],a_til);
            Poly_Mul_By_X_i(trlwe1[1],trlwe0[1],a_til);

            // CMUX Dec(BK_i) ? trlwe1 : trlwe0
            CMUX_lvl1(res_trlwe,bk[i],trlwe1,trlwe0);
        }

        return res_trlwe;
    }
}