/*
    HomNAND()

    NAND(A,B) -> C
    A   B   C
    0   0   1
    0   1   1
    1   0   1
    1   1   0  

    HomNAND(Enc(A),Enc(B)) -> Enc(C)
    Enc(A)  Enc(B)  Enc(C)
    Enc(0)  Enc(0)  Enc(1)
    Enc(0)  Enc(1)  Enc(1)
    Enc(1)  Enc(0)  Enc(1)
    Enc(1)  Enc(1)  Enc(0)

*/

#include<array>
#include<vector>
#include<cassert>
#include<iostream>
#include<random>
#include<chrono>
#include<../RANDEN/randen.h>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>

int main(){
    using namespace std;
    using namespace myTFHE;

    // random
    randen::Randen<uint64_t> engine;
    uniform_int_distribution<uint32_t> binary(0,1);

    // gen secret key   lwekeylvl0/lvl1
    secretkey sk;

    // gen bootstrapping key bk
    GateKey* gk = new GateKey(sk);

    // time
    double time_homo=0.0;

/************************************************************************************************/

    // test HomNAND
    cout << "test HomNAND" << endl;
    // test
    const uint32_t num_test = 1000;
    for(int test=0;test<num_test;test++){

        // gen input A,B
        uint8_t A,B;
        A=binary(engine);
        B=binary(engine);

        // Enc A,B
        TLWElvl0 tlweA,tlweB;
        tlweA = TLWE_ENC(A,sk);
        tlweB = TLWE_ENC(B,sk);

        chrono::system_clock::time_point start,end;
        start = chrono::system_clock::now();

        // HomNAND  res_tlwe = (!(tlweA & tlweB))
        TLWElvl0 res_tlwe;
        HomNAND(res_tlwe,tlweA,tlweB,*gk);

        end = chrono::system_clock::now();

        // Dec res_tlwe
        uint8_t res;
        res = tlwe_Dec_lvl0(res_tlwe,sk.key.lvl0);

        // check
        assert((!(A&B)) == res);

        //
        double elapsed = chrono::duration_cast<chrono::microseconds>(end-start).count();
        time_homo += elapsed;

    }
    cout << "HomNAND PASS!" << endl;
    cout << "time = " << time_homo/num_test << " micro sec" << endl << endl;

/************************************************************************************************/

    // test HomAND
    cout << "test HomAND" << endl;
    time_homo = 0.0;

    for(int test=0;test<num_test;test++){

        // gen input A,B
        uint8_t A,B;
        A=binary(engine);
        B=binary(engine);

        // Enc A,B
        TLWElvl0 tlweA,tlweB;
        tlweA = TLWE_ENC(A,sk);
        tlweB = TLWE_ENC(B,sk);

        chrono::system_clock::time_point start,end;
        start = chrono::system_clock::now();

        // HomNAND  res_tlwe = (tlweA & tlweB)
        TLWElvl0 res_tlwe;
        HomAND(res_tlwe,tlweA,tlweB,*gk);

        end = chrono::system_clock::now();

        // Dec res_tlwe
        uint8_t res;
        res = tlwe_Dec_lvl0(res_tlwe,sk.key.lvl0);

        // check
        assert((A&B) == res);

        //
        double elapsed = chrono::duration_cast<chrono::microseconds>(end-start).count();
        time_homo += elapsed;

    }
    
    cout << "HomAND PASS!" << endl;
    cout << "time = " << time_homo/num_test << " micro sec" << endl << endl;

/************************************************************************************************/

    // test HomOR
    cout << "test HomOR" << endl;
    time_homo = 0.0;
    
    for(int test=0;test<num_test;test++){

        // gen input A,B
        uint8_t A,B;
        A=binary(engine);
        B=binary(engine);

        // Enc A,B
        TLWElvl0 tlweA,tlweB;
        tlweA = TLWE_ENC(A,sk);
        tlweB = TLWE_ENC(B,sk);

        chrono::system_clock::time_point start,end;
        start = chrono::system_clock::now();

        // HomOR  res_tlwe = (tlweA  tlweB)
        TLWElvl0 res_tlwe;
        HomOR(res_tlwe,tlweA,tlweB,*gk);

        end = chrono::system_clock::now();

        // Dec res_tlwe
        uint8_t res;
        res = tlwe_Dec_lvl0(res_tlwe,sk.key.lvl0);

        // check
        assert((A||B) == res);

        //
        double elapsed = chrono::duration_cast<chrono::microseconds>(end-start).count();
        time_homo += elapsed;

    }
    
    cout << "HomOR PASS!" << endl;
    cout << "time = " << time_homo/num_test << " micro sec" << endl << endl;

/************************************************************************************************/
    // test HomNOR
    cout << "test HomNOR" << endl;
    time_homo = 0.0;
    
    for(int test=0;test<num_test;test++){

        // gen input A,B
        uint8_t A,B;
        A=binary(engine);
        B=binary(engine);

        // Enc A,B
        TLWElvl0 tlweA,tlweB;
        tlweA = TLWE_ENC(A,sk);
        tlweB = TLWE_ENC(B,sk);

        chrono::system_clock::time_point start,end;
        start = chrono::system_clock::now();

        // HomOR  res_tlwe = (tlweA  tlweB)
        TLWElvl0 res_tlwe;
        HomNOR(res_tlwe,tlweA,tlweB,*gk);

        end = chrono::system_clock::now();

        // Dec res_tlwe
        uint8_t res;
        res = tlwe_Dec_lvl0(res_tlwe,sk.key.lvl0);

        // check
        assert((!(A||B)) == res);

        //
        double elapsed = chrono::duration_cast<chrono::microseconds>(end-start).count();
        time_homo += elapsed;

    }
    
    cout << "HomNOR PASS!" << endl;
    cout << "time = " << time_homo/num_test << " micro sec" << endl << endl;

/************************************************************************************************/



}