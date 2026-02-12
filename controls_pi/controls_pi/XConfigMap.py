# Translates the necessary controller events and values into the throttles for the motors and servo angles for the servos.
# Meant to be used with Gamepad.py
# Using Motocol V1

from math import *
from time import perf_counter
from control_msg.msg import ControllerInput

# Some helpers
def clamp(val:float, minimum:float, maximum:float) -> float:
    if (val < minimum):
        return minimum
    elif (val > maximum):
        return maximum
    else:
        return val

class ROVMapping():
    # Mapping ordering: (axis inputs) 0:forward_axis, 1:strafe_axis, 2:yaw_axis, 3:up_axis
    #                   (bool inputs) 4:yaw_servo+, 5:yaw_servo-,
    #                                 6:pitch_servo+, 7:pitch_servo-,
    #                                 8:roll_servo+, 9:roll_servo-,
    #                                 10:claw_stepper+, 11:claw_stepper-
    def __init__(self, throttle_limit=1.0, mapping=["LEFT-Y", "LEFT-X", "RIGHT-X", "RIGHT-Y", 
                                                    "X", "B",
                                                    "A", "Y",
                                                    "RB", "LB",
                                                    "RT", "LT"]):
        self.control_ordering = ["forward_axis", "strafe_axis", "yaw_axis", "up_axis", "yaw_servo+", "yaw_servo-",
                                 "pitch_servo+", "pitch_servo-", "roll_servo+", "roll_servo-", "claw_stepper+", "claw_stepper-"]
        # Maps the controller axes to the control it actuates
        self.map_to_ordering = dict(zip(mapping, self.control_ordering))
        self.last_update = perf_counter()
        self.t_lim = throttle_limit
        self.servo_gain = 40.0 # int per second

        self.motor_vals = [128, 128, 128, 128, 128, 128]
        self.servo_vals = [128, 128, 128]
        self.stepper_vals = [1]
        self.data = self.motor_vals + self.servo_vals + self.stepper_vals

        self.ordering_to_val = dict(zip(self.control_ordering, [0.0 for i in range(len(mapping) + 1)]))

        self.yaw_on = False
        self.pitch_on = False
        self.roll_on = False

        self.yaw_servo_flt = 128.0
        self.pitch_servo_flt = 128.0
        self.roll_servo_flt = 128.0

        self.direction = 0.0
        self.magnitude = 0.0
        # print(self.map_to_ordering)
        # print(self.ordering_to_val)
        return

    # Callback for when a controller input is recieved
    def ProcessEventCallback(self, msg: ControllerInput):
        self.ordering_to_val["forward_axis"] = -msg.left_y
        self.ordering_to_val["strafe_axis"] = msg.left_x
        self.ordering_to_val["yaw_axis"] = msg.right_x
        self.ordering_to_val["up_axis"] = msg.right_y

        # Currently unused
        self.ordering_to_val["yaw_servo+"] = 0
        self.ordering_to_val["yaw_servo-"] = 0
        self.ordering_to_val["pitch_servo+"] = 0
        self.ordering_to_val["pitch_servo-"] = 0
        self.ordering_to_val["roll_servo+"] = 0
        self.ordering_to_val["roll_servo-"] = 0
        self.ordering_to_val["claw_stepper+"] = 0
        self.ordering_to_val["claw_stepper-"] = 0

        self.update()
        return

    # Update the motor vals
    def update(self):
        # Do the motors
        self.magnitude = sqrt((self.ordering_to_val["forward_axis"] ** 2) + (self.ordering_to_val["strafe_axis"] ** 2))
        self.direction = atan2(self.ordering_to_val["forward_axis"], self.ordering_to_val["strafe_axis"])
        # Front left
        angleMagnitude = self.magnitude*clamp(sqrt(2.0)*sin(self.direction+(0.75*pi)), -1.0, 1.0)
        self.motor_vals[0] = int(127.5+self.t_lim*127.5*clamp(self.ordering_to_val["yaw_axis"]+angleMagnitude, -1.0, 1.0))
        # Front right
        angleMagnitude = self.magnitude*clamp(sqrt(2.0)*sin(self.direction+(1.25*pi)), -1.0, 1.0)
        self.motor_vals[1] = int(127.5+self.t_lim*127.5*clamp(-self.ordering_to_val["yaw_axis"]+angleMagnitude, -1.0, 1.0))
        # Rear left
        angleMagnitude = self.magnitude*clamp(sqrt(2.0)*sin(self.direction+(1.25*pi)), -1.0, 1.0)
        self.motor_vals[2] = int(127.5+self.t_lim*127.5*clamp(self.ordering_to_val["yaw_axis"]+angleMagnitude, -1.0, 1.0))
        # Rear right
        angleMagnitude = self.magnitude*clamp(sqrt(2.0)*sin(self.direction+(0.75*pi)), -1.0, 1.0)
        self.motor_vals[3] = int(127.5+self.t_lim*127.5*clamp(-self.ordering_to_val["yaw_axis"]+angleMagnitude, -1.0, 1.0))
        
        self.motor_vals[4] = int(127.5+self.t_lim*127.5*self.ordering_to_val["up_axis"])
        self.motor_vals[5] = self.motor_vals[4]

        # ok now do the servos
        current_update = perf_counter()
        d_time = current_update - self.last_update
        d_yaw = d_time * self.servo_gain * (self.ordering_to_val["yaw_servo+"] - self.ordering_to_val["yaw_servo-"])
        d_pitch = d_time * self.servo_gain * (self.ordering_to_val["pitch_servo+"] - self.ordering_to_val["pitch_servo-"])
        d_roll = d_time * self.servo_gain * (self.ordering_to_val["roll_servo+"] - self.ordering_to_val["roll_servo-"])

        if not ((self.yaw_servo_flt + d_yaw >= 254.0) or (self.yaw_servo_flt + d_yaw <= 1.0)):
            self.yaw_servo_flt += d_yaw
        if not ((self.pitch_servo_flt + d_pitch >= 254.0) or (self.pitch_servo_flt + d_pitch <= 1.0)):
            self.pitch_servo_flt += d_pitch
        if not ((self.roll_servo_flt + d_roll >= 254.0) or (self.roll_servo_flt + d_roll <= 1.0)):
            self.roll_servo_flt += d_roll
        
        self.servo_vals[0] = int(self.yaw_servo_flt)
        self.servo_vals[1] = int(self.pitch_servo_flt)
        self.servo_vals[2] = int(self.roll_servo_flt)

        self.stepper_vals[0] = 1 + int((self.ordering_to_val["claw_stepper+"] + 1.0) / 2.0) - int((self.ordering_to_val["claw_stepper-"] + 1.0) / 2.0)
        # print(int((self.ordering_to_val["claw_stepper-"] + 1.0) / 2.0))
        self.data = self.motor_vals + self.servo_vals + self.stepper_vals
        self.last_update = current_update
        return