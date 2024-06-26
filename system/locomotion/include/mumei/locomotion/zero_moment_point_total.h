#pragma once

#include <memory>
#include <vector>

#include "mumei/locomotion/zero_moment_point.h"

namespace mumei {

class ZeroMomentPointTotal : public ZeroMomentPoint {
 public:
  ZeroMomentPointTotal(
    std::weak_ptr<const multibody::Frame> zmp_frame,
    const std::vector<std::shared_ptr<ZeroMomentPoint>>& zmp_vector);
  ZeroMomentPointTotal(const ZeroMomentPointTotal&) = delete;
  ZeroMomentPointTotal& operator=(const ZeroMomentPointTotal&) = delete;
  ~ZeroMomentPointTotal() override = default;

  Eigen::Vector2d Eval(double& fz) override;

 private:
  std::vector<std::shared_ptr<ZeroMomentPoint>> zmp_vector_;
};

}  // namespace mumei
