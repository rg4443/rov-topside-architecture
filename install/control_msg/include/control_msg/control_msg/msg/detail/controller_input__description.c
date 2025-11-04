// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from control_msg:msg/ControllerInput.idl
// generated code does not contain a copyright notice

#include "control_msg/msg/detail/controller_input__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_control_msg
const rosidl_type_hash_t *
control_msg__msg__ControllerInput__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x64, 0xae, 0xb8, 0xb5, 0x87, 0x7a, 0x7e, 0xc8,
      0x19, 0x89, 0x3e, 0x23, 0xea, 0x4d, 0x23, 0x8d,
      0x96, 0x5d, 0xcb, 0x13, 0x23, 0x3b, 0x4a, 0xdc,
      0x86, 0x71, 0x85, 0x9e, 0x5b, 0x61, 0x37, 0x01,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char control_msg__msg__ControllerInput__TYPE_NAME[] = "control_msg/msg/ControllerInput";

// Define type names, field names, and default values
static char control_msg__msg__ControllerInput__FIELD_NAME__left_x[] = "left_x";
static char control_msg__msg__ControllerInput__FIELD_NAME__left_y[] = "left_y";
static char control_msg__msg__ControllerInput__FIELD_NAME__right_x[] = "right_x";
static char control_msg__msg__ControllerInput__FIELD_NAME__right_y[] = "right_y";
static char control_msg__msg__ControllerInput__FIELD_NAME__left_trigger[] = "left_trigger";
static char control_msg__msg__ControllerInput__FIELD_NAME__right_trigger[] = "right_trigger";
static char control_msg__msg__ControllerInput__FIELD_NAME__a[] = "a";
static char control_msg__msg__ControllerInput__FIELD_NAME__b[] = "b";
static char control_msg__msg__ControllerInput__FIELD_NAME__x[] = "x";
static char control_msg__msg__ControllerInput__FIELD_NAME__y[] = "y";
static char control_msg__msg__ControllerInput__FIELD_NAME__left_bumper[] = "left_bumper";
static char control_msg__msg__ControllerInput__FIELD_NAME__right_bumper[] = "right_bumper";
static char control_msg__msg__ControllerInput__FIELD_NAME__back[] = "back";
static char control_msg__msg__ControllerInput__FIELD_NAME__start[] = "start";
static char control_msg__msg__ControllerInput__FIELD_NAME__left_stick_pressed[] = "left_stick_pressed";
static char control_msg__msg__ControllerInput__FIELD_NAME__right_stick_pressed[] = "right_stick_pressed";
static char control_msg__msg__ControllerInput__FIELD_NAME__guide[] = "guide";
static char control_msg__msg__ControllerInput__FIELD_NAME__dpad_up[] = "dpad_up";
static char control_msg__msg__ControllerInput__FIELD_NAME__dpad_down[] = "dpad_down";
static char control_msg__msg__ControllerInput__FIELD_NAME__dpad_left[] = "dpad_left";
static char control_msg__msg__ControllerInput__FIELD_NAME__dpad_right[] = "dpad_right";

static rosidl_runtime_c__type_description__Field control_msg__msg__ControllerInput__FIELDS[] = {
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__left_x, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__left_y, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__right_x, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__right_y, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__left_trigger, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__right_trigger, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__a, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__b, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__x, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__y, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__left_bumper, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__right_bumper, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__back, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__start, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__left_stick_pressed, 18, 18},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__right_stick_pressed, 19, 19},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__guide, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__dpad_up, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__dpad_down, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__dpad_left, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {control_msg__msg__ControllerInput__FIELD_NAME__dpad_right, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
control_msg__msg__ControllerInput__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {control_msg__msg__ControllerInput__TYPE_NAME, 31, 31},
      {control_msg__msg__ControllerInput__FIELDS, 21, 21},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float64 left_x\n"
  "float64 left_y\n"
  "float64 right_x\n"
  "float64 right_y\n"
  "float64 left_trigger\n"
  "float64 right_trigger\n"
  "bool a\n"
  "bool b\n"
  "bool x\n"
  "bool y\n"
  "bool left_bumper\n"
  "bool right_bumper\n"
  "bool back\n"
  "bool start\n"
  "bool left_stick_pressed\n"
  "bool right_stick_pressed\n"
  "bool guide\n"
  "bool dpad_up\n"
  "bool dpad_down\n"
  "bool dpad_left\n"
  "bool dpad_right";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
control_msg__msg__ControllerInput__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {control_msg__msg__ControllerInput__TYPE_NAME, 31, 31},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 308, 308},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
control_msg__msg__ControllerInput__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *control_msg__msg__ControllerInput__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
