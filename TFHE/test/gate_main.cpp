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
#include<../RANDEN/randen.h>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>

int main(){
    using namespace std;
    using namespace myTFHE;

    // gen secret key   lwekeylvl0/lvl1
    secretkey sk;

    // gen bootstrapping key bk
    GateKey* gk = new GateKey(sk);

    cout << "1" << endl;
}