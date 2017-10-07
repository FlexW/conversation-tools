# Conversation Tools

Command line tools for converting numbers.

## Currently Available Tools
```
dtoh - decimal to hexadecimal converter
htod - hexadecimal to decimal converter
```

## Build

The tools use the GNU GMP library. 
In case you have that library not installed and you are on Ubuntu enter:
```
sudo apt install libgmp-dev
```
To build the tools simply enter:
```
cd ~ 
git clone https://github.com/FlexW/conversation-tools.git
cd conversation-tools
make && sudo make install
```
