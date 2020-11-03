#include<array>
#include<random>
#include<vector>
#include<../include/tfhe++.hpp>
#include<../RANDEN/randen.h>

namespace myTFHE{
    using namespace std;
    static randen::Randen<uint64_t> engine;

    TRLWElvl1 trlweEncZerolvl1(const double abk,const lwekeylvl1 &key){
        TRLWElvl1 c;
        // uint32_Tの一様分布 Torusは32bit幅の小数を整数として扱っているからuint32_tでいい
        uniform_int_distribution<uint32_t> Torus32dist(0,UINT32_MAX);

        // c={a[X],b[X]}のc[0]の部分に格納
        for(uint32_t &i : c[0]) i=Torus32dist(engine);

        // c[1]= a[X](c[0]) dot key[X]　の多項式乗算
        PolyMullvl1(c[1],c[0],key);

        // error[X] をモジュラーガウス分布から
        for(uint32_t &i : c[i]) i+=garussian32(0,abk);
        
        return c;
    }

    TRLWElvl1 trlweEnclvl1(const array<uint32_t,DEF_N> &myu,const double abk,const lwekeylvl1 &key){
        TRLWElvl1 c;
        // c[0][X] = a[X]
        // c[1][X] = a[X] dot s[X] + e[x]
        c = trlweEncZerolvl1(abk,key);
        // c[1][X] = a[X] dot s[X] + e[x] + myu[X]
        for(int i=0;i<DEF_N;i++) c[1][i]+=myu[i];
        return c;
    }



}// myTFHE