#include<array>
#include<random>
#include<vector>
#include<../include/tfhe++.hpp>
#include<../RANDEN/randen.h>

namespace myTFHE{
    using namespace std;
    //static randen::Randen<uint64_t> engine;

    TRLWElvl1 trlweEncZerolvl1(const double abk,const lwekeylvl1 &key){
        TRLWElvl1 c;
        // uint32_Tの一様分布 Torusは32bit幅の小数を整数として扱っているからuint32_tでいい
        uniform_int_distribution<uint32_t> Torus32dist(0,UINT32_MAX);

        // c={a[X],b[X]}のa[X]の部分にc[0]として格納
        for(uint32_t &i : c[0]) i=Torus32dist(engine);

        // c[1]= a[X](c[0]) dot key[X]　の多項式乗算
        PolyMullvl1(c[1],c[0],key);

        // error[X] をモジュラーガウス分布から
        for(uint32_t &i : c[1]) i+=gaussian32(0,abk);
        
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


    array<bool,DEF_N> trlweDeclvl1(const TRLWElvl1 &c,const lwekeylvl1 &key){

        // m2= b[X] - a[X] dot s[X]         
        array<bool,DEF_N> m2;

        Polynomiallvl1 mulres;
        // mulres[X] = a[X] dot s[X]
        PolyMullvl1(mulres,c[0],key);

        // m2= (b[X]-mulres[X]) > 0
        for(int i=0;i<DEF_N;i++) m2[i]= static_cast<int32_t>(c[1][i]-mulres[i]) > 0;

        return m2;
    }

    template <typwename T=uint32_t,uint32_t N=DEF_N>
    void SampleExtractIndex(array<T,N+1> &tlwe,const array<array<T,N>,2> &trlwe, const int index){

        // a'_i
        // if i<=k      a_k-i
        // otherwise    -a_N+k-i
        for(int i=0;i<=index;i++){
            tlwe[i] = trlwe[0][index - i];
        }
        for(int i=0;i<N;i++){
            tlwe[i] = -trlwe[0][N + index - i];
        }
        // b'=b_k
        tlwe[N]=trlwe[1][index];
    }
    
    void SampleExtractIndexlvl1(TLWElvl1 &tlwe, const TRLWE &trlwe, const int index){
        SampleExtractIndex<uint32_t,DEF_N>(tlwe,trlwe,index);
    }



}// myTFHE