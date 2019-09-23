# JADCC
Automatically detects when a blower gate is opened and turns on the collector motor
https://hackaday.io/project/167479-just-another-dust-collector-controller

### :warning: WARNING BEFORE PROCEEDING :warning: 
**YOU CAN BE ELECTROCUTED OR CAUSE BODILY HARM TO YOURSELF OR SOMEONE ELSE IF YOU DON'T KNOW WHAT YOU ARE DOING!**

Read the Safety Wiki page for more information [here](https://github.com/jchambers2012/JADCC/wiki/Safety-Information)

A dust collection system is an air quality improvement system used in industrial, commercial, and home production shops to improve breathable air quality and safety by removing particulate matter from the air and environment. Dust collection systems work on the basic formula of capture, convey and collect. See more here: [Wikipedia](https://en.wikipedia.org/wiki/Dust_collection_system)

This system will be able to monitor 15+ switches that will be installed on the dust air flow control door or via a non-invasive current sensor. When the door is in the open position or when the tool is powered on, the system will sent a IR signal or relay loop will turn on to tell Dust Collector controller to turn on the system. When all doors are closed or the stop button is pressed; the system will send a stop signal to the controller.

Project Goals:
* Simple, should be able to be changed/rewired/managed by the shop’s owner
* Customizable, each sensor should be able to start, stop and/or perform other functions. System will include 2 special function relays or one if 1 relay is used to control a motor contactor
* Friendly, should be able to let the end user know what is going on and what sensor(s) is triggering the start or stop condition
* Expandable, existing controller PCB can be chained to increase the number of inputs that can be monitored
* Reusable, controller board can be used to replace other systems (IE my town house's outdated security system)
