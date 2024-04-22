#pragma once

#include <mujoco/mujoco.h>

#include <string>
#include <vector>
#include <memory>

#include "huron/control_interfaces/legged_robot.h"


namespace huron {
namespace mujoco {

class Huron : public huron::LeggedRobot {
 public:
  explicit Huron(std::unique_ptr<huron::RobotConfiguration> config);
  Huron();
  Huron(const Huron&) = delete;
  Huron& operator=(const Huron&) = delete;
  ~Huron() override = default;

  // GenericComponent interface
  void Initialize() override;
  void SetUp() override;
  void Terminate() override;
};

}  // namespace mujoco
}  // namespace huron
