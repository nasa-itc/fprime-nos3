// ======================================================================
// \title  Generic_adcs.cpp
// \author jstar
// \brief  cpp file for Generic_adcs component implementation class
// ======================================================================

#include "Components/Generic_adcs/Generic_adcs.hpp"
#include "FpConfig.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_adcs ::
    Generic_adcs(const char* const compName) :
      Generic_adcsComponentBase(compName)
  {
    ingest_init(&DIPacket.Payload);
    init_ad_and_ac(&ADPacket.Payload, &GNCPacket.Payload, &ACSPacket.Payload);
    init_output(&DOPacket.Payload);
    
  }

  Generic_adcs ::
    ~Generic_adcs()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_adcs ::
    Placeholder_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->tlmWrite_PH(0);

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

  void Generic_adcs :: ingest_init(Generic_ADCS_DI_Tlm_Payload_t *DI)
  {
    //hardcoded instead of from the cfg

    //mag
    DI->Mag.qbs[0] = 0.0;
    DI->Mag.qbs[1] = 0.0;
    DI->Mag.qbs[2] = 0.0;
    DI->Mag.qbs[3] = 1.0;

    //fss
    DI->Fss.qbs[0] = 0.0;
    DI->Fss.qbs[1] = -0.7071;
    DI->Fss.qbs[2] = 0.0;
    DI->Fss.qbs[3] = 0.7071;

    //css
    DI->Css.Sensor[0].axis[0] = 1.0;
    DI->Css.Sensor[0].axis[1] = 0.0;
    DI->Css.Sensor[0].axis[2] = 0.0;
    DI->Css.Sensor[0].scale   = 0.001;

    DI->Css.Sensor[1].axis[0] = -1.0;
    DI->Css.Sensor[1].axis[1] = 0.0;
    DI->Css.Sensor[1].axis[2] = 0.0;
    DI->Css.Sensor[1].scale   = 0.001;

    DI->Css.Sensor[2].axis[0] = 0.0;
    DI->Css.Sensor[2].axis[1] = 1.0;
    DI->Css.Sensor[2].axis[2] = 0.0;
    DI->Css.Sensor[2].scale   = 0.001;

    DI->Css.Sensor[3].axis[0] = 0.0;
    DI->Css.Sensor[3].axis[1] = -1.0;
    DI->Css.Sensor[3].axis[2] = 0.0;
    DI->Css.Sensor[3].scale   = 0.001;

    DI->Css.Sensor[4].axis[0] = 0.0;
    DI->Css.Sensor[4].axis[1] = 0.0;
    DI->Css.Sensor[4].axis[2] = 1.0;
    DI->Css.Sensor[4].scale   = 0.001;

    DI->Css.Sensor[5].axis[0] = 0.0;
    DI->Css.Sensor[5].axis[1] = 0.0;
    DI->Css.Sensor[5].axis[2] = -1.0;
    DI->Css.Sensor[5].scale   = 0.001;

    //imu
    DI->Imu.qbs[0] = 0.0;
    DI->Imu.qbs[1] = 0.0;
    DI->Imu.qbs[2] = 0.0;
    DI->Imu.qbs[3] = 1.0;

    DI->Imu.pos[0] = 0.5;
    DI->Imu.pos[1] = 1.0;
    DI->Imu.pos[2] = 1.5;


    //rw
    double h_max[3] = {0.0, 0.0, 0.0};
    DI->Rw.whl_axis[0][0] =1.0;
    DI->Rw.whl_axis[0][1] =0.0;
    DI->Rw.whl_axis[0][2] =0.0;
    h_max[0] =0.01082;

    DI->Rw.whl_axis[1][0] =0.0;
    DI->Rw.whl_axis[1][1] =1.0;
    DI->Rw.whl_axis[1][2] =0.0;
    h_max[1] =0.01082;

    DI->Rw.whl_axis[2][0] =0.0;
    DI->Rw.whl_axis[2][1] =0.0;
    DI->Rw.whl_axis[2][2] =1.0;
    h_max[2] =0.01082;

    double H_in_body[3] = {0.0, 0.0, 0.0};
    for(int i = 0; i < 3; i++)
    {
      DI->Rw.H_maxB[i] = 0.0;
    }

    for (int whl = 0; whl < 3; whl++)
    {
        SxV(h_max[whl], DI->Rw.whl_axis[whl], H_in_body);
        for (int i = 0; i < 3; i++)
        {
            DI->Rw.H_maxB[i] += H_in_body[i];
        }
    }


    //st
    DI->St.qbs[0] = 0.0;
    DI->St.qbs[1] = 0.0;
    DI->St.qbs[2] = 0.0;
    DI->St.qbs[3] = 1.0;
  }

  void Generic_adcs :: init_ad_and_ac(Generic_ADCS_AD_Tlm_Payload_t *AD,
                                      Generic_ADCS_GNC_Tlm_Payload_t *GNC,
                                      Generic_ADCS_AC_Tlm_Payload_t  *ACS)
  {
    //Hardcode instead of reading from the cfg

    AD->Imu.alpha = 0.0;

    GNC->DT = 0.1;
    GNC->MaxMcmd = 1.42;

    ACS->Bdot.b_range = 4.096E-6;
    ACS->Bdot.Kb = 200.0;

    ACS->Sunsafe.Kp[0] = 0.0047;
    ACS->Sunsafe.Kp[1] = 0.0047;
    ACS->Sunsafe.Kp[2] = 0.0047;
    ACS->Sunsafe.Kr[0] = 0.1329;
    ACS->Sunsafe.Kr[1] = 0.1329;
    ACS->Sunsafe.Kr[2] = 0.1329;

    ACS->Sunsafe.sside[0] = 1.0;
    ACS->Sunsafe.sside[1] = 0.0;
    ACS->Sunsafe.sside[2] = 0.0;
    ACS->Sunsafe.vmax = 0.1;
    ACS->Sunsafe.cmd_wbn[0] = 0.0;
    ACS->Sunsafe.cmd_wbn[1] = 0.0;
    ACS->Sunsafe.cmd_wbn[2] = 0.0;

    for(int i = 0; i < 3; i++)
    {
      ACS->Sunsafe.therr[i] = ACS->Sunsafe.werr[i] = ACS->Sunsafe.Tcmd[i] = 0;
    }

    //skipped inertial

    GNC->Hmgmt.Kb = 1.0;
    GNC->Hmgmt.b_range = 4.096E-6;
    GNC->Hmgmt.loFrac = 0.1;
    GNC->Hmgmt.hiFrac = 0.5;
  }

  void Generic_adcs :: init_output(Generic_ADCS_DO_Tlm_Payload_t *DO)
  {
    DO->Trq.qba[0] = 0.0;
    DO->Trq.qba[1] = 0.0;
    DO->Trq.qba[2] = 0.0;
    DO->Trq.qba[3] = 1.0;

    DO->Rw.axis[0][0] = 1.0;
    DO->Rw.axis[0][1] = 0.0;
    DO->Rw.axis[0][2] = 0.0;

    DO->Rw.axis[1][0] = 0.0;
    DO->Rw.axis[1][1] = 1.0;
    DO->Rw.axis[1][2] = 0.0;

    DO->Rw.axis[2][0] = 0.0;
    DO->Rw.axis[2][1] = 0.0;
    DO->Rw.axis[2][2] = 1.0;
  }

}
