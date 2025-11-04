// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from control_msg:msg/ControllerInput.idl
// generated code does not contain a copyright notice
#include "control_msg/msg/detail/controller_input__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
control_msg__msg__ControllerInput__init(control_msg__msg__ControllerInput * msg)
{
  if (!msg) {
    return false;
  }
  // left_x
  // left_y
  // right_x
  // right_y
  // left_trigger
  // right_trigger
  // a
  // b
  // x
  // y
  // left_bumper
  // right_bumper
  // back
  // start
  // left_stick_pressed
  // right_stick_pressed
  // guide
  // dpad_up
  // dpad_down
  // dpad_left
  // dpad_right
  return true;
}

void
control_msg__msg__ControllerInput__fini(control_msg__msg__ControllerInput * msg)
{
  if (!msg) {
    return;
  }
  // left_x
  // left_y
  // right_x
  // right_y
  // left_trigger
  // right_trigger
  // a
  // b
  // x
  // y
  // left_bumper
  // right_bumper
  // back
  // start
  // left_stick_pressed
  // right_stick_pressed
  // guide
  // dpad_up
  // dpad_down
  // dpad_left
  // dpad_right
}

bool
control_msg__msg__ControllerInput__are_equal(const control_msg__msg__ControllerInput * lhs, const control_msg__msg__ControllerInput * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // left_x
  if (lhs->left_x != rhs->left_x) {
    return false;
  }
  // left_y
  if (lhs->left_y != rhs->left_y) {
    return false;
  }
  // right_x
  if (lhs->right_x != rhs->right_x) {
    return false;
  }
  // right_y
  if (lhs->right_y != rhs->right_y) {
    return false;
  }
  // left_trigger
  if (lhs->left_trigger != rhs->left_trigger) {
    return false;
  }
  // right_trigger
  if (lhs->right_trigger != rhs->right_trigger) {
    return false;
  }
  // a
  if (lhs->a != rhs->a) {
    return false;
  }
  // b
  if (lhs->b != rhs->b) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // left_bumper
  if (lhs->left_bumper != rhs->left_bumper) {
    return false;
  }
  // right_bumper
  if (lhs->right_bumper != rhs->right_bumper) {
    return false;
  }
  // back
  if (lhs->back != rhs->back) {
    return false;
  }
  // start
  if (lhs->start != rhs->start) {
    return false;
  }
  // left_stick_pressed
  if (lhs->left_stick_pressed != rhs->left_stick_pressed) {
    return false;
  }
  // right_stick_pressed
  if (lhs->right_stick_pressed != rhs->right_stick_pressed) {
    return false;
  }
  // guide
  if (lhs->guide != rhs->guide) {
    return false;
  }
  // dpad_up
  if (lhs->dpad_up != rhs->dpad_up) {
    return false;
  }
  // dpad_down
  if (lhs->dpad_down != rhs->dpad_down) {
    return false;
  }
  // dpad_left
  if (lhs->dpad_left != rhs->dpad_left) {
    return false;
  }
  // dpad_right
  if (lhs->dpad_right != rhs->dpad_right) {
    return false;
  }
  return true;
}

bool
control_msg__msg__ControllerInput__copy(
  const control_msg__msg__ControllerInput * input,
  control_msg__msg__ControllerInput * output)
{
  if (!input || !output) {
    return false;
  }
  // left_x
  output->left_x = input->left_x;
  // left_y
  output->left_y = input->left_y;
  // right_x
  output->right_x = input->right_x;
  // right_y
  output->right_y = input->right_y;
  // left_trigger
  output->left_trigger = input->left_trigger;
  // right_trigger
  output->right_trigger = input->right_trigger;
  // a
  output->a = input->a;
  // b
  output->b = input->b;
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // left_bumper
  output->left_bumper = input->left_bumper;
  // right_bumper
  output->right_bumper = input->right_bumper;
  // back
  output->back = input->back;
  // start
  output->start = input->start;
  // left_stick_pressed
  output->left_stick_pressed = input->left_stick_pressed;
  // right_stick_pressed
  output->right_stick_pressed = input->right_stick_pressed;
  // guide
  output->guide = input->guide;
  // dpad_up
  output->dpad_up = input->dpad_up;
  // dpad_down
  output->dpad_down = input->dpad_down;
  // dpad_left
  output->dpad_left = input->dpad_left;
  // dpad_right
  output->dpad_right = input->dpad_right;
  return true;
}

control_msg__msg__ControllerInput *
control_msg__msg__ControllerInput__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  control_msg__msg__ControllerInput * msg = (control_msg__msg__ControllerInput *)allocator.allocate(sizeof(control_msg__msg__ControllerInput), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(control_msg__msg__ControllerInput));
  bool success = control_msg__msg__ControllerInput__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
control_msg__msg__ControllerInput__destroy(control_msg__msg__ControllerInput * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    control_msg__msg__ControllerInput__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
control_msg__msg__ControllerInput__Sequence__init(control_msg__msg__ControllerInput__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  control_msg__msg__ControllerInput * data = NULL;

  if (size) {
    data = (control_msg__msg__ControllerInput *)allocator.zero_allocate(size, sizeof(control_msg__msg__ControllerInput), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = control_msg__msg__ControllerInput__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        control_msg__msg__ControllerInput__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
control_msg__msg__ControllerInput__Sequence__fini(control_msg__msg__ControllerInput__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      control_msg__msg__ControllerInput__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

control_msg__msg__ControllerInput__Sequence *
control_msg__msg__ControllerInput__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  control_msg__msg__ControllerInput__Sequence * array = (control_msg__msg__ControllerInput__Sequence *)allocator.allocate(sizeof(control_msg__msg__ControllerInput__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = control_msg__msg__ControllerInput__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
control_msg__msg__ControllerInput__Sequence__destroy(control_msg__msg__ControllerInput__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    control_msg__msg__ControllerInput__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
control_msg__msg__ControllerInput__Sequence__are_equal(const control_msg__msg__ControllerInput__Sequence * lhs, const control_msg__msg__ControllerInput__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!control_msg__msg__ControllerInput__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
control_msg__msg__ControllerInput__Sequence__copy(
  const control_msg__msg__ControllerInput__Sequence * input,
  control_msg__msg__ControllerInput__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(control_msg__msg__ControllerInput);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    control_msg__msg__ControllerInput * data =
      (control_msg__msg__ControllerInput *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!control_msg__msg__ControllerInput__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          control_msg__msg__ControllerInput__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!control_msg__msg__ControllerInput__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
