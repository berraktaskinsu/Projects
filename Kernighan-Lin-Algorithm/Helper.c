#include "Helper.h"

int FindNearestPowerOfTwo(int originalPower) {
    int nearestPower;
    double power = log((double) originalPower) / log(2);
    if (power == ((double)((int) power))) {
        nearestPower = power + 1;
    } 
    else 
    {
        nearestPower = (int) ceil(power);
    }
    return (int) pow(2, nearestPower) -1;
}
