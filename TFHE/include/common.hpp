#pragma once
#include<random>
#include</home/hagarikuo/seccamp/TFHE/RANDEN/randen.h>

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


}// myTFHE