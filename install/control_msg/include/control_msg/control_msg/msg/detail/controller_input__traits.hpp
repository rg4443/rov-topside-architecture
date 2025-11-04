// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from control_msg:msg/ControllerInput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "control_msg/msg/controller_input.hpp"


#ifndef CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__TRAITS_HPP_
#define CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "control_msg/msg/detail/controller_input__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace control_msg
{

namespace msg
{

inline void to_flow_style_yaml(
  const ControllerInput & msg,
  std::ostream & out)
{
  out << "{";
  // member: left_x
  {
    out << "left_x: ";
    rosidl_generator_traits::value_to_yaml(msg.left_x, out);
    out << ", ";
  }

  // member: left_y
  {
    out << "left_y: ";
    rosidl_generator_traits::value_to_yaml(msg.left_y, out);
    out << ", ";
  }

  // member: right_x
  {
    out << "right_x: ";
    rosidl_generator_traits::value_to_yaml(msg.right_x, out);
    out << ", ";
  }

  // member: right_y
  {
    out << "right_y: ";
    rosidl_generator_traits::value_to_yaml(msg.right_y, out);
    out << ", ";
  }

  // member: left_trigger
  {
    out << "left_trigger: ";
    rosidl_generator_traits::value_to_yaml(msg.left_trigger, out);
    out << ", ";
  }

  // member: right_trigger
  {
    out << "right_trigger: ";
    rosidl_generator_traits::value_to_yaml(msg.right_trigger, out);
    out << ", ";
  }

  // member: a
  {
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << ", ";
  }

  // member: b
  {
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: left_bumper
  {
    out << "left_bumper: ";
    rosidl_generator_traits::value_to_yaml(msg.left_bumper, out);
    out << ", ";
  }

  // member: right_bumper
  {
    out << "right_bumper: ";
    rosidl_generator_traits::value_to_yaml(msg.right_bumper, out);
    out << ", ";
  }

  // member: back
  {
    out << "back: ";
    rosidl_generator_traits::value_to_yaml(msg.back, out);
    out << ", ";
  }

  // member: start
  {
    out << "start: ";
    rosidl_generator_traits::value_to_yaml(msg.start, out);
    out << ", ";
  }

  // member: left_stick_pressed
  {
    out << "left_stick_pressed: ";
    rosidl_generator_traits::value_to_yaml(msg.left_stick_pressed, out);
    out << ", ";
  }

  // member: right_stick_pressed
  {
    out << "right_stick_pressed: ";
    rosidl_generator_traits::value_to_yaml(msg.right_stick_pressed, out);
    out << ", ";
  }

  // member: guide
  {
    out << "guide: ";
    rosidl_generator_traits::value_to_yaml(msg.guide, out);
    out << ", ";
  }

  // member: dpad_up
  {
    out << "dpad_up: ";
    rosidl_generator_traits::value_to_yaml(msg.dpad_up, out);
    out << ", ";
  }

  // member: dpad_down
  {
    out << "dpad_down: ";
    rosidl_generator_traits::value_to_yaml(msg.dpad_down, out);
    out << ", ";
  }

  // member: dpad_left
  {
    out << "dpad_left: ";
    rosidl_generator_traits::value_to_yaml(msg.dpad_left, out);
    out << ", ";
  }

  // member: dpad_right
  {
    out << "dpad_right: ";
    rosidl_generator_traits::value_to_yaml(msg.dpad_right, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ControllerInput & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: left_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_x: ";
    rosidl_generator_traits::value_to_yaml(msg.left_x, out);
    out << "\n";
  }

  // member: left_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_y: ";
    rosidl_generator_traits::value_to_yaml(msg.left_y, out);
    out << "\n";
  }

  // member: right_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_x: ";
    rosidl_generator_traits::value_to_yaml(msg.right_x, out);
    out << "\n";
  }

  // member: right_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_y: ";
    rosidl_generator_traits::value_to_yaml(msg.right_y, out);
    out << "\n";
  }

  // member: left_trigger
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_trigger: ";
    rosidl_generator_traits::value_to_yaml(msg.left_trigger, out);
    out << "\n";
  }

  // member: right_trigger
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_trigger: ";
    rosidl_generator_traits::value_to_yaml(msg.right_trigger, out);
    out << "\n";
  }

  // member: a
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << "\n";
  }

  // member: b
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: left_bumper
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_bumper: ";
    rosidl_generator_traits::value_to_yaml(msg.left_bumper, out);
    out << "\n";
  }

  // member: right_bumper
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_bumper: ";
    rosidl_generator_traits::value_to_yaml(msg.right_bumper, out);
    out << "\n";
  }

  // member: back
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "back: ";
    rosidl_generator_traits::value_to_yaml(msg.back, out);
    out << "\n";
  }

  // member: start
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "start: ";
    rosidl_generator_traits::value_to_yaml(msg.start, out);
    out << "\n";
  }

  // member: left_stick_pressed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_stick_pressed: ";
    rosidl_generator_traits::value_to_yaml(msg.left_stick_pressed, out);
    out << "\n";
  }

  // member: right_stick_pressed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_stick_pressed: ";
    rosidl_generator_traits::value_to_yaml(msg.right_stick_pressed, out);
    out << "\n";
  }

  // member: guide
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "guide: ";
    rosidl_generator_traits::value_to_yaml(msg.guide, out);
    out << "\n";
  }

  // member: dpad_up
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dpad_up: ";
    rosidl_generator_traits::value_to_yaml(msg.dpad_up, out);
    out << "\n";
  }

  // member: dpad_down
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dpad_down: ";
    rosidl_generator_traits::value_to_yaml(msg.dpad_down, out);
    out << "\n";
  }

  // member: dpad_left
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dpad_left: ";
    rosidl_generator_traits::value_to_yaml(msg.dpad_left, out);
    out << "\n";
  }

  // member: dpad_right
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dpad_right: ";
    rosidl_generator_traits::value_to_yaml(msg.dpad_right, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ControllerInput & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace control_msg

namespace rosidl_generator_traits
{

[[deprecated("use control_msg::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const control_msg::msg::ControllerInput & msg,
  std::ostream & out, size_t indentation = 0)
{
  control_msg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use control_msg::msg::to_yaml() instead")]]
inline std::string to_yaml(const control_msg::msg::ControllerInput & msg)
{
  return control_msg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<control_msg::msg::ControllerInput>()
{
  return "control_msg::msg::ControllerInput";
}

template<>
inline const char * name<control_msg::msg::ControllerInput>()
{
  return "control_msg/msg/ControllerInput";
}

template<>
struct has_fixed_size<control_msg::msg::ControllerInput>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<control_msg::msg::ControllerInput>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<control_msg::msg::ControllerInput>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__TRAITS_HPP_
