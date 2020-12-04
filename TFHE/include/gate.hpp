#pragma onece

#include<array>
#include<vector>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>

namespace myTFHE{

    void HomNAND(TLWElvl0 &res_tlwe,const TLWElvl0 &tlweA,const TLWElvl0 &tlweB,const GateKey &gk);
    void HomAND(TLWElvl0 &res_tlwe,const TLWElvl0 &tlweA,const TLWElvl0 &tlweB,const GateKey &gk);
    void HomNOT(TLWElvl0 &res_tlwe,const TLWElvl0 &tlweA,const GateKey &gk);
    void HomOR(TLWElvl0 &res_tlwe,const TLWElvl0 &tlweA,const TLWElvl0 &tlweB,const GateKey &gk);
    void HomNOR(TLWElvl0 &res_tlwe,const TLWElvl0 &tlweA,const TLWElvl0 &tlweB,const GateKey &gk);
    void HomXOR(TLWElvl0 &res_tlwe,const TLWElvl0 &tlweA,const TLWElvl0 &tlweB,const GateKey &gk);
    void HomXNOR(TLWElvl0 &res_tlwe,const TLWElvl0 &tlweA,const TLWElvl0 &tlweB,const GateKey &gk);

} // myTFHE