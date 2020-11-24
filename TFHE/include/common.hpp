#pragma once

#include<random>
#include<../RANDEN/randen.h>

namespace myTFHE{
    using namespace std;
    static randen::Randen<uint64_t> engine;

    // 実数からTorusへの変換 (実数の小数部分32bit幅分を取り出す操作)　引数：double 返り値：uint32_t
    inline uint32_t DtoT32(double d){

        return int32_t(int64_t((d-int64_t(d))*(1L << 32)));
    }

    // 平均0.0,分散alphaの正規分布からerrorを選び、mに足して返す
    inline uint32_t gaussian32(uint32_t m,double alpha){
        // 平均0.0,分散alphaの正規分布
        normal_distribution<double> gaussian_dist(0.0,alpha);

        double error = gaussian_dist(engine);
        return m + DtoT32(error);
    }


    // 負巡回乗算// 引数(res,a,b)
    template<uint32_t N>
    inline void MulInFD(array<double,N> &res, const array<double,N> &a, const array<double,N> &b){

        for(int i=0;i<N/2;i++){
            double a_image_b_image = a[i+N/2]*b[i+N/2];
            double a_real_b_image = a[i]*b[i+N/2];

            res[i]= a[i]*b[i] - a_image_b_image;
            res[i+N/2]= a[i+N/2]*b[i] + a_real_b_image;
        }
    }

    //// 引き数(res,a,b)
    template<uint32_t N>
    inline void FMAInFD(array<double,N> &res, const array<double,N> &a, const array<double,N> &b){
        for(int i=0;i<N/2;i++){
            res[i]=a[i+N/2] * b[i+N/2] -res[i];
            res[i]=a[i]*b[i]-res[i];
            res[i+N/2] += a[i] * b[i+N/2];
            res[i+N/2] += a[i+N/2] * b[i];
        }
    }


    // 多項式乗算
    // template<class T, class T1, class T2, uint32_t N>
    // void poly_mult(array<T,N> &res, const array<T1,N> &a, const array<T2,N> &b){
        
    //     uint32_t tmp=0;

    // }

    // 多項式剰余
//     array<int32_t,n> polymod(array<int32_t,2*DEF_N> &a){
//         array<int32_t,DEF_N> res;

//         int32_t tmp=0;
//         int i=1;
//         while(i<=n){
//             tmp=a[2*n-i];
//             a[2*n-i]-=tmp;
//             a[2*n-(i+n)]-=tmp;
//             ++i;
//         }
//         int j=0;
//         while(j<n){
//             res[j]=a[j];
//             ++j;
//         }
//         return res;
    // }
}// myTFHE