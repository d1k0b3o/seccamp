// CMUX test
//
// C ext_pro [(a1[x],b1[x])-(a0[x],b0[x])] + (a0[x],b0[x])

// C is trgsw
// c1:(a1[x],b1[x]) is trlwe
// c0:(a0[x],b0[x]) is trlwe
// out:res is trlwe

#include<array>
#include<vector>
#include<iostream>
#include<random>
#include<cassert>
#include<chrono>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>
#include<../RANDEN/randen.h>
#include<../include/common.hpp>

int main(){
    using namespace std;
    using namespace myTFHE;

    const uint32_t num_test = 100;

    // random
    randen::Randen<uint64_t> engine;
    uniform_int_distribution<uint32_t> binary(0,1);

    // gen sk
    secretkey *sk = new secretkey;

    // test 100 times

    // trgsw:m
    vector<int32_t> m(num_test);
    for(int32_t &i : m) i=binary(engine);

    // trlwe0:m0 -> myu0
    vector<array<uint8_t,DEF_N>> m0(num_test);
    for(int i=0;i<num_test;i++)
        for(int j=0;j<DEF_N;j++)
            m0[i][j] = binary(engine);
    
    vector<array<uint32_t,DEF_N>> myu0(num_test);
    for(int i=0;i<num_test;i++)
        for(int j=0;j<DEF_N;j++)
            myu0[i][j] = (m0[i][j] > 0) ? DEF_myu:-DEF_myu;
    
    // trlwe1:m1 -> myu1
    vector<array<uint8_t,DEF_N>> m1(num_test);
    for(int i=0;i<num_test;i++)
        for(int j=0;j<DEF_N;j++)
            m1[i][j] = binary(engine);
    
    vector<array<uint32_t,DEF_N>> myu1(num_test);
    for(int i=0;i<num_test;i++)
        for(int j=0;j<DEF_N;j++)
            myu1[i][j] = (m1[i][j] > 0) ? DEF_myu:-DEF_myu;

    // 
    array<bool,DEF_N> m_res;

    // TRGSW : cs
    vector<TRGSWFFTlvl1> cs(num_test);

    for(int i=0;i<num_test;i++)
        cs[i] = trgsw_fft_Enc_lvl1(m[i],DEF_abk,sk->key.lvl1);

    // TRLWE : c0
    vector<TRLWElvl1> c0(num_test);
    
    for(int i=0;i<num_test;i++)
        c0[i] = trlwe_Enc_lvl1(myu0[i],DEF_abk,sk->key.lvl1);
    
    // TRLWE : c1
    vector<TRLWElvl1> c1(num_test);

    for(int i=0;i<num_test;i++)
        c1[i] = trlwe_Enc_lvl1(myu1[i],DEF_abk,sk->key.lvl1);
    
    // TRLWE : c_res
    vector<TRLWElvl1> c_res(num_test);

    chrono::system_clock::time_point start,end;
    start = chrono::system_clock::now();

    // CMUX(res,cs,c1,c0)
    for(int i=0;i<num_test;i++)
        CMUX_lvl1(c_res[i],cs[i],c1[i],c0[i]);

    end = chrono::system_clock::now();

    for(int i=0;i<num_test;i++){
        m_res = trlwe_Dec_lvl1(c_res[i],sk->key.lvl1);
        for(int j=0;j<DEF_N;j++){
            assert(m_res[j] == ((m[i] > 0)? m1[i][j] : m0[i][j]) > 0);
        }
    }

    cout << "PASS!" << endl;

    double elapsed = chrono::duration_cast<chrono::microseconds>(end-start).count();

    cout << elapsed/num_test << "micro sec" << endl;

}