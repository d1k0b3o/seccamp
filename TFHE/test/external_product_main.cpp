/*

TRGSW x TRLWE -> TRLWE

*/
#include<iostream>
#include<array>
#include<vector>
#include<random>
#include<cassert>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>
#include<../RANDEN/randen.h>
#include<../include/common.hpp>



int main(){

    using namespace myTFHE;
    using namespace std;
    
    // random
    randen::Randen<uint64_t> engine;
    uniform_int_distribution<uint32_t> binary(0,1);

    // test
    const uint32_t num_test = 1000;

    // 1 の TRGSW で External Product TRLWE x 1 だから結果は計算前のTRLWEと変わらないはず  
    cout << "lvl1:TRGSW(1)" << endl;
    for(int test=0;test<num_test;test++){

        // cout << "test:" << test << endl;
        
        //lvl1鍵 key 生成
        lwekey key;

        // TRLWE の平文 m 生成
        array<bool,DEF_N> m;
        for(bool &i: m) i = (binary(engine)>0);

        // cout << "gen message done" << endl;
        
        // m -> myu
        // array<uint32_t,DEF_N>
        Polynomiallvl1 myu;
        for(int i=0;i<DEF_N;i++){
            myu[i]= m[i] ? DEF_myu : -DEF_myu;
        }

        // cout << "m->myu done" << endl;
        
        // TRLWE で m の暗号化  暗号文 c の生成
        // TRLWElvl1 = array<array<uint32_t,DEF_N>,DEF_N> N x N
        TRLWElvl1 c = trlwe_Enc_lvl1(myu,DEF_abk,key.lvl1);

        // cout << "enc m done" << endl;

        // TRGSW の平文は 1　暗号文trgsw の生成
        // TRGSWFFTlvl1 = array<array<array<double,DEF_N>,2>,2*DEF_l>  
        TRGSWFFTlvl1 trgswfft = trgsw_fft_Enc_lvl1(1,DEF_abk,key.lvl1);

        // cout << "gen trgswfft done" << endl;

        // External Product
        // TRGSW x TRLWE -> TRLWE  c に結果(TRLWE)が返る
        trgsw_External_Product_lvl1(c,c,trgswfft);

        // cout << "external product done" << endl;

        // TRLWE で c の復号 復号したものをm2とする。
        array<bool,DEF_N> m2 = trlwe_Dec_lvl1(c,key.lvl1);

        // cout << "dec c done" << endl;
        
        // TRGSWは 1 だから　m==m2 のはず
        // for(int i=0;i<DEF_N;i++) cout << (m[i] ? 1:0);
        // cout << endl;
        // for(int i=0;i<DEF_N;i++) cout << (m2[i] ? 1:0);
        // cout << endl;
        for(int i=0;i<DEF_N;i++) assert(m[i]==m2[i]);

        // cout << "check done" << endl;
    }
    cout << "lvl1:TRGSW(1):PASSED!" << endl;

    // -1 の TRGSW で External Product TRLWE x (-1) だから結果は計算前と符号が反転しているはず -> 一致している箇所が無い
    cout << "lvl1:TRGSW(-1)" << endl;
    for(int test=0;test<num_test;test++){

        // cout << "test:" << test << endl;
        
        //lvl1鍵 key 生成
        lwekey key;

        // TRLWE の平文 m 生成
        array<bool,DEF_N> m;
        for(bool &i: m) i = (binary(engine)>0);

        // cout << "gen message done" << endl;
        
        // m -> myu
        // array<uint32_t,DEF_N>
        Polynomiallvl1 myu;
        for(int i=0;i<DEF_N;i++){
            myu[i]= m[i] ? DEF_myu : -DEF_myu;
        }

        // cout << "m->myu done" << endl;
        
        // TRLWE で m の暗号化  暗号文 c の生成
        // TRLWElvl1 = array<array<uint32_t,DEF_N>,DEF_N> N x N
        TRLWElvl1 c = trlwe_Enc_lvl1(myu,DEF_abk,key.lvl1);

        // cout << "enc m done" << endl;

        // TRGSW の平文は 1　暗号文trgsw の生成
        // TRGSWFFTlvl1 = array<array<array<double,DEF_N>,2>,2*DEF_l>  
        TRGSWFFTlvl1 trgswfft = trgsw_fft_Enc_lvl1(-1,DEF_abk,key.lvl1);

        // cout << "gen trgswfft done" << endl;

        // External Product
        // TRGSW x TRLWE -> TRLWE  c に結果(TRLWE)が返る
        trgsw_External_Product_lvl1(c,c,trgswfft);

        // cout << "external product done" << endl;

        // TRLWE で c の復号 復号したものをm2とする。
        array<bool,DEF_N> m2 = trlwe_Dec_lvl1(c,key.lvl1);

        // cout << "dec c done" << endl;
        
        // TRGSWは -1 だから　m!=m2 のはず
        // for(int i=0;i<DEF_N;i++) cout << (m[i] ? 1:0);
        // cout << endl;
        // for(int i=0;i<DEF_N;i++) cout << (m2[i] ? 1:0);
        // cout << endl;
        for(int i=0;i<DEF_N;i++) assert(m[i]!=m2[i]);

        // cout << "check done" << endl;
    }
    cout << "lvl1:TRGSW(-1):PASS!" << endl;

}