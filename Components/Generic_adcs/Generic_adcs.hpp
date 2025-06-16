// ======================================================================
// \title  Generic_adcs.hpp
// \author jstar
// \brief  hpp file for Generic_adcs component implementation class
// ======================================================================

#ifndef Components_Generic_adcs_HPP
#define Components_Generic_adcs_HPP

#include "Components/Generic_adcs/Generic_adcsComponentAc.hpp"

extern "C"{
  #include "generic_adcs_utilities.h"
  #include "generic_adcs_msg.h"
}

#define NANO 10e-9
#define EPS 1.0E-6

#define PASSIVE_MODE 0
#define BDOT_MODE    1
#define SUNSAFE_MODE 2

namespace Components {

  class Generic_adcs :
    public Generic_adcsComponentBase
  {

    public:

    Generic_ADCS_Hk_tlm_t  HkTelemetryPkt; /* GENERIC_ADCS Housekeeping Telemetry Packet */
    Generic_ADCS_DI_Tlm_t  DIPacket;
    Generic_ADCS_AD_Tlm_t  ADPacket;
    Generic_ADCS_GNC_Tlm_t GNCPacket;
    Generic_ADCS_AC_Tlm_t  ACSPacket;
    Generic_ADCS_DO_Tlm_t  DOPacket;

    U32 ingestIMUCount = 0;
    U32 ingestMagCount = 0;
    U32 ingestFSSCount = 0;
    U32 ingestCSSCount = 0;
    U32 ingestRWCount = 0;
    U32 ingestSTCount = 0;

    struct
    {
        uint8_t Direction;
        uint8_t PercentOn;
    } CurrentMtb[3];

    int16_t CurrentRw[3];

    
      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct Generic_adcs object
      Generic_adcs(
          const char* const compName //!< The component name
      );

      //! Destroy Generic_adcs object
      ~Generic_adcs();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for commands
      // ----------------------------------------------------------------------

      //! Handler implementation for command TODO
      //!
      //! TODO

      void IMUin_handler(
        NATIVE_INT_TYPE portNum,
        F32 XLin,
        F32 YLin,
        F32 ZLin,
        F32 XAng,
        F32 YAng,
        F32 ZAng
      ) override;

      void ingest_init(Generic_ADCS_DI_Tlm_Payload_t *DI);
      void init_adac(Generic_ADCS_AD_Tlm_Payload_t *AD,
                          Generic_ADCS_GNC_Tlm_Payload_t *GNC,
                          Generic_ADCS_AC_Tlm_Payload_t  *ACS);
      
      void init_output(Generic_ADCS_DO_Tlm_Payload_t *DO);

      // all of these ingests need fprime ports with input from respective components
      // periodic or event-based update
      void ingest_mag(I32 MagIntX, I32 MagIntY, I32 MagIntZ, Generic_ADCS_DI_Mag_Tlm_Payload_t *Mag);

      void ingest_fss(U32 Alpha, U32 Beta, U8 Error, Generic_ADCS_DI_Fss_Tlm_Payload_t *Fss);

      void ingest_css(U16 ADCV0, U16 ADCV1, U16 ADCV2, U16 ADCV3, U16 ADCV4, U16 ADCV5, Generic_ADCS_DI_Css_Tlm_Payload_t *Css);

      void ingest_imu(F32 LinX, F32 LinY, F32 LinZ, F32 AngX, F32 AngY, F32 AngZ, Generic_ADCS_DI_Imu_Tlm_Payload_t *Imu);

      void ingest_rw(F64 RW0, F64 RW1, F64 RW2, Generic_ADCS_DI_Rw_Tlm_Payload_t *Rw);

      void ingest_st(F64 Q0, F64 Q1, F64 Q2, F64 Q3, U8 IsValid, Generic_ADCS_DI_St_Tlm_Payload_t *St);

      // needs to be called periodically or after an ingest is called
      void exec_adac( const Generic_ADCS_DI_Tlm_Payload_t *DI,
                      Generic_ADCS_AD_Tlm_Payload_t       *AD,
                      Generic_ADCS_GNC_Tlm_Payload_t      *GNC,
                      Generic_ADCS_AC_Tlm_Payload_t       *ACS);

      void AD_imu(const Generic_ADCS_DI_Imu_Tlm_Payload_t *DI_IMU, Generic_ADCS_AD_Imu_Tlm_Payload_t *AD_IMU);
      void AD_mag(const Generic_ADCS_DI_Mag_Tlm_Payload_t *DI_Mag, Generic_ADCS_AD_Mag_Tlm_Payload_t *AD_Mag);
      void AD_sol(const Generic_ADCS_DI_Fss_Tlm_Payload_t *DI_FSS, const Generic_ADCS_DI_Css_Tlm_Payload_t *DI_CSS,
                        Generic_ADCS_AD_Sol_Tlm_Payload_t *AD_Sol);
      void AD_to_GNC(const Generic_ADCS_AD_Tlm_Payload_t *AD, Generic_ADCS_GNC_Tlm_Payload_t *GNC);
      void AC_bdot(Generic_ADCS_GNC_Tlm_Payload_t *GNC, Generic_ADCS_AC_Bdot_Tlm_t *AC_bdot);
      void AC_sunsafe(Generic_ADCS_GNC_Tlm_Payload_t *GNC, Generic_ADCS_AC_Sunsafe_Tlm_t *ACS);
      void AC_h_mgmt(Generic_ADCS_GNC_Tlm_Payload_t *GNC);

      void output_actuators(Generic_ADCS_GNC_Tlm_Payload_t *GNC, Generic_ADCS_DO_Tlm_Payload_t *DO,
                            GENERIC_TORQUER_All_Percent_On_cmd_t *MtbPctOnCmd, GENERIC_RW_Cmd_t *RwCmd);
      
      void send_mtb_commands(double Mcmd[3], Generic_ADCS_DO_Trq_TlmPayload_t *DO,
                            GENERIC_TORQUER_All_Percent_On_cmd_t *MtbPctOnCmd);

      void mcmd_to_percent_direction(double Mcmd, uint8_t *percent, uint8_t *direction);

      void  send_rw_commands(double Tcmd[3], Generic_ADCS_DO_Rw_TlmPayload_t *DO, GENERIC_RW_Cmd_t *RwCmd);

  };

}

#endif
