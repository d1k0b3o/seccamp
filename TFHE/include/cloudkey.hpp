#pragma onece

#include<array>
#include<vector>
#include<../include/params.hpp>
//#include<../include/tfhe++.hpp>

namespace myTFHE{

    struct GateKey{
        BootStrappingKeyFFTlvl01 bk;
        KeySwitchingKey ksk;
        
        GateKey(secretkey sk);
        GateKey() {}
    };

}