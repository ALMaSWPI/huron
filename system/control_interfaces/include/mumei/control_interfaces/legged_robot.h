#pragma once

#include <eigen3/Eigen/Core>

#include <memory>

#include "robot.h"
#include "mumei/locomotion/zero_moment_point.h"

namespace mumei {

class LeggedRobot : public Robot {
 public:
  explicit LeggedRobot(std::unique_ptr<RobotConfiguration> config);
  LeggedRobot();
  LeggedRobot(const LeggedRobot&) = delete;
  LeggedRobot& operator=(const LeggedRobot&) = delete;
  ~LeggedRobot() override = default;

  void InitializeZmp(std::shared_ptr<ZeroMomentPoint> zmp);
  /**
   * Computes the Center of Mass in Base frame.
   */
  Eigen::Vector2d EvalZeroMomentPoint();

 private:
  std::shared_ptr<ZeroMomentPoint> zmp_;
};

}  // namespace mumei
