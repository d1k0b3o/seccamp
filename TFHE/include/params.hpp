#pragma once
#include<cstdint>
#include<array>
#include<cmath>

namespace myTFHE{

using namespace std;

#ifdef USE_80BIT_SECURITY
constexpr uint32_t DEF_n=500;
#else
// 1/8を32bit幅ずらすと000100000...となり、最初の三桁の000がいらないから<<29
constexpr uint32_t DEF_myu = 1U << 29;

// TLWE  security params
constexpr uint32_t DEF_n = 630;
const double DEF_alpha = pow(2.0,-15);

// TRLWE security params
constexpr uint32_t DEF_Nbit = 10;
constexpr uint32_t DEF_N = 1 << DEF_Nbit;
const double DEF_abk = pow(2.0,-25);

constexpr uint64_t DEF_nbarbit = 11;
constexpr uint64_t DEF_nbar = 1 << DEF_nbarbit;

#endif

// 鍵の呼吸 壱ノ型
using lwekeylvl0 = array<uint32_t,DEF_n>;
using lwekeylvl1 = array<uint32_t,DEF_N>;

// TLWE 暗号文の型 {a,b}
using TLWElvl0 = array<uint32_t,DEF_n + 1>;
using TLWElvl1 = array<uint32_t,DEF_N + 1>;

using Polynomiallvl1 = array<uint32_t,DEF_N>;
using PolynomialInFDlvl1 = array<double,DEF_N>;

// TRLWE 暗号文cの型 c={a[X],b[X]}
using TRLWElvl1 = array<Polynomiallvl1,2>;


struct lweparams{
    // Common
    uint32_t myu=DEF_myu;
    
    // TLWE security params
    uint32_t n=DEF_n;
    double alpha=DEF_alpha;

    // TRLWE　security params
    uint32_t Nbit=DEF_Nbit;
    uint32_t N=DEF_N;
    double abk=DEF_abk;

};


}// myTFHE

