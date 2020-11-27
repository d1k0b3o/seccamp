/*
    TLWE実装
    "binary"
    B={0,1}
    　
    "securty parameter"
    n in Z
    alpha in R  
    n=630, alpha=2^-15
    
    U_T_n は T から n 個の値を独立にとる一様分布
    D_T,aplha を平均0標準偏差alphaのモジュラー正規分布とする。
    
    "cipher text" (a,b) n+1要素
    a in T_n        a <- U_T_n
    b in T          b = a dot s + m + e //enc
    
    "message"
    m  in T  
       in B
            myu = 1/8
            myu(2*m - 1) in T 

    "error"
    e in T          e <- D_T,alpha 
    
    "secret key"
    s in B_n    s <- U_B_n

    "enc"
    b = a dot s + m + e

    "dec"
    (1+sgn(b - a dot s))/2

*/
#include<iostream>
#include<array>
#include<random>
#include<vector>
#include<cassert>
#include<../RANDEN/randen.h>
#include<../include/tfhe++.hpp>


using namespace myTFHE;
using namespace std;

// mainですることは秘密鍵を生成して、その鍵を利用して、平文を暗号化、できた暗号文の復号
int main(){

    // random　一様分布からランダムに取り出すため 
    randen::Randen<uint64_t> engine;

    // bainaryの一様分布　平文の生成のため
    uniform_int_distribution<uint32_t> binary(0,1);

    // 秘密鍵 sk の生成
    secretkey sk;

    // bainary平文 m の生成
    vector<uint8_t> m(DEF_n);
    for(uint8_t &i : m) i=binary(engine);

    // // m -> myu
    // vector<uint32_t> myu(DEF_n);
    // for(int i=0;i<DEF_n;i++) myu[i] = m[i] ? DEF_myu : -DEF_myu;

    // sk で m を暗号化 暗号文 c はn x (n+1)行列の形
    vector<TLWElvl0> c(DEF_n);
    c=tlwe_Enc(m,sk);

    // sk で c から m2 を復元
    vector<uint8_t> m2(DEF_n);
    m2=tlwe_Dec(c,sk);

    //m=m2なら"pass" ?
    for(int i=0;i<DEF_n;i++) assert(m[i]==m2[i]);

    cout << "PASS!" << endl;

    // bool flag=1;
    // for(int i=0;i<DEF_n;i++) if(m[i]!=m2[i]) flag=0;
    // if(flag) cout << "pass" << endl;
    // else cout << "miss" << endl;
}
