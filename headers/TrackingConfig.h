#pragma once

#include "MotorStepConfig.h"

const int FULL_STEP_PERIOD_MS = 3000;

class TrackingConfig {
    public:
      TrackingConfig(const MotorStepConfig& motorStepConfig, int tickPeriodMillis, char encodedConfig): 
        motorStepConfig(motorStepConfig), tickPeriodMillis(tickPeriodMillis), encodedConfig(encodedConfig) {};

      const MotorStepConfig& motorStepConfig;
      int tickPeriodMillis;
      char encodedConfig;
};

namespace TrackingConfigs {
  static const TrackingConfig FULL_STEP(MotorStepConfigs::FULL_STEP, FULL_STEP_PERIOD_MS, 'F');
  static const TrackingConfig HALF_STEP(MotorStepConfigs::HALF_STEP, FULL_STEP_PERIOD_MS / 2, 'H');
  static const TrackingConfig QUARTER_STEP(MotorStepConfigs::QUARTER_STEP, FULL_STEP_PERIOD_MS / 4, 'Q');
}
