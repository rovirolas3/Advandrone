#!/usr/bin/env python
import rospy
from mavros_msgs.msg import GlobalPositionTarget, State
from mavros_msgs.srv import CommandBool, CommandTOL, SetMode
from geometry_msgs.msg import PoseStamped, Twist
from sensor_msgs.msg import Imu, NavSatFix
from std_msgs.msg import Float32, String
from pyquaternion import Quaternion
import time
import math
import yaml
import sys





class ObstacleBackAvoider:
    def __init__(self):
        with open('/home/miguel/catkin_ws/src/Firmware/data.yaml') as f:
    
           data = yaml.load(f, Loader=yaml.FullLoader)
           for key, value in data.items():
              if key == "rate_value":
                 rate_value = value

        rospy.init_node("obstacleavoider_back_node") # We initialize the node with the name: obstacleavoider_node
        rate = rospy.Rate(rate_value) # Rate of 20 Hz

        self.avoidbackobstacle = rospy.Publisher('gi/avoidobstacle/back', Float32, queue_size=10) # Custom publisher of avoidobstacle
        self.avoidbackobstacle_return = rospy.Publisher('gi/avoidobstacle/back_return', Float32, queue_size=10) # Custom publisher of avoidobstacle

    
    # Moves X meters to the left to evit back obstacle
    def avoid_back_obstacle(self, distance_obst_avoid): # Function called to move the drone X distance to avoid the obstacle
        with open('/home/miguel/catkin_ws/src/Firmware/data.yaml') as f:
    
           data = yaml.load(f, Loader=yaml.FullLoader)
           for key, value in data.items():
              if key == "distance_obst_avoid":
                 distance_obst_avoid = value


        self.avoidbackobstacle.publish(distance_obst_avoid) # It publishes the float distance to move



    # Moves X meters to the back to remove the distance moved previously
    def avoid_back_obstacle_return(self, distance_obst_avoid): # Function called to move the drone X distance to avoid the obstacle
        with open('/home/miguel/catkin_ws/src/Firmware/data.yaml') as f:
    
           data = yaml.load(f, Loader=yaml.FullLoader)
           for key, value in data.items():
              if key == "distance_obst_avoid":
                 distance_obst_avoid = value


        self.avoidbackobstacle_return.publish(distance_obst_avoid) # It publishes the float distance to move



if __name__ == "__main__": # From here to the end we call all the functions in our order desired
    with open('/home/miguel/catkin_ws/src/Firmware/data.yaml') as f:
   
        data = yaml.load(f, Loader=yaml.FullLoader)
        for key, value in data.items():
            if key == "distance_obst_avoid":
                distance_obst_avoid = value
    #print(distance_obst_avoid)    

    avo = ObstacleBackAvoider()


    if sys.argv[1] == "BACK":
        time.sleep(1)
        avo.avoid_back_obstacle_return(distance_obst_avoid)
        time.sleep(1)
    else:
        time.sleep(1)
        avo.avoid_back_obstacle(distance_obst_avoid)
        time.sleep(1)


