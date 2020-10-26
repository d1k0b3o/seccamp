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
#include</home/hagarikuo/seccamp/TFHE/params.hpp>
using namespace std;

// function
uint32_t Dto32t(double d);
void tlweEnc_T_m(vector<double> a,vector<uint8_t> s,double T_m,double e);
void tlweEnc_B_m(vector<double> a,vector<uint8_t> s,uint8_t B_m,double e);

// 実数からTorusへの変換 (実数の小数部分32bit幅分を取り出す操作)　引数：double 返り値：uint32_t
uint32_t DtoT32(double d){

    return int32_t(int64_t((d-int64_t(d))*(1L << 32)));
}

// print()
void tlweEnc_T_m(vector<double> a,vector<uint8_t> s,double T_m,double e){
    uint32_t b=0;
    uint32_t adots=0;

    for(int i=0;i<DEF_n;i++){
        adots+=a[i]*s[i];
    }
    b=adots+T_m+DtoT32(e);
    a.push_back(b);

    cout << "message : " << T_m << endl;
    cout << "ciphertext : ";
    for(int i=0;i<DEF_n+1;i++){
        cout << a[i] << ", "; 
    }cout << endl;
}

void tlweEnc_B_m(vector<double> a,vector<uint8_t> s,uint8_t B_m,double e){
    double m = myu*(2*B_m-1);
    uint32_t b=0;
    uint32_t adots=0;

    for(int i=0;i<DEF_n;i++){
        adots+=a[i]*s[i];
    }
    b=adots+m+DtoT32(e);
    a.push_back(b);
    
    
    cout << "message : " << B_m << endl;
    cout << "ciphertext : ";
    for(int i=0;i<=DEF_n;i++){
        cout << a[i] << ", "; 
    }cout << endl;
}



int main(){
    
    // 平文がTorusの場合
    double T_m = 1;
    // 平文がBainaryの場合
    uint8_t B_m = 1;

    // random
    random_device seed_gen;
    default_random_engine engine(seed_gen());

    // 0,1 の整数の一様分布
    uniform_int_distribution<uint32_t> binary(0,1);    
 
    //　0.0 ~ 1.0 のTorusの一様分布
    uniform_real_distribution<double> Torus(0.0,1.0);

    // 秘密鍵sをBinaryからDEF_n個の値を独立に一様分布から選ぶ　
    vector<uint8_t> s(DEF_n);
    for(int i=0;i<DEF_n;i++){
        s[i]=binary(engine);
    }

    // aをTorusからDEF_n個の値を独立に一様分布から選ぶ
    vector<double> a(DEF_n);
    for(int i=0;i<DEF_n;i++){
        a[i]=Torus(engine);
    }

    // eを平均0標準偏差alphaのModular正規分布から選ぶ
    normal_distribution<double> MGD(0.0,DEF_alpha);  // MGD:Modular Gaussian Distribution
    double e=MGD(engine);

    // 平文がTorusの場合
    tlweEnc_T_m(a,s,T_m,e);

    // 平文がBinaryの場合
    tlweEnc_B_m(a,s,B_m,e); 
    
}
