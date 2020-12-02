/*
    TLWElvl1 tlwelvl1={a,b}
    keyswitch(tlwelvl1)
        -> tlwelvl0={a_chil,b_chil}

    KS_ijk  

    KS is tlwelvl0 cipher encrypt (k dot S_i)/(2^(j+1)*basebit)

    S is tlwelvl1 key
    i from 0 to DEF_N-1
    j from 0 to t-1
    k 1 <= k <= 2^(basebit)-1

*/

#include<array>
#include<vector>
#include<iostream>
#include<cassert>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>
#include<../RANDEN/randen.h>

int main(){
    using namespace std;
    using namespace myTFHE;

    randen::Randen<uint64_t> engine;
    uniform_int_distribution<uint32_t> binary(0,1);

    // gen sk
    secretkey sk;

    // gen key switching key
    GateKey* gk = new GateKey(sk);

    // KeySwitchingKey *ksk = new KeySwitchingKey;
    // gen_Key_Switching_Key(*ksk,sk.key.lvl1,sk.key.lvl0);

    //cout << "gen ksk ?" << endl;
    
    const int num_test = 100;
    for(int test=0;test<num_test;test++){

        // gen in_m
        uint8_t in_m = binary(engine);

        // m -> myu
        uint32_t myu= in_m ? DEF_myu:-DEF_myu;

        // tlwe Enc lvl1
        TLWElvl1 tlwe1;
        tlwe1 = tlwe_Enc_lvl1(myu,DEF_alpha,sk.key.lvl1);
        //cout << "tlwelvl1 enc?" <<endl;

        // Id Key Switch   keylvl1 -> keylvl0
        TLWElvl0 res_tlwe0;
        Id_Key_Switch(res_tlwe0,tlwe1,*gk);

        //cout << "Id key Switch ?" <<endl;

        // gen out_m
        uint8_t out_m;
        out_m = tlwe_Dec_lvl0(res_tlwe0,sk.key.lvl0);

        //cout << "dec tlwe0?" << endl;

        // check in_m == out_m
        assert(in_m == out_m);
    }

    cout << "Identity Key Switch PASS!" << endl;

}