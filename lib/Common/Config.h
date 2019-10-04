#ifndef CONFIG_H
#define CONFIG_H

// MOTORS
    // Motor A
    #define mA_en 3
    #define mA_in1 23
    #define mA_in2 22

    // Motor B
    #define mB_en 4
    #define mB_in1 24
    #define mB_in2 25

    // Motor C
    #define mC_en 5
    #define mC_in1 26
    #define mC_in2 27
    
    // Motor D
    #define mD_en 6 
    #define mD_in1 28
    #define mD_in2 29

    // MOTOR OFFSETS
    #define mA_a -576.720973421242
    #define mB_a -950.43881286879
    #define mC_a -493.674039622371  
    #define mD_a -566.547251642468

    #define mA_b 215.595569133866
    #define mB_b 276.772370017802
    #define mC_b 210.832249154296
    #define mD_b 219.40386190851


    #define MOTOR1_OFFSET 1
    #define MOTOR2_OFFSET 1.37
    #define MOTOR3_OFFSET 1.07
    #define MOTOR4_OFFSET 1.07

// IMU
    #define HEADING_KP 4.0
    #define HEADING_KI 0.0
    #define HEADING_KD 0.3
    #define HEADING_MAX_CORRECTION 180

    #define IMU_CALIBRATION_COUNT 20
    #define IMU_CALIBRATION_TIME 50
    #define IMU_THRESHOLD 1000

    #define MPU9250_ADDRESS 0x68
    #define MAG_ADDRESS 0x0C

    #define GYRO_FULL_SCALE_250_DPS 0x00
    #define GYRO_FULL_SCALE_500_DPS 0x08
    #define GYRO_FULL_SCALE_1000_DPS 0x10
    #define GYRO_FULL_SCALE_2000_DPS 0x18

    #define ACC_FULL_SCALE_2_G 0x00
    #define ACC_FULL_SCALE_4_G 0x08
    #define ACC_FULL_SCALE_8_G 0x10
    #define ACC_FULL_SCALE_16_G 0x18

// Thermal
    #define MLX90614_I2CADDR 0x5A

    // RAM
        #define MLX90614_RAWIR1 0x04
        #define MLX90614_RAWIR2 0x05
        #define MLX90614_TA 0x06
        #define MLX90614_TOBJ1 0x07
        #define MLX90614_TOBJ2 0x08

    // EEPROM
        #define MLX90614_TOMAX 0x20
        #define MLX90614_TOMIN 0x21
        #define MLX90614_PWMCTRL 0x22
        #define MLX90614_TARANGE 0x23
        #define MLX90614_EMISS 0x24
        #define MLX90614_CONFIG 0x25
        #define MLX90614_ADDR 0x0E
        #define MLX90614_ID1 0x3C
        #define MLX90614_ID2 0x3D
        #define MLX90614_ID3 0x3E
        #define MLX90614_ID4 0x3F
// LRF
    #define VL53L0X_REG_IDENTIFICATION_MODEL_ID         0xc0
    #define VL53L0X_REG_IDENTIFICATION_REVISION_ID      0xc2
    #define VL53L0X_REG_PRE_RANGE_CONFIG_VCSEL_PERIOD   0x50
    #define VL53L0X_REG_FINAL_RANGE_CONFIG_VCSEL_PERIOD 0x70
    #define VL53L0X_REG_SYSRANGE_START                  0x00
    #define VL53L0X_REG_RESULT_INTERRUPT_STATUS         0x13
    #define VL53L0X_REG_RESULT_RANGE_STATUS             0x14
    #define VL53L0X_ADDRESS 0x29

    #define VL53L0X_XSHUT_pin1 50
    #define VL53L0X_XSHUT_pin2 51
    #define VL53L0X_XSHUT_pin3 52
    #define VL53L0X_XSHUT_pin4 53


    //ADDRESS_DEFAULT 0b0101001 or 41
    #define VL53L0x_DEFAULT_ADDRESS 41
    //#define Sensor1_newAddress 41 not required address change
    #define VL53L0X_Sensor2_newAddress 42
    #define VL53L0X_Sensor3_newAddress 43
    #define VL53L0X_Sensor4_newAddress 44

// Color Sensors
    #define TCS230_Sensor1_S0 30
    #define TCS230_Sensor1_S1 31
    #define TCS230_Sensor1_S2 32
    #define TCS230_Sensor1_S3 33
    #define TCS230_Sensor1_OUT 34

    #define TCS230_Sensor2_S0 35
    #define TCS230_Sensor2_S1 36
    #define TCS230_Sensor2_S2 37
    #define TCS230_Sensor2_S3 38
    #define TCS230_Sensor2_OUT 39

    #define TCS230_Sensor3_S0 40
    #define TCS230_Sensor3_S1 41
    #define TCS230_Sensor3_S2 42
    #define TCS230_Sensor3_S3 43
    #define TCS230_Sensor3_OUT 44

    #define TCS230_Sensor4_S0 45
    #define TCS230_Sensor4_S1 46
    #define TCS230_Sensor4_S2 47
    #define TCS230_Sensor4_S3 48
    #define TCS230_Sensor4_OUT 49

    #define CALIBRATION_COUNT 50


    #define COLOR_FRONT 900
    #define COLOR_RIGHT 900
    #define COLOR_BACK 1100
    #define COLOR_LEFT 90


// Light Sensor
    #define LIGHT_OUT_N 12
    #define LIGHT_OUT_E 13
    #define LIGHT_OUT_S 14
    #define LIGHT_OUT_W 15

    #define LIGHT_CALIBRATION_COUNT 10

    #define LIGHT_FRONT 450
    #define LIGHT_RIGHT 500
    #define LIGHT_BACK 500
    #define LIGHT_LEFT 500

// LED
    #define LED_PIN 7


// Constants
    #define WALL_THRESHOLD 150
    #define BLACK_THRESHOLD 450
    #define TIME_TO_TRAVEL 850
    #define EXTRA_SIDEWAYS_TIME 450
    #define BASELINE_SPEED 50

    // Sideways Offsets
    #define MOTOR1_SIDEWAYS_OFFSET 1.7
    #define MOTOR2_SIDEWAYS_OFFSET 1.5
    #define MOTOR3_SIDEWAYS_OFFSET 1.7
    #define MOTOR4_SIDEWAYS_OFFSET 1.5


    // #define E 2.718281828459045235360287471352662497757247093699959574966967627724076630353

    #define MAZE_X 17
    #define MAZE_Y 17
#endif
