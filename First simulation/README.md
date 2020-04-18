# First simulation
## First movements and avoiding obstacles 

In this simulation we will make the drone go to a desired position. The drone will detect obstacles and depending on the distance it will block the movement, it will unblock the movement or it will go to the opposite direction to evit an obstacle. 


## Commands

In a terminal:

```
roslaunch px4 final_advanbird.launch
```

In a second terminal:

```
cd 'your_path'/listener/build
make 
./listener
```

In a third terminal:

```
roslaunch px4 final_pythonscripts.launch
```


## Commands file by file

In terminal 1:

```
roslaunch px4 posix_sitl.launch
```

In terminal 2:

```
roslaunch mavros px4.launch fcu_url:="udp://:14540@127.0.0.1:14557"
```

In terminal 3:

```
cd 'your_path'/listener/build
make 
./listener
```

In terminal 4:

```
cd 'your_path'/catkin_ws/src/Firmware
python px4_mavros_run.py
```

In terminal 5:

```
cd 'your_path'/catkin_ws/src/Firmware
python commander.py
```





