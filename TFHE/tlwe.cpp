#include</home/hagarikuo/seccamp/TFHE/RANDEN/randen.h>

#include<array>
#include<random>
#include<vector>
#include</home/hagarikuo/seccamp/TFHE/INCLUDE/params.hpp>
#include</home/hagarikuo/seccamp/TFHE/INCLUDE/common.hpp>
#include</home/hagarikuo/seccamp/TFHE/INCLUDE/key.hpp>

namespace myTFHE{
    using namespace std;
    // random
    static randen::Randen<uint64_t> engine;

    // tlwe の暗号化処理呼び出し　
    vector<TLWElvl0> tlweEnc(const vector<uint8_t> &m,const secretkey &sk){
        vector<TLWElvl0> c(m.size());
        // 暗号化処理を呼び出し、cに代入していく
        for(int i=0;i<m.size();++i){
            c[i]= tlweEnclvl0(m[i]? DEF_myu : -DEF_myu,DEF_alpha,sk.key.lvl0);
        }

        return c;

    }

    // 中継？
    TLWElvl0 tlweEnclvl0(const uint32_t m,const double alpha,const lwekeylvl0 &key){
        return tlweSymEnc<uint32_t,DEF_n>(m,alpha,key);
    }

    // 実際の暗号化処理
    template <typename T=uint32_t,uint32_t n=DEF_n>
    inline array<T,n+1> tlweSymEnc(const T m,const double alpha,const array<uint32_t,n> &key){
        // Torusからn個の実数をとる これがa
        uniform_int_distribution<T> Torusdist(0,numeric_limits<T>::max());
        
        // 暗号文の入れ物{a,b}となるように aがn,bが1
        array<T,n+1> res={};
        // m+e
        res[n]=gaussian32(m,alpha);
        
        for(int i=0;i<n,++i){
            // a
            res[i]=Torusdist(engine);
            // b=a*s+m+e
            res[n]+=res[i]*key[i];
        }

        return res;
    }

}// myTFHE

