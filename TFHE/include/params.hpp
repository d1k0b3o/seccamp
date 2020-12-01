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

// Identity Key Switch security prams
constexpr uint32_t DEF_basebit = 2;
constexpr uint32_t DEF_t = 8;

constexpr uint64_t DEF_nbarbit = 11;
constexpr uint64_t DEF_nbar = 1 << DEF_nbarbit;

#endif

// 鍵の呼吸 壱ノ型
using lwekeylvl0 = array<uint32_t,DEF_n>;                           // n
using lwekeylvl1 = array<uint32_t,DEF_N>;                           // N

// TLWE 暗号文の型 {a,b}
using TLWElvl0 = array<uint32_t,DEF_n + 1>;                         // n+1
using TLWElvl1 = array<uint32_t,DEF_N + 1>;                         // N+1

// TRLWE の多項式の係数はそれぞれ DEF_N の TLWE となっている
using Polynomiallvl1 = array<uint32_t,DEF_N>;                       // N
using PolynomialInFDlvl1 = array<double,DEF_N>;                     // N

// TRLWE 暗号文cの型 c={a[X],b[X]}
using TRLWElvl1 = array<Polynomiallvl1,2>;                          // 2 x N                array<array<uint32_t,DEF_N>,2>
using TRLWEInFDlvl1 = array<PolynomialInFDlvl1,2>;                  // 2 x N                array<array<double,DEF_N>,2>

// Decomposition後の型
using DecomposedTRLWElvl1 = array<Polynomiallvl1, 2*DEF_l>;         // (2*l) x N          array<array<uint32_t,DEF_N>,2*DEF_l>
using DecomposedTRLWEInFDlvl1 = array<PolynomialInFDlvl1,2*DEF_l>;  // (2*l) x N          array<array<double,DEF_N>,2*DEF_l>

// TRGSW 暗号文cの型
using TRGSWlvl1 = array<TRLWElvl1,2*DEF_l>;                         // (2*l) x (N x 2)    array<array<array<uint32_t,DEF_N>,2>,2*DEF_l>
using TRGSWFFTlvl1 = array<TRLWEInFDlvl1,2*DEF_l>;                  // (2*l) x (N x 2)     array<array<array<double,DEF_N>,2>,2*DEF_l>

// Bootstrapping Key 鍵の型
// lwekeylvl0 を 1bit ずつTRGSWに暗号化
using BootStrappingKeyFFTlvl01 = array<TRGSWFFTlvl1,DEF_n>;         // n x ((2*l) x (2 x N)) array<array<array<array<double,DEF_N>,2>,2*DEF_l>,DEF_n>

using KeySwitchingKey = array<array<array<TLWElvl0,(1U >> DEF_basebit)-1>,DEF_t>,DEF_N>; // N x t x 3 x 2 x N


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

    // Identity Key Switch security params
    uint32_t basebit = DEF_basebit;
    uint32_t t = DEF_t;

};


}// myTFHE

