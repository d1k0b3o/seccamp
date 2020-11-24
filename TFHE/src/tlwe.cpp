#include<array>
#include<random>
#include<vector>
#include<../include/tfhe++.hpp>
#include<../RANDEN/randen.h>

namespace myTFHE{
    using namespace std;

    // random
    //static randen::Randen<uint64_t> tengine;
    // 実際の暗号化処理
    template <typename T=uint32_t,uint32_t n=DEF_n>
    inline array<T,n+1> tlwe_Sym_Enc(const T m,const double alpha,const array<uint32_t,n> &key){
        // Torusからn個の実数をとる これがa
        uniform_int_distribution<T> Torusdist(0,numeric_limits<T>::max());
            
        // 暗号文の入れ物   {a,b}となるように aがn,bが1
        array<T,n+1> res={};
        // m+e
        res[n]=gaussian_32(m,alpha);

        for(int i=0;i<n;++i){
            // a
            res[i]=Torusdist(engine);
            // b=a*s+m+e                
            res[n]+=res[i]*key[i];
        }

        return res;
    }

    // 中継？
    TLWElvl0 tlwe_Enc_lvl0(const uint32_t m,const double alpha,const lwekeylvl0 &key){
        return tlwe_Sym_Enc<uint32_t,DEF_n>(m,alpha,key);
    }

    // tlwe の暗号化処理呼び出し　
    vector<TLWElvl0> tlwe_Enc(const vector<uint8_t> &m,const secretkey &sk){
        vector<TLWElvl0> c(m.size());
        // 暗号化処理を呼び出し、cに代入していく
        for(int i=0;i<m.size();++i){
            c[i]= tlwe_Enc_lvl0(m[i]? DEF_myu : -DEF_myu,DEF_alpha,sk.key.lvl0);
        }

        // 暗号文を返す
        return c;

    }

    // 実際の復号処理
    template <typename T=uint32_t,uint32_t n=DEF_n>
    bool tlwe_Sym_Dec(const array<T,n+1> &c,const array<T,n> &key){
        T b = c[n];
        T tmp = 0;
        for(int i=0;i<n;i++) tmp += c[i]*key[i];
        // T を符号付きにする uint32_t -> int32_t
        // bool res = int32_t(b-tmp) > 0;
        bool res = static_cast<typename make_signed<T>::type>(b-tmp) > 0;
        return res;
    }

    // 中継？
    bool tlwe_Dec_lvl0(const TLWElvl0 &c,const lwekeylvl0 &key){
        return tlwe_Sym_Dec<uint32_t,DEF_n>(c,key);
        //return tlweSymDecrypt<uint32_t,DEF_n>(c,key);
    }

    // tlwe の復号処理の呼び出し
    vector<uint8_t> tlwe_Dec(const vector<TLWElvl0> c,const secretkey &sk){
        // 復号してできる平文
        vector<uint8_t> m2(c.size());

        // 暗号文を1行ずつ処理
        for(int i=0;i<c.size();i++){
            m2[i]=tlwe_Dec_lvl0(c[i],sk.key.lvl0);
        }

        // 復号してできた平文を返す
        return m2;
    }

}// myTFHE

