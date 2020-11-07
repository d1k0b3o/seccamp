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


    // 負巡回乗算
    template<uint32_t N>
    inline void MulInFD(array<double,N> &res,const array<double,N> &a,const array<double,N> &b){

        for(int i=0;i<N/2;i++){
            double a_image_b_image = a[i+N/2]*b[i+N/2];
            double a_real_b_image = a[i]*b[i+N/2];

            res[i]= a[i]*b[i] - a_image_b_image;
            res[i+N/2]= a[i+N/2]*b[i] + a_real_b_image;
        }
    }

}// myTFHE