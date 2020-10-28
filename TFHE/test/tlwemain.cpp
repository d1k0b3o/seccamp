/*
    TLWE実装
    B={0,1}　"binary"
    n は Z に含まれる整数, alpha は R に含まれる実数  "securty parameter"
    n=630,alpha=2^-15
    UTn は T から n 個の値を独立にとる一様分布
    DTaplha を平均0標準偏差alphaのモジュラー正規分布とする。
    
    a are in Tn
    e,b are in T 
    s are in Bn sk
    m is in T   平文

    a <- UTn
    e <- DTalpha
    s <- UBn
    b = a dot s + m + e

    (a,b) cipher text (n+1要素)
*/
#include<iostream>
#include<array>
#include<random>
#include<vector>
#include</home/hagarikuo/seccamp/TFHE/RANDEN/randen.h>
#include</home/hagarikuo/seccamp/TFHE/include/params.hpp>
#include</home/hagarikuo/seccamp/TFHE/include/common.hpp>
#include</home/hagarikuo/seccamp/TFHE/include/key.hpp>
#include</home/hagarikuo/seccamp/TFHE/include/tlwe.hpp>

using namespace myTFHE;
using namespace std;

// mainですることは秘密鍵を生成して、その鍵を利用して、平文を暗号化、できた暗号文の復号
int main(){
    using namespace myTFHE;

    //lweparams params;

    // random　一様分布からランダムに取り出すため RANDENじゃない？
    // random_device seed_gen;
    // default_random_engine engine(seed_gen());
    randen::Randen<uint64_t> engine;

    // bainaryの一様分布　平文の生成のため
    uniform_int_distribution<uint32_t> binary(0,1);

    // 秘密鍵 sk の生成
    secretkey sk;

    // bainary平文 m の生成
    vector<uint8_t> m(DEF_n);
    for(uint8_t &i : m) i=binary(engine);

    // sk で m を暗号化 暗号文 c はn*(n+1)行列の形
    vector<TLWElvl0> c(DEF_n);
    c=tlweEnc(m,sk);

    cout << "ENCRYPTED!" << endl;

    // // sk で c から m2 を復元
    // vector<uint32_t> m2(DEF_n);
    // m2=tlwedec(c,sk);

    // // m=m2なら"pass" ?
    // if(m==m2) cout << "pass" << endl;
    
}
