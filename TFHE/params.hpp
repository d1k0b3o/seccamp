#include<cstdint>
#include<array>
#include<cmath>

using namespace std;

constexpr double myu = 1.0/8.0;

// TLWE 
constexpr uint32_t DEF_n = 630;
const double DEF_alpha = pow(2.0,-15);

// TRLWE
constexpr uint32_t DEF_Nbit = 10;
constexpr uint32_t DEF_N = 1 << DEF_Nbit;
const double DEF_abk = pow(2.0,-25);

