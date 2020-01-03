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
  static const TrackingConfig EIGHT_STEP(MotorStepConfigs::EIGHTH_STEP, FULL_STEP_PERIOD_MS / 8, 'E');
  static const TrackingConfig SIXTEENTH_STEP(MotorStepConfigs::SIXTEENTH_STEP, FULL_STEP_PERIOD_MS / 16, 'S');
}

// namespace TrackingConfigs {
//   static const TrackingConfig FULL_STEP(MotorStepConfigs::FULL_STEP, 3000, 'F');
//   static const TrackingConfig HALF_STEP(MotorStepConfigs::HALF_STEP, 1500, 'H');
//   static const TrackingConfig QUARTER_STEP(MotorStepConfigs::HALF_STEP, 1450, 'Q');
//   static const TrackingConfig EIGHT_STEP(MotorStepConfigs::HALF_STEP, 1400, 'E');
//   static const TrackingConfig SIXTEENTH_STEP(MotorStepConfigs::HALF_STEP, 1300, 'S');
// }

// namespace TrackingConfigs {
//   static const TrackingConfig FULL_STEP(MotorStepConfigs::HALF_STEP, 1500, 'F');
//   static const TrackingConfig HALF_STEP(MotorStepConfigs::HALF_STEP, 1400, 'H');
//   static const TrackingConfig QUARTER_STEP(MotorStepConfigs::QUARTER_STEP, 750, 'Q');
//   static const TrackingConfig EIGHT_STEP(MotorStepConfigs::QUARTER_STEP, 700, 'E');
//   static const TrackingConfig SIXTEENTH_STEP(MotorStepConfigs::QUARTER_STEP, 650, 'S');
// }
