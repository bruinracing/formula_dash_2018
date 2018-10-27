#ifndef CONDITIONS_H
#define CONDITIONS_H

#include "constants.h"

#define RPM_ACTIVE (rpm > 0)
#define CLT_ACTIVE (clt > 0)
#define BAT_ACTIVE (bat > 0)

#define ENGINE_RUNNING (rpm > RPM_RANGE0)
#define SHIFT_POINT1   (rpm > RPM_RANGE5)
#define SHIFT_POINT2   (rpm > RPM_RANGE6)

#define ENGINE_COLD      (clt <= CLT_RANGE0)
#define ENGINE_OPERATING (clt > CLT_RANGE0 && clt <= CLT_RANGE1)
#define ENGINE_HOT       (clt > CLT_RANGE1 && clt <= CLT_RANGE2)
#define ENGINE_OVERHEAT  (clt > CLT_RANGE2)

#define BATTERY_LOW  (bat < BAT_RANGE0)
#define BATTERY_HIGH (bat > BAT_RANGE1)

#endif // CONDITIONS_H
