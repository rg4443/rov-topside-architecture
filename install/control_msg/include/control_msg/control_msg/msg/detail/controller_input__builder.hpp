// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from control_msg:msg/ControllerInput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "control_msg/msg/controller_input.hpp"


#ifndef CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__BUILDER_HPP_
#define CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "control_msg/msg/detail/controller_input__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace control_msg
{

namespace msg
{

namespace builder
{

class Init_ControllerInput_dpad_right
{
public:
  explicit Init_ControllerInput_dpad_right(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  ::control_msg::msg::ControllerInput dpad_right(::control_msg::msg::ControllerInput::_dpad_right_type arg)
  {
    msg_.dpad_right = std::move(arg);
    return std::move(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_dpad_left
{
public:
  explicit Init_ControllerInput_dpad_left(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_dpad_right dpad_left(::control_msg::msg::ControllerInput::_dpad_left_type arg)
  {
    msg_.dpad_left = std::move(arg);
    return Init_ControllerInput_dpad_right(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_dpad_down
{
public:
  explicit Init_ControllerInput_dpad_down(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_dpad_left dpad_down(::control_msg::msg::ControllerInput::_dpad_down_type arg)
  {
    msg_.dpad_down = std::move(arg);
    return Init_ControllerInput_dpad_left(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_dpad_up
{
public:
  explicit Init_ControllerInput_dpad_up(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_dpad_down dpad_up(::control_msg::msg::ControllerInput::_dpad_up_type arg)
  {
    msg_.dpad_up = std::move(arg);
    return Init_ControllerInput_dpad_down(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_guide
{
public:
  explicit Init_ControllerInput_guide(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_dpad_up guide(::control_msg::msg::ControllerInput::_guide_type arg)
  {
    msg_.guide = std::move(arg);
    return Init_ControllerInput_dpad_up(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_right_stick_pressed
{
public:
  explicit Init_ControllerInput_right_stick_pressed(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_guide right_stick_pressed(::control_msg::msg::ControllerInput::_right_stick_pressed_type arg)
  {
    msg_.right_stick_pressed = std::move(arg);
    return Init_ControllerInput_guide(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_left_stick_pressed
{
public:
  explicit Init_ControllerInput_left_stick_pressed(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_right_stick_pressed left_stick_pressed(::control_msg::msg::ControllerInput::_left_stick_pressed_type arg)
  {
    msg_.left_stick_pressed = std::move(arg);
    return Init_ControllerInput_right_stick_pressed(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_start
{
public:
  explicit Init_ControllerInput_start(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_left_stick_pressed start(::control_msg::msg::ControllerInput::_start_type arg)
  {
    msg_.start = std::move(arg);
    return Init_ControllerInput_left_stick_pressed(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_back
{
public:
  explicit Init_ControllerInput_back(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_start back(::control_msg::msg::ControllerInput::_back_type arg)
  {
    msg_.back = std::move(arg);
    return Init_ControllerInput_start(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_right_bumper
{
public:
  explicit Init_ControllerInput_right_bumper(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_back right_bumper(::control_msg::msg::ControllerInput::_right_bumper_type arg)
  {
    msg_.right_bumper = std::move(arg);
    return Init_ControllerInput_back(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_left_bumper
{
public:
  explicit Init_ControllerInput_left_bumper(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_right_bumper left_bumper(::control_msg::msg::ControllerInput::_left_bumper_type arg)
  {
    msg_.left_bumper = std::move(arg);
    return Init_ControllerInput_right_bumper(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_y
{
public:
  explicit Init_ControllerInput_y(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_left_bumper y(::control_msg::msg::ControllerInput::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_ControllerInput_left_bumper(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_x
{
public:
  explicit Init_ControllerInput_x(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_y x(::control_msg::msg::ControllerInput::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_ControllerInput_y(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_b
{
public:
  explicit Init_ControllerInput_b(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_x b(::control_msg::msg::ControllerInput::_b_type arg)
  {
    msg_.b = std::move(arg);
    return Init_ControllerInput_x(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_a
{
public:
  explicit Init_ControllerInput_a(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_b a(::control_msg::msg::ControllerInput::_a_type arg)
  {
    msg_.a = std::move(arg);
    return Init_ControllerInput_b(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_right_trigger
{
public:
  explicit Init_ControllerInput_right_trigger(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_a right_trigger(::control_msg::msg::ControllerInput::_right_trigger_type arg)
  {
    msg_.right_trigger = std::move(arg);
    return Init_ControllerInput_a(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_left_trigger
{
public:
  explicit Init_ControllerInput_left_trigger(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_right_trigger left_trigger(::control_msg::msg::ControllerInput::_left_trigger_type arg)
  {
    msg_.left_trigger = std::move(arg);
    return Init_ControllerInput_right_trigger(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_right_y
{
public:
  explicit Init_ControllerInput_right_y(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_left_trigger right_y(::control_msg::msg::ControllerInput::_right_y_type arg)
  {
    msg_.right_y = std::move(arg);
    return Init_ControllerInput_left_trigger(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_right_x
{
public:
  explicit Init_ControllerInput_right_x(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_right_y right_x(::control_msg::msg::ControllerInput::_right_x_type arg)
  {
    msg_.right_x = std::move(arg);
    return Init_ControllerInput_right_y(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_left_y
{
public:
  explicit Init_ControllerInput_left_y(::control_msg::msg::ControllerInput & msg)
  : msg_(msg)
  {}
  Init_ControllerInput_right_x left_y(::control_msg::msg::ControllerInput::_left_y_type arg)
  {
    msg_.left_y = std::move(arg);
    return Init_ControllerInput_right_x(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

class Init_ControllerInput_left_x
{
public:
  Init_ControllerInput_left_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ControllerInput_left_y left_x(::control_msg::msg::ControllerInput::_left_x_type arg)
  {
    msg_.left_x = std::move(arg);
    return Init_ControllerInput_left_y(msg_);
  }

private:
  ::control_msg::msg::ControllerInput msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::control_msg::msg::ControllerInput>()
{
  return control_msg::msg::builder::Init_ControllerInput_left_x();
}

}  // namespace control_msg

#endif  // CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__BUILDER_HPP_
