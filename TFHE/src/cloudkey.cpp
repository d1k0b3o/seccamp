#include<array>
#include<vector>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>
//#include<../RANDEN/randen.h>

namespace myTFHE{

    GateKey::GateKey(secretkey sk){

        // gen Boot_Strapping_Key
        for(int i=0;i<DEF_n;i++){
            bk[i] = trgsw_fft_Enc_lvl1(static_cast<uint32_t>(sk.key.lvl0[i]),DEF_abk,sk.key.lvl1);
        }

        // gen Key_Switching_Key
        uint32_t base = (1 << DEF_basebit);

        for(int i=0;i<DEF_N;i++){
            for(int j=0;j<DEF_tt;j++){
                for(int k=0;k<base-1;k++){
                    uint32_t in_M = (k+1)*sk.key.lvl1[i]*(1U << (32-DEF_basebit*(j+1)));
                    ksk[i][j][k] = tlwe_Enc_lvl0(in_M,DEF_alpha,sk.key.lvl0);
                }
            }
        }
    }

}