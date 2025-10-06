module Components {

    port MagDataPort (MagX: I32, MagY: I32, MagZ: I32)
    port FSSDataPort (Alpha: F32, Beta: F32, Error: U8)
    port CSSDataPort (ADCV0: U16, ADCV1: U16, ADCV2: U16, ADCV3: U16, ADCV4: U16, ADCV5: U16)
    port IMUDataPort (XLin: F32, YLin: F32, ZLin: F32, XAng: F32, YAng: F32, ZAng: F32)
    port RWDataPort  (RW0: F64, RW1: F64, RW2: F64)
    port STDataPort  (Q0: F64, Q1: F64, Q2: F64, Q3: F64, IsValid: U8)

    port TORQDataPort (Percent_0: U8, Direction_0: U8, Percent_1: U8, Direction_1: U8, Percent_2: U8, Direction_2: U8)
    port RWOUTDataPort  (Torque0: F64, Torque1: F64, Torque2: F64)
    
}