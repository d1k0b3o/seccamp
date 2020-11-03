/*
    TRLWE実装
    -LWEを多項式環上で実現し、係数がTorusのもの
    -多項式の係数としてN個の平文を同時に計算できるのでTLWEより高速（並列）

    "security parameter"
    N in N+
    alphabk in R+
    N = 1024, alphabk = 2^-25

    T_N[X] はTorusを係数とする多項式を(X^N)+1で割った余りが成す剰余環である
    
    "cipher text"    (a[X],b[X])というN-1次の多項式2要素ベクトル
    a[X] in T_N[X]  a[X] <- U_T_N[X]
    b[X] in T_N[X]  b[X] = a[X] dot s[X] + m[X] + e[X]
    
    "message"
    m[x] in T_N[X]
         in B_N[X]
            myu = 1/8
            myu(2*m - 1[X]) in T_N[X]
    
    "error"
    e[X] in T_N[X]  e[C] <- D_T_N[X],alphabk
    
    "secret key"
    s[X] in B_N[X]  s[X] <- U_T_N[X]

    "enc"
    b[x] = a[X] dot s[X] + m[X] + e[X]

    "dec"
    (1+sgn(b[X] - a[X] dot s[X]))/2

    Sample Extract Index実装
    -TRLWE を N個の TLWE に分解する操作　多項式の係数を取り出す操作
    -分解されたTLWEの要素数はN個　このTLWEをTLWElvl1という　それぞれ鍵が違う


*/

#include<iostream>
#include<array>
#include<vector>
#include<random>
#include<../include/tfhe++.hpp>
#include<../RANDEN/randen.h>

using namespace myTFHE;
using namespace std;

int main(){

    // random
    randen::Randen<uint64_t> engine;
    cout << "lvl1" << endl;

    for(int i=0;i < DEF_N;i++){
        // binary　の一様分布
        uniform_int_distribution<uint32_t> binary(0,1);

        // 鍵生成
        lwekey key;

        // 平文生成
        array<bool,DEF_N> m;
        for(bool &j : m) j=binary(engine);
        
        // 平文を1/8 or -1/8の状態に
        array<uint32_t,DEF_N> myu;
        for(int j=0;j<DEF_N;j++) myu[j]=m[j]? DEF_myu : -DEF_myu;

        // 暗号化処理の呼び出し
        TRLWElvl1 c;
        c=trlweEnclvl1(myu,DEF_abk,key.lvl1);

        cout << "enc!" << endl;
        // // 復号処理の呼び出し
        // array<bool,DEF_N> m2;
        // m2=trlweDeclvl1(c,key.lvl1);

        // // check
        // bool flag=1;
        // for(int i=0;i<DEF_n;i++) if(m[i]!=m2[i]) flag=0;
        // if(flag) cout << "pass" << endl;
        // else cout << "miss" << endl;
    }

    

}