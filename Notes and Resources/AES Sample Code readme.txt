Please note: in order to compile and run this code, you will need to install libssl-dev:

Installation on Ubuntu:

sudo apt-get update -y
sudo apt-get install -y libssl-dev

You can also connect to the Titan Server where the libssl-dev was already installed: To connect: ssh youusername@ecs.fullerton.edu

To compile: g++ myaes.cpp -o myaes -lcrypto

To run: ./myaes