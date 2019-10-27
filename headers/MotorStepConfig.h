#pragma once

class MotorStepConfig {
  public:
    MotorStepConfig(bool ms1, bool ms2, bool ms3): ms1(ms1), ms2(ms2), ms3(ms3) {};
    bool ms1, ms2, ms3;
};

namespace MotorStepConfigs {
  static const MotorStepConfig FULL_STEP(LOW, LOW, LOW);
  static const MotorStepConfig HALF_STEP(HIGH, LOW, LOW);
  static const MotorStepConfig QUARTER_STEP(LOW, HIGH, LOW);
  static const MotorStepConfig EIGHTH_STEP(HIGH, HIGH, LOW);
  static const MotorStepConfig SIXTEENTH_STEP(HIGH, HIGH, HIGH);
}
