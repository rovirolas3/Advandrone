# Second simulation
## First movements autonomosly 

In this simulation we will make the drone to go to a random position where there is no obstacle detected. So the drone will choose one of the four directions that the movement it is not blocked.

The code is very similar to the first simulation. You can see the changes in the **commander.py** and in the **px4_mavros_run.py** files.

## Paths that are mandatory to be changed

In the file listener/listener.cc:

* char pathBack[] = "/'your\_path'/catkin_ws/src/Firmware/avoidobstacleback.py"; 
* char pathFront[] = "/'your\_path'/catkin_ws/src/Firmware/avoidobstaclefront.py";
* char pathRight[] = "/'your\_path'/catkin_ws/src/Firmware/avoidobstacleright.py";
* char pathLeft[] = "/'your\_path'/catkin_ws/src/Firmware/avoidobstacleleft.py";
* char pathUp[] = "/'your\_path'/catkin_ws/src/Firmware/avoidobstacleup.py";
* char pathDown[] = "/'your\_path'/catkin_ws/src/Firmware/avoidobstacledown.py";

In the file catkin_ws/src/Firmware/avoidobstacleback.py:

*     yamlpath = "/'your\_path/catkin_ws/src/Firmware/data.yaml"

In the file catkin_ws/src/Firmware/avoidobstacledown.py:

*     yamlpath = "/'your\_path/catkin_ws/src/Firmware/data.yaml"

In the file catkin_ws/src/Firmware/avoidobstaclefront.py:

*     yamlpath = "/'your\_path/catkin_ws/src/Firmware/data.yaml"

In the file catkin_ws/src/Firmware/avoidobstacleleft.py:

*     yamlpath = "/'your\_path/catkin_ws/src/Firmware/data.yaml"

In the file catkin_ws/src/Firmware/avoidobstacleright.py:

*     yamlpath = "/'your\_path/catkin_ws/src/Firmware/data.yaml"

In the file catkin_ws/src/Firmware/avoidobstacleup.py:

*     yamlpath = "/'your\_path/catkin_ws/src/Firmware/data.yaml"

In the file commander.py:

*     yamlpath = "/'your\_path/catkin_ws/src/Firmware/data.yaml"

In the file px4\_mavros_run.py:

*     yamlpath = "/'your\_path/catkin_ws/src/Firmware/data.yaml" 

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





