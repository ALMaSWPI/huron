#include <chrono>//NOLINT
#include <iostream>
#include <thread>//NOLINT

#include "mumei/driver/can/socket_can_bus.h"
#include "mumei/driver/config/config.h"
#include "mumei/odrive/odrive_can.h"
#include "mumei/odrive/odrive_enums.h"

using namespace std::chrono_literals; //NOLINT

int main(int argc, char* argv[]) {
  mumei::driver::can::SocketCanBus hcb{"can0", 0};
  std::cout << "HURONCanBus initialized successfully.\n";
  can_Message_t msg;

  // Set axis state IDLE
  msg.id = hcb.axis_id_ << mumei::odrive::ODriveCAN::NUM_CMD_ID_BITS;
  msg.id += mumei::odrive::ODriveCAN::MSG_SET_AXIS_REQUESTED_STATE;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<uint32_t>(msg, AXIS_STATE_IDLE, 0, 32, true);
  hcb.send_message(msg);

  std::this_thread::sleep_for(2s);

  // Set input mode & control mode
  msg.id = hcb.axis_id_ << mumei::odrive::ODriveCAN::NUM_CMD_ID_BITS;
  msg.id += mumei::odrive::ODriveCAN::MSG_SET_CONTROLLER_MODES;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<int32_t>(msg, CONTROL_MODE_TORQUE_CONTROL, 0, 32, true);
  can_setSignal<int32_t>(msg, INPUT_MODE_PASSTHROUGH, 32, 32, true);
  hcb.send_message(msg);
  std::cout << "Control mode and input mode set.\n";

  std::this_thread::sleep_for(2s);

  // Set limits
  msg.id = hcb.axis_id_ << mumei::odrive::ODriveCAN::NUM_CMD_ID_BITS;
  msg.id += mumei::odrive::ODriveCAN::MSG_SET_LIMITS;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<float>(msg, ODRIVE_VELOCITY_LIMIT, 0, 32, true);
  can_setSignal<float>(msg, ODRIVE_CURRENT_LIMIT, 32, 32, true);
  hcb.send_message(msg);
  std::cout << "Control mode and input mode set.\n";

  std::this_thread::sleep_for(2s);

  // Set axis state CALIB
  msg.id = hcb.axis_id_ << mumei::odrive::ODriveCAN::NUM_CMD_ID_BITS;
  msg.id += mumei::odrive::ODriveCAN::MSG_SET_AXIS_REQUESTED_STATE;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<uint32_t>(msg, AXIS_STATE_FULL_CALIBRATION_SEQUENCE, 0, 32,
                          true);
  hcb.send_message(msg);

  std::this_thread::sleep_for(25s);

  // Set axis state CLOSEDLOOP
  msg.id = hcb.axis_id_ << mumei::odrive::ODriveCAN::NUM_CMD_ID_BITS;
  msg.id += mumei::odrive::ODriveCAN::MSG_SET_AXIS_REQUESTED_STATE;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<uint32_t>(msg, AXIS_STATE_CLOSED_LOOP_CONTROL, 0, 32, true);
  hcb.send_message(msg);

  std::this_thread::sleep_for(2s);

  // Move motor
  msg.id = hcb.axis_id_ << mumei::odrive::ODriveCAN::NUM_CMD_ID_BITS;
  msg.id += mumei::odrive::ODriveCAN::MSG_SET_INPUT_TORQUE;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<float>(msg, 0.7, 0, 32, true);
  hcb.send_message(msg);
  std::cout << "Sending torque...\n";

  std::this_thread::sleep_for(2s);

  // Stop motor
  can_setSignal<float>(msg, 0.0, 0, 32, true);
  hcb.send_message(msg);
  std::cout << "Stopping...\n";

  // Set axis state IDLE
  msg.id = hcb.axis_id_ << mumei::odrive::ODriveCAN::NUM_CMD_ID_BITS;
  msg.id += mumei::odrive::ODriveCAN::MSG_SET_AXIS_REQUESTED_STATE;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<uint32_t>(msg, AXIS_STATE_IDLE, 0, 32, true);
  hcb.send_message(msg);

  std::this_thread::sleep_for(2s);
  return 0;
}
