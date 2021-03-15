# ardupet

# arduino-cli
https://arduino.github.io/arduino-cli/latest/installation/

# compile sketch
arduino-cli compile --fqbn arduino:avr:leonardo ardupet

# uploading to arduino
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:leonardo ardupet
