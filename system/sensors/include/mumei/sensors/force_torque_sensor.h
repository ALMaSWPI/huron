#pragma once

#include <eigen3/Eigen/Core>

#include <memory>
#include <string>

#include "mumei/control_interfaces/sensor_with_frame.h"
#include "mumei/types.h"

namespace mumei {

class ForceTorqueSensor : public SensorWithFrame {
 public:
  ForceTorqueSensor(const std::string& name,
                    bool reverse_wrench_direction,
                    std::weak_ptr<const multibody::Frame> frame);
  ForceTorqueSensor(const std::string& name,
                    bool reverse_wrench_direction,
                    std::weak_ptr<const multibody::Frame> frame,
                    std::unique_ptr<Configuration> config);
  ForceTorqueSensor(const ForceTorqueSensor&) = delete;
  ForceTorqueSensor& operator=(const ForceTorqueSensor&) = delete;
  ~ForceTorqueSensor() override = default;

  void RequestStateUpdate() override;

  void GetNewState(Eigen::Ref<Eigen::MatrixXd> new_state) const override;
  /**
   * Measures the external forces and moments.
   *
   * @return Wrench 6x1 vector \f$ [Fx, Fy, Fz, Tx, Ty, Tz]^T \f$.
   */
  Eigen::VectorXd GetValue() const override;

 protected:
  /**
   * To be overriden.
   */
  virtual Vector6d DoGetWrenchRaw() = 0;

  bool reverse_wrench_direction_;

 private:
  mumei::Vector6d wrench_;
};

}  // namespace mumei
