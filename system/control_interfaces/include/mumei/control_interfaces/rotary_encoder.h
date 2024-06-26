#pragma once

#include <cmath>
#include <set>
#include <string>
#include <utility>
#include <memory>

#include "encoder.h"

namespace mumei {

class RotaryEncoderConfiguration : public EncoderConfiguration {
 public:
  /**
   * Supports further inheritance.
   */
  RotaryEncoderConfiguration(ConfigMap config_map,
                             std::set<std::string> valid_keys)
      : EncoderConfiguration(config_map,
                             [&valid_keys]() {
                               std::set<std::string> tmp(kRotEncValidKeys);
                               tmp.merge(valid_keys);
                               return tmp;
                             }()) {}

  explicit RotaryEncoderConfiguration(double cpr)
      : RotaryEncoderConfiguration(
          ConfigMap({{"cpr", cpr}}), {}) {}

 private:
  static const inline std::set<std::string> kRotEncValidKeys{"cpr"};
};

/**
 * Abstract class for using an encoder.
 *
 * @ingroup control_interfaces
 */
class RotaryEncoder : public Encoder {
 public:
  RotaryEncoder(const std::string& name,
                double gear_ratio,
                std::unique_ptr<RotaryEncoderConfiguration> config)
    : Encoder(name, gear_ratio, std::move(config)) {
    cpr_ = std::any_cast<double>(config_.get()->Get("cpr"));
  }
  RotaryEncoder(const std::string& name,
                double gear_ratio,
                double cpr)
      : RotaryEncoder(name,
                      gear_ratio,
                      std::make_unique<RotaryEncoderConfiguration>(cpr)) {}
  RotaryEncoder(const std::string& name, double cpr)
      : RotaryEncoder(name, 1.0, cpr) {}
  RotaryEncoder(const RotaryEncoder&) = delete;
  RotaryEncoder& operator=(const RotaryEncoder&) = delete;
  ~RotaryEncoder() override = default;

  void RequestStateUpdate() final {
    prev_count_ = count_;
    prev_velocity_ = velocity_;
    DoUpdateState();
  }

  /**
     * Gets the current encoder count.
     */
  double GetCount() const {
    return count_;
  }

  /**
     * Gets the current encoder velocity in count.
     */
  double GetVelocityCount() const {
    return velocity_;
  }

  /**
     * Gets the previous encoder count.
     */
  double GetPrevCount() const {
    return prev_count_;
  }

  /**
     * Gets the counts per revolution (CPR).
     */
  double GetCPR() const {
    return cpr_;
  }

  /**
     * Gets the current angle in radians. This takes into account the gear ratio
     * and CPR.
     */
  double GetPosition() const override {
    return count_ / cpr_ * 2.0 * M_PI / gear_ratio_;
  }

  /**
     * Gets the current angle in degrees. This takes into account the gear ratio
     * and CPR.
     */
  double GetAngleDegree() const {
    return count_ / cpr_ * 360.0 / gear_ratio_;
  }

  /**
     * Gets the current velocity in radians/second. This takes into account the
     * gear ratio and CPR.
     */
  double GetVelocity() const override {
    return velocity_ / cpr_ * 2 * M_PI / gear_ratio_;
  }

  /**
     * Gets the current velocity in degrees/second. This takes into account the
     * gear ratio and CPR.
     */
  double GetVelocityDegree() const {
    return velocity_ / cpr_ * 360.0 / gear_ratio_;
  }

  /**
     * Resets the encoder count.
     */
  void Reset() override {
    count_ = 0.0;
    prev_count_ = 0.0;
  }

 protected:
  /**
   * Classes derived from RotaryEncoder should override this function instead
   * of directly overriding RequestUpdateState(). RotaryEncoder already handled
   * the internal count update for convenience.
   *
   * This function should update the current count (count_) and, if possible,
   * velocity (velocity_).
   */
  virtual void DoUpdateState() = 0;

  /// \brief Encoder velocity in counts per second.
  double velocity_ = 0.0;
  /// \brief Encoder previous velocity in counts per second.
  double prev_velocity_ = 0.0;
  double count_ = 0.0;
  double prev_count_ = 0.0;
  double cpr_;
};

}  // namespace mumei
