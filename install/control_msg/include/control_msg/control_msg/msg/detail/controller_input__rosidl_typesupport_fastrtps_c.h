// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from control_msg:msg/ControllerInput.idl
// generated code does not contain a copyright notice
#ifndef CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "control_msg/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "control_msg/msg/detail/controller_input__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_control_msg
bool cdr_serialize_control_msg__msg__ControllerInput(
  const control_msg__msg__ControllerInput * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_control_msg
bool cdr_deserialize_control_msg__msg__ControllerInput(
  eprosima::fastcdr::Cdr &,
  control_msg__msg__ControllerInput * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_control_msg
size_t get_serialized_size_control_msg__msg__ControllerInput(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_control_msg
size_t max_serialized_size_control_msg__msg__ControllerInput(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_control_msg
bool cdr_serialize_key_control_msg__msg__ControllerInput(
  const control_msg__msg__ControllerInput * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_control_msg
size_t get_serialized_size_key_control_msg__msg__ControllerInput(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_control_msg
size_t max_serialized_size_key_control_msg__msg__ControllerInput(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_control_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, control_msg, msg, ControllerInput)();

#ifdef __cplusplus
}
#endif

#endif  // CONTROL_MSG__MSG__DETAIL__CONTROLLER_INPUT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
