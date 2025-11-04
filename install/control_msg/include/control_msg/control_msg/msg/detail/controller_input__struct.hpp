// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from control_msg:msg/ControllerInput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "control_msg/msg/controller_input.hpp"


#ifndef CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__STRUCT_HPP_
#define CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__control_msg__msg__ControllerInput __attribute__((deprecated))
#else
# define DEPRECATED__control_msg__msg__ControllerInput __declspec(deprecated)
#endif

namespace control_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ControllerInput_
{
  using Type = ControllerInput_<ContainerAllocator>;

  explicit ControllerInput_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->left_x = 0.0;
      this->left_y = 0.0;
      this->right_x = 0.0;
      this->right_y = 0.0;
      this->left_trigger = 0.0;
      this->right_trigger = 0.0;
      this->a = false;
      this->b = false;
      this->x = false;
      this->y = false;
      this->left_bumper = false;
      this->right_bumper = false;
      this->back = false;
      this->start = false;
      this->left_stick_pressed = false;
      this->right_stick_pressed = false;
      this->guide = false;
      this->dpad_up = false;
      this->dpad_down = false;
      this->dpad_left = false;
      this->dpad_right = false;
    }
  }

  explicit ControllerInput_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->left_x = 0.0;
      this->left_y = 0.0;
      this->right_x = 0.0;
      this->right_y = 0.0;
      this->left_trigger = 0.0;
      this->right_trigger = 0.0;
      this->a = false;
      this->b = false;
      this->x = false;
      this->y = false;
      this->left_bumper = false;
      this->right_bumper = false;
      this->back = false;
      this->start = false;
      this->left_stick_pressed = false;
      this->right_stick_pressed = false;
      this->guide = false;
      this->dpad_up = false;
      this->dpad_down = false;
      this->dpad_left = false;
      this->dpad_right = false;
    }
  }

  // field types and members
  using _left_x_type =
    double;
  _left_x_type left_x;
  using _left_y_type =
    double;
  _left_y_type left_y;
  using _right_x_type =
    double;
  _right_x_type right_x;
  using _right_y_type =
    double;
  _right_y_type right_y;
  using _left_trigger_type =
    double;
  _left_trigger_type left_trigger;
  using _right_trigger_type =
    double;
  _right_trigger_type right_trigger;
  using _a_type =
    bool;
  _a_type a;
  using _b_type =
    bool;
  _b_type b;
  using _x_type =
    bool;
  _x_type x;
  using _y_type =
    bool;
  _y_type y;
  using _left_bumper_type =
    bool;
  _left_bumper_type left_bumper;
  using _right_bumper_type =
    bool;
  _right_bumper_type right_bumper;
  using _back_type =
    bool;
  _back_type back;
  using _start_type =
    bool;
  _start_type start;
  using _left_stick_pressed_type =
    bool;
  _left_stick_pressed_type left_stick_pressed;
  using _right_stick_pressed_type =
    bool;
  _right_stick_pressed_type right_stick_pressed;
  using _guide_type =
    bool;
  _guide_type guide;
  using _dpad_up_type =
    bool;
  _dpad_up_type dpad_up;
  using _dpad_down_type =
    bool;
  _dpad_down_type dpad_down;
  using _dpad_left_type =
    bool;
  _dpad_left_type dpad_left;
  using _dpad_right_type =
    bool;
  _dpad_right_type dpad_right;

  // setters for named parameter idiom
  Type & set__left_x(
    const double & _arg)
  {
    this->left_x = _arg;
    return *this;
  }
  Type & set__left_y(
    const double & _arg)
  {
    this->left_y = _arg;
    return *this;
  }
  Type & set__right_x(
    const double & _arg)
  {
    this->right_x = _arg;
    return *this;
  }
  Type & set__right_y(
    const double & _arg)
  {
    this->right_y = _arg;
    return *this;
  }
  Type & set__left_trigger(
    const double & _arg)
  {
    this->left_trigger = _arg;
    return *this;
  }
  Type & set__right_trigger(
    const double & _arg)
  {
    this->right_trigger = _arg;
    return *this;
  }
  Type & set__a(
    const bool & _arg)
  {
    this->a = _arg;
    return *this;
  }
  Type & set__b(
    const bool & _arg)
  {
    this->b = _arg;
    return *this;
  }
  Type & set__x(
    const bool & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const bool & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__left_bumper(
    const bool & _arg)
  {
    this->left_bumper = _arg;
    return *this;
  }
  Type & set__right_bumper(
    const bool & _arg)
  {
    this->right_bumper = _arg;
    return *this;
  }
  Type & set__back(
    const bool & _arg)
  {
    this->back = _arg;
    return *this;
  }
  Type & set__start(
    const bool & _arg)
  {
    this->start = _arg;
    return *this;
  }
  Type & set__left_stick_pressed(
    const bool & _arg)
  {
    this->left_stick_pressed = _arg;
    return *this;
  }
  Type & set__right_stick_pressed(
    const bool & _arg)
  {
    this->right_stick_pressed = _arg;
    return *this;
  }
  Type & set__guide(
    const bool & _arg)
  {
    this->guide = _arg;
    return *this;
  }
  Type & set__dpad_up(
    const bool & _arg)
  {
    this->dpad_up = _arg;
    return *this;
  }
  Type & set__dpad_down(
    const bool & _arg)
  {
    this->dpad_down = _arg;
    return *this;
  }
  Type & set__dpad_left(
    const bool & _arg)
  {
    this->dpad_left = _arg;
    return *this;
  }
  Type & set__dpad_right(
    const bool & _arg)
  {
    this->dpad_right = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    control_msg::msg::ControllerInput_<ContainerAllocator> *;
  using ConstRawPtr =
    const control_msg::msg::ControllerInput_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<control_msg::msg::ControllerInput_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<control_msg::msg::ControllerInput_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      control_msg::msg::ControllerInput_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<control_msg::msg::ControllerInput_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      control_msg::msg::ControllerInput_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<control_msg::msg::ControllerInput_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<control_msg::msg::ControllerInput_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<control_msg::msg::ControllerInput_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__control_msg__msg__ControllerInput
    std::shared_ptr<control_msg::msg::ControllerInput_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__control_msg__msg__ControllerInput
    std::shared_ptr<control_msg::msg::ControllerInput_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ControllerInput_ & other) const
  {
    if (this->left_x != other.left_x) {
      return false;
    }
    if (this->left_y != other.left_y) {
      return false;
    }
    if (this->right_x != other.right_x) {
      return false;
    }
    if (this->right_y != other.right_y) {
      return false;
    }
    if (this->left_trigger != other.left_trigger) {
      return false;
    }
    if (this->right_trigger != other.right_trigger) {
      return false;
    }
    if (this->a != other.a) {
      return false;
    }
    if (this->b != other.b) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->left_bumper != other.left_bumper) {
      return false;
    }
    if (this->right_bumper != other.right_bumper) {
      return false;
    }
    if (this->back != other.back) {
      return false;
    }
    if (this->start != other.start) {
      return false;
    }
    if (this->left_stick_pressed != other.left_stick_pressed) {
      return false;
    }
    if (this->right_stick_pressed != other.right_stick_pressed) {
      return false;
    }
    if (this->guide != other.guide) {
      return false;
    }
    if (this->dpad_up != other.dpad_up) {
      return false;
    }
    if (this->dpad_down != other.dpad_down) {
      return false;
    }
    if (this->dpad_left != other.dpad_left) {
      return false;
    }
    if (this->dpad_right != other.dpad_right) {
      return false;
    }
    return true;
  }
  bool operator!=(const ControllerInput_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ControllerInput_

// alias to use template instance with default allocator
using ControllerInput =
  control_msg::msg::ControllerInput_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace control_msg

#endif  // CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__STRUCT_HPP_
