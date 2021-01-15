#pragma once

#define DATA_PUBLISH_PERIOD_SECS 60
#define NETWORK_TIME_SYNC_HOURS 24

#define VIPER_LOCK D3
#define VIPER_UNLOCK D2
#define VIPER_REMOTE_START D4

#define VIPER_REMOTE_START_DURATION_SECS 12 * 60
#define VIPER_REMOTE_START_DELAY_UNTIL_NEXT_SECS 3 * 60
#define VIPER_REMOTE_START_MAX_STARTS_PER_SESSION 40

#define VOLTMETER_PIN A5
#define VOLTMETER_ADC_MAX 4096
#define VOLTMETER_R_TOP 1000000
#define VOLTMETER_R_BOTTOM 100400
#define VOLTMETER_SAMPLE_COUNT 5
#define VOLTMETER_MAX_BOUND 50

#include "const_auth.h"