#pragma once
#include<cstdint>
#include<array>
#include<cmath>

namespace myTFHE{

using namespace std;

#ifdef USE_80BIT_SECURITY
constexpr uint32_t DEF_n=500;
#else
// 1/8を32bit幅ずらすと000100000...となり、最初の三桁の000がいらないから<<29になってる
constexpr uint32_t DEF_myu = 1U << 29;

// TLWE 
constexpr uint32_t DEF_n = 630;
const double DEF_alpha = pow(2.0,-15);

// TRLWE
constexpr uint32_t DEF_Nbit = 10;
constexpr uint32_t DEF_N = 1 << DEF_Nbit;
const double DEF_abk = pow(2.0,-25);

#endif

using lwekeylvl0 = array<uint32_t,DEF_n>;
using TLWElvl0 = array<uint32_t,DEF_n+1>;

struct lweparams{
    // COMMON
    uint32_t myu=DEF_myu;
    
    // TLWE
    uint32_t n=DEF_n;
    double alpha=DEF_alpha;

    // TRLWE
    uint32_t Nbit=DEF_Nbit;
    uint32_t N=DEF_N;
    double abk=DEF_abk;

};


}// myTFHE

