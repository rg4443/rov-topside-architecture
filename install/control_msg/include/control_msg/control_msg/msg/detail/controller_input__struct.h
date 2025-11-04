// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from control_msg:msg/ControllerInput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "control_msg/msg/controller_input.h"


#ifndef CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__STRUCT_H_
#define CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/ControllerInput in the package control_msg.
typedef struct control_msg__msg__ControllerInput
{
  double left_x;
  double left_y;
  double right_x;
  double right_y;
  double left_trigger;
  double right_trigger;
  bool a;
  bool b;
  bool x;
  bool y;
  bool left_bumper;
  bool right_bumper;
  bool back;
  bool start;
  bool left_stick_pressed;
  bool right_stick_pressed;
  bool guide;
  bool dpad_up;
  bool dpad_down;
  bool dpad_left;
  bool dpad_right;
} control_msg__msg__ControllerInput;

// Struct for a sequence of control_msg__msg__ControllerInput.
typedef struct control_msg__msg__ControllerInput__Sequence
{
  control_msg__msg__ControllerInput * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} control_msg__msg__ControllerInput__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__STRUCT_H_
