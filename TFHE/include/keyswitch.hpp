#pragma onece

#include<array>
#include<random>
#include<vector>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>

namespace myTFHE{
    void gen_Key_Switching_Key(KeySwitchingKey &ksk,const lwekeylvl1 &keylvl1, const lwekeylvl0 &keylvl0);
    void Id_Key_Switch(TLWElvl0 &res_tlwe0,const TLWElvl1 tlwe1,const KeySwitchingKey &ksk);

}