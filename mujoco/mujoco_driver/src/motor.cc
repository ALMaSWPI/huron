#include "mumei/mujoco/motor.h"
#include "mumei/mujoco/mujoco_env.h"

namespace mumei {
namespace mujoco {

Motor::Motor(const std::string& name, int mj_id,
             std::weak_ptr<MujocoEnvironment> env, double gear_ratio)
    : mumei::Motor(name, gear_ratio), mj_id_(mj_id), env_(env) {}

void Motor::Initialize() {
}

void Motor::SetUp() {
}

void Motor::Terminate() {
}

bool Motor::Move(const std::vector<double>& values) {
  return Move(values[0]);
}

bool Motor::Move(const Eigen::VectorXd& values) {
  return Move(values[0]);
}

bool Motor::Stop() {
  return Move(0.0);
}

bool Motor::Move(double value) {
  env_.lock()->SetMotorValue(mj_id_, value);
  return true;
}

}  // namespace mujoco
}  // namespace mumei
