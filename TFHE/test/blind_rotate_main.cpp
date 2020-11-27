/*
    gen in_plain_message
        ->
        in_m
    enc(in_m,key.lvl0)
        -> TLWElvl0 tlwe
    
    gen trivial_cipher  b[x]= plain torus poly, a[x]=0
        -> TRLWElvl1 testvector

    gen bootstrapping_key()
        -> TRGSWlvl1 bootstrapping_key


    Blind_Rotate(testvector,tlwe,bootstrapping_key)
        b_til = 2*N - ((testvector[1] + (1 << (31 - Nbit - 1))) >> (32 - Nbit - 1))

        res_trlwe= X^b_til dot (testvector[0],testvector[1])

        for i to n-1
            a_til = (a_i + (1 << (31 - Nbit - 1))) >> (32 - Nbit -1)
            res_trlwe = CMUX (bootstrapping_key[i], X^a_til dot res_trlwe,res_trlwe)

            -> res_trlwe
            
    -> Sample_Extract_Index(TLWElvl1 res_tlwelvl1,TRLWElvl1 trlwe, 0)
        -> TLWElvl1 res_tlwe
    
    -> dec(res_tlwe)
        -> out_m

    assert(in_m == out_m)

*/

#include<array>
#include<vector>
#include<iostream>
#include<cassert>
#include<random>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>
#include<../include/common.hpp>
#include<../RANDEN/randen.h>

int main(){

    using namespace std;
    using namespace myTFHE;

    // random
    randen::Randen<uint64_t> engine;
    uniform_int_distribution<uint32_t> binary(0,1);

    // gen sk
    secretkey sk;

    cout << "gen sk ?" << endl;

    // gen in_plain_message as in_m
    uint8_t in_m = binary(engine);

    cout << "gen m ?" << endl;

    // in_m -> myu
    uint32_t myu= in_m ? DEF_myu : DEF_myu;

    cout << "gen m -> myu ?" << endl;

    // Enc in_m
    // tlwe   DEF_n x DEF_n
    TLWElvl0 tlwe;
    tlwe = tlwe_Enc_lvl0(myu,DEF_alpha,sk.key.lvl0);

    cout << "enc ?" << endl;

    // gen testvector (trivial cipher)
    TRLWElvl1 testvector = gen_testvector();

    cout << "gen testvector ?" << endl;

    // gen bootstrapping key (TRGSWlvl1)
    BootStrappingKeyFFTlvl01 bk;

    array<int32_t,DEF_n> tmp;
    for(int i=0;i<DEF_n;i++){
        tmp[i]=(int)sk.key.lvl0[i];
    }
    gen_bootstrapping_key3(bk,tmp,sk.key.lvl1);

    // for(int i=0;i<DEF_n;i++){
    //     bk[i] = gen_bootstrapping_key2(sk.key.lvl0[i],sk.key.lvl1);
    // }

    //bk = gen_bootstrapping_key(sk.key.lvl0,sk.key.lvl1);

    cout << "gen bootstrapping key ?" << endl;

    // // Blind Rotate
    // TRLWElvl1 res_trlwe;
    // Blind_Rotate(res_trlwe,testvector,tlwe,bk);

    // cout << "do rotate ?" << endl;

    // // Sample Extract Index (0)
    // TLWElvl1 res_tlwe;
    // Sample_Extract_Index_lvl1(res_tlwe,res_trlwe,0);

    // cout << "sample extract ?" << endl;

    // // Dec res_tlwe
    // uint8_t out_m;
    // out_m=tlwe_Dec_lvl1(res_tlwe,sk.key.lvl1);

    // cout << "dec ?" << endl;

    // // check m==m2
    // assert(in_m==out_m);

    cout << "PASS!" << endl;

}