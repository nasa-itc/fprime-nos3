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

// typedef struct
// {
//     uint8_t                   Mode;
// } Generic_ADCS_Mode_cmd_t;

// typedef struct
// {
//     uint8_t                   MomentumManagement;
// } Generic_ADCS_MomentumManagement_cmd_t;

// typedef struct
// {
//     float                   qbn[4];
// } Generic_ADCS_Quat_cmd_t;

// /*
// ** Generic_ADCS housekeeping type definition
// */
// typedef struct
// {
//     uint8_t                     CommandErrorCount;
//     uint8_t                     CommandCount;
// } __attribute__((packed)) Generic_ADCS_Hk_tlm_t;
// #define GENERIC_ADCS_HK_TLM_LNGTH sizeof(Generic_ADCS_Hk_tlm_t)

// /*
// ** Generic_ADCS DI type definition
// */
// typedef struct
// {
//     double qbs[4]; // quaternion from sensor to body
//     double bvb[3]; // magnetic field measurement by sensor in body frame
// } __attribute__((packed)) Generic_ADCS_DI_Mag_Tlm_Payload_t;

// typedef struct
// {
//     double qbs[4]; // quaternion from sensor to body
//     uint8_t  valid;
//     double svb[3]; // sun vector from sensor in body frame
// } __attribute__((packed)) Generic_ADCS_DI_Fss_Tlm_Payload_t;

// typedef struct
// {
//     double axis[3]; // CSS axis in body frame
//     double scale;   // scale factor
//     double percenton;
// } __attribute__((packed)) Generic_ADCS_DI_Css_Sensor_Payload_t;

// typedef struct
// {
//     Generic_ADCS_DI_Css_Sensor_Payload_t Sensor[6];
//     uint8_t                                valid;
//     double                               svb[3]; // sun vector from sensors in body frame
// } __attribute__((packed)) Generic_ADCS_DI_Css_Tlm_Payload_t;

// typedef struct
// {
//     double qbs[4]; // quaternion from sensor to body
//     double pos[3]; // position of sensor in body
//     uint8_t  valid;
//     double wbn[3]; // angular rate
//     double acc[3]; // acceleration
// } __attribute__((packed)) Generic_ADCS_DI_Imu_Tlm_Payload_t;

// typedef struct
// {
//     double whl_axis[3][3];
//     double H_maxB[3];
//     double HwhlB[3];
// } __attribute__((packed)) Generic_ADCS_DI_Rw_Tlm_Payload_t;

// typedef struct
// {
//     double qbs[4]; // quaternion from sensor to body
//     double q[4];
//     uint8_t  valid;
// } __attribute__((packed)) Generic_ADCS_DI_St_Tlm_Payload_t;

// typedef struct
// {
//     Generic_ADCS_DI_Mag_Tlm_Payload_t Mag;
//     Generic_ADCS_DI_Fss_Tlm_Payload_t Fss;
//     Generic_ADCS_DI_Css_Tlm_Payload_t Css;
//     Generic_ADCS_DI_Imu_Tlm_Payload_t Imu;
//     Generic_ADCS_DI_Rw_Tlm_Payload_t  Rw;
//     Generic_ADCS_DI_St_Tlm_Payload_t  St;
// } __attribute__((packed)) Generic_ADCS_DI_Tlm_Payload_t;

// typedef struct
// {
//     Generic_ADCS_DI_Tlm_Payload_t Payload;
// } __attribute__((packed)) Generic_ADCS_DI_Tlm_t;
// #define GENERIC_ADCS_DI_LNGTH sizeof(Generic_ADCS_DI_Tlm_t)

// /*
// ** Generic_ADCS AD type definition
// */
// typedef struct
// {
//     double bvb[3];
// } __attribute__((packed)) Generic_ADCS_AD_Mag_Tlm_Payload_t;

// typedef struct
// {
//     uint8_t  SunValid;
//     uint8_t  FssValid;
//     double svb[3];
// } __attribute__((packed)) Generic_ADCS_AD_Sol_Tlm_Payload_t;

// typedef struct
// {
//     uint8_t  init;
//     double alpha;
//     uint8_t  valid;
//     double wbn_prev[3];
//     double wbn[3];
//     double acc[3];
// } __attribute__((packed)) Generic_ADCS_AD_Imu_Tlm_Payload_t;

// typedef struct
// {
//     uint8_t  Valid;  /* [-] data validity flag */
//     double qbn[4]; /* [-] quaternion expressed in body frame */
// } __attribute__((packed)) Generic_ADCS_AD_ST_Tlm_Payload_t;

// typedef struct
// {
//     Generic_ADCS_AD_Mag_Tlm_Payload_t Mag;
//     Generic_ADCS_AD_Sol_Tlm_Payload_t Sol;
//     Generic_ADCS_AD_Imu_Tlm_Payload_t Imu;
//     Generic_ADCS_AD_ST_Tlm_Payload_t  ST;
// } __attribute__((packed)) Generic_ADCS_AD_Tlm_Payload_t;

// typedef struct
// {
//     Generic_ADCS_AD_Tlm_Payload_t Payload;
// } __attribute__((packed)) Generic_ADCS_AD_Tlm_t;
// #define GENERIC_ADCS_AD_LNGTH sizeof(Generic_ADCS_AD_Tlm_t)

// /*
// ** Generic_ADCS GNC type definition
// */
// typedef struct
// {
//     double Kb;
//     double b_range;
//     double loFrac;
//     double hiFrac;
//     uint8_t  mm_active[3];
//     double Mcmd[3];
// } __attribute__((packed)) Generic_ADCS_GNC_Hmgmt_t;

// typedef struct
// {
//     double                   DT;
//     double                   MaxMcmd;
//     uint8_t                    Mode;
//     uint8_t                    HmgmtOn;
//     Generic_ADCS_GNC_Hmgmt_t Hmgmt;
//     double                   bvb[3];
//     double                   svb[3];
//     uint8_t                    SunValid;
//     double                   wbn[3];
//     double                   HwhlMaxB[3];
//     double                   HwhlB[3];
//     double                   Mcmd[3];
//     double                   Tcmd[3];
//     uint8_t                    qValid;
//     double                   qbn[4];
//     double                   qErr[4];
// } __attribute__((packed)) Generic_ADCS_GNC_Tlm_Payload_t;

// typedef struct
// {
//     Generic_ADCS_GNC_Tlm_Payload_t Payload;
// } __attribute__((packed)) Generic_ADCS_GNC_Tlm_t;
// #define GENERIC_ADCS_GNC_LNGTH sizeof(Generic_ADCS_GNC_Tlm_t)

// /*
// ** Generic_ADCS AC type definition
// */
// typedef struct
// {
//     double b_range;
//     double Kb;
//     double bold[3];
//     double bdot[3];
// } __attribute__((packed)) Generic_ADCS_AC_Bdot_Tlm_t;

// typedef struct
// {
//     /* Inputs*/
//     double Kp[3];
//     double Kr[3];
//     double sside[3];
//     double vmax;
//     double cmd_wbn[3];
//     uint8_t  h_mgmt;

//     /* Internal Variables */
//     double therr[3];
//     double werr[3];
//     double Tcmd[3];
//     double err_t;
// } __attribute__((packed)) Generic_ADCS_AC_Sunsafe_Tlm_t;

// typedef struct
// {
//     /* Inputs*/
//     double Kp[3];
//     double Kr[3];
//     double Ki[3];
//     double phiErr_max;
//     double qbn_cmd[4];
//     long   h_mgmt;

//     /* Internal Variables */
//     double therr[3];
//     double sumtherr[3];
//     double qErr[4];
//     double werr[3];
//     double Tcmd[3];
// } __attribute__((packed)) Generic_ADCS_AC_Inertial_Tlm_t;

// typedef struct
// {
//     Generic_ADCS_AC_Bdot_Tlm_t     Bdot;
//     Generic_ADCS_AC_Sunsafe_Tlm_t  Sunsafe;
//     Generic_ADCS_AC_Inertial_Tlm_t Inertial;
// } __attribute__((packed)) Generic_ADCS_AC_Tlm_Payload_t;

// typedef struct
// {
//     Generic_ADCS_AC_Tlm_Payload_t Payload;
// } __attribute__((packed)) Generic_ADCS_AC_Tlm_t;
// #define GENERIC_ADCS_AC_LNGTH sizeof(Generic_ADCS_AC_Tlm_t)

// /*
// ** Generic_ADCS DO type definition
// */
// typedef struct
// {
//     double qba[4]; // quaternion from actuator to body
//     double Mcmd[3];
// } __attribute__((packed)) Generic_ADCS_DO_Trq_TlmPayload_t;

// typedef struct
// {
//     double axis[3][3];
//     double Tcmd[3];
// } __attribute__((packed)) Generic_ADCS_DO_Rw_TlmPayload_t;

// typedef struct
// {
//     Generic_ADCS_DO_Trq_TlmPayload_t Trq;
//     Generic_ADCS_DO_Rw_TlmPayload_t  Rw;
// } __attribute__((packed)) Generic_ADCS_DO_Tlm_Payload_t;

// typedef struct
// {
//     Generic_ADCS_DO_Tlm_Payload_t Payload;
// } __attribute__((packed)) Generic_ADCS_DO_Tlm_t;
// #define GENERIC_ADCS_DO_LNGTH sizeof(Generic_ADCS_DO_Tlm_t)

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
      void Placeholder_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq //!< The command sequence number
      ) override;

      void ingest_init(Generic_ADCS_DI_Tlm_Payload_t *DI);
      void init_ad_and_ac(Generic_ADCS_AD_Tlm_Payload_t *AD,
                          Generic_ADCS_GNC_Tlm_Payload_t *GNC,
                          Generic_ADCS_AC_Tlm_Payload_t  *ACS);
      
      void init_output(Generic_ADCS_DO_Tlm_Payload_t *DO);

      void ingest_mag(I32 MagIntX, I32 MagIntY, I32 MagIntZ, Generic_ADCS_DI_Mag_Tlm_Payload_t *Mag);

      void ingest_fss(U32 Alpha, U32 Beta, U8 Error, Generic_ADCS_DI_Fss_Tlm_Payload_t *Fss);

      void ingest_css(U16 ADCV0, U16 ADCV1, U16 ADCV2, U16 ADCV3, U16 ADCV4, U16 ADCV5, Generic_ADCS_DI_Css_Tlm_Payload_t *Css);

      void ingest_imu(F32 LinX, F32 LinY, F32 LinZ, F32 AngX, F32 AngY, F32 AngZ, Generic_ADCS_DI_Imu_Tlm_Payload_t *Imu);

      void ingest_rw(F64 RW0, F64 RW1, F64 RW2, Generic_ADCS_DI_Rw_Tlm_Payload_t *Rw);

      void ingest_st(F64 Q0, F64 Q1, F64 Q2, F64 Q3, U8 IsValid, Generic_ADCS_DI_St_Tlm_Payload_t *St);

  };

}

#endif
