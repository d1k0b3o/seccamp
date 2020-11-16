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

// TLWE security params
constexpr uint32_t DEF_n = 630;
const double DEF_alpha = pow(2.0,-15);

// TRLWE security params
constexpr uint32_t DEF_Nbit = 10;
constexpr uint32_t DEF_N = 1 << DEF_Nbit;       // N=1024
const double DEF_abk = pow(2.0,-25);

// TRGSW security params
constexpr uint32_t DEF_l = 3;
constexpr uint32_t DEF_Bgbit = 6;
constexpr uint32_t DEF_Bg = 1 << DEF_Bgbit;     // Bg=64

constexpr uint64_t DEF_nbarbit = 11;
constexpr uint64_t DEF_nbar = 1 << DEF_nbarbit;

#endif

// 鍵の呼吸 壱ノ型
using lwekeylvl0 = array<uint32_t,DEF_n>;
using lwekeylvl1 = array<uint32_t,DEF_N>;

// TLWE 暗号文の型 {a,b}
using TLWElvl0 = array<uint32_t,DEF_n + 1>;
using TLWElvl1 = array<uint32_t,DEF_N + 1>;

// TRLWE の多項式の係数はそれぞれ DEF_N の TLWE となっている
using Polynomiallvl1 = array<uint32_t,DEF_N>;
using PolynomialInFDlvl1 = array<double,DEF_N>;

// TRLWE 暗号文cの型 c={a[X],b[X]}
using TRLWElvl1 = array<Polynomiallvl1,2>;
using TRLWEInFDlvl1 = array<PolynomialInFDlvl1,2>;

// Decomposition
using DecomposedTRLWElvl1 = array<Polynomiallvl1, 2*DEF_l>;
using DecomposedTRLWEInFDlvl1 = array<PolynomialInFDlvl1,2*DEF_l>;

// TRGSW 暗号文cの型
using TRGSWlvl1 = array<TRLWElvl1,2*DEF_l>;
using TRGSWInFDlvl1 = array<TRLWEInFDlvl1,2*DEF_l>;

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

    // TRGSW security params
    uint32_t l=DEF_l;
    uint32_t Bgbit=DEF_Bgbit;
    uint32_t Bg=DEF_Bg;

};


}// myTFHE

