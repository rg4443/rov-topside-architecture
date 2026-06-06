from pymavlink import mavutil
import logging
import RPi.GPIO as GPIO

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - [%(levelname)s] - %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S'
)
logger = logging.getLogger("ClawController")

RC_CHANNEL = 7          # Guess, need to change to match BlueOS channel
PWM_THRESHOLD = 1500    # high, below is low

class ClawController:
    def __init__(self):
        self.pin = 18 # CHANGE IF ON DIFFERENT PIN
        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.pin, GPIO.OUT)
        GPIO.output(self.pin, 1)  # Start w/ replay off

        self.connection = None
        self.target_system = 1  # Doc says this is default, may be different.
        self.claw_open = False
        self.channel_was_high = False

    def connect(self):
        """Establish a connection to the BlueOS internal MAVLink router."""
        try:
            logger.info("Attempting to connect to BlueOS MAVLink stream (udpin:0.0.0.0:14550)...")
            self.connection = mavutil.mavlink_connection('udpin:0.0.0.0:14550') # Change udp port if different!

            logger.info("Waiting for vehicle heartbeat...")
            self.connection.wait_heartbeat(timeout=10)
            self.target_system = self.connection.target_system
            logger.info(f"Heartbeat received! Connected to Vehicle System ID: {self.target_system}")

        except Exception as e:
            logger.info(f"Connection failed: {e}")
            self.connection = None

    def run(self):
        """The main loop that listens for RC channel PWM input."""
        self.connect()

        if self.connection is None:
            logger.info("Could not connect to BlueOS. Exiting.")
            return

        logger.info(f"Listening for RC_CHANNELS, watching channel {RC_CHANNEL}...")

        try:
            while True:
                msg = self.connection.recv_match(type='RC_CHANNELS', blocking=True, timeout=5)

                # Fallback
                if msg is None:
                    logger.info("Connection lost, attempting reconnect...")
                    self.connect()
                    continue

                pwm = getattr(msg, f"chan{RC_CHANNEL}_raw", None)
                if pwm is None or pwm == 0:
                    continue

                channel_high = pwm >= PWM_THRESHOLD

                if channel_high and not self.channel_was_high:
                    self.claw_open = not self.claw_open

                    if self.claw_open:
                        logger.info(f"Channel {RC_CHANNEL} high ({pwm}): Claw Toggled OPEN.")
                        GPIO.output(self.pin, 0) # on
                    else:
                        logger.info(f"Channel {RC_CHANNEL} high ({pwm}): Claw Toggled CLOSED.")
                        GPIO.output(self.pin, 1) # off

                self.channel_was_high = channel_high

        except KeyboardInterrupt:
             logger.warning("Main loop interrupted by user.")
        except Exception as e:
            logger.error(f"Fatal error in main loop: {e}", exc_info=True)

    def cleanup(self):
        logger.info("Executing safe shutdown procedure...")
        GPIO.output(self.pin, 1)
        GPIO.cleanup()
        logger.info("Shutdown complete.")

if __name__ == '__main__':
    claw = ClawController()
    try:
        claw.run()
    finally:
        claw.cleanup()
