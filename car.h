#define PI 3.14159266
#define STOP_RW 2
#define STOP_R 0
#define STOP_W 1
#define BUFFSIZE1 50
#define MSGLEN1 500

#define NDATA_P_GROUP 7

typedef struct stList {
// General type linked list

    char * elem;
    struct stList * next;

} List;

typedef struct stCtrlMsg {
    float accel;
    float brake;
    int gear;
    float focus[5];
    float clutch;
    int meta;
    float steer;
} CtrlMsg;

typedef struct stSensorMsg {
    double angle;
    float curLapTime;
    float damage;
    float distFromStart;
    float totalDistFromStart;
    float distRaced;
    int fuel;
    int gear;
    float lastLapTime;
    float opponents[36];
    int racePos;
    float rpm;
    float speedX;
    float speedY;
    float speedZ;
    float track[19];
    double trackPos;
    float wheelSpinVel[4];
    double z;
    float focus[5];
} SensorMsg;


