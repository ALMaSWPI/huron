#pragma once

#include <string>

#include "state_provider.h"

namespace mumei {

class ConstantStateProvider : public StateProvider {
 public:
  ConstantStateProvider(const std::string& name,
                                 const Eigen::MatrixXd& state)
    : StateProvider(name, state.rows(), state.cols()),
      state_(state) {}
  ConstantStateProvider(const ConstantStateProvider&) = delete;
  ConstantStateProvider& operator=(const ConstantStateProvider&) = delete;
  ~ConstantStateProvider() override = default;

  void RequestStateUpdate() override {}
  void GetNewState(Eigen::Ref<Eigen::MatrixXd> new_state) const override {
    new_state = state_;
  }

  void SetState(const Eigen::MatrixXd& state) {
    assert(state.rows() == dim()[0] && state.cols() == dim()[1]);
    state_ = state;
  }

 private:
  Eigen::MatrixXd state_;
};

}  // namespace mumei
