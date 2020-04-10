/*
 * Copyright (C) 2012 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo_client.hh>

#include <iostream>

#include <fstream>

#include <stdio.h>
#include <python2.7/Python.h>

#include <stdlib.h>

using namespace std;

// Global values with the range of each sensor
float range_back {};
float range_right {};
float range_left {};
float range_front {};
float range_down {};
float range_up {};

// Global values with the times the drone has moved from the desired position X meters
float range_back_times = 0;
float range_right_times = 0;
float range_left_times = 0;
float range_front_times = 0;
float range_down_times = 0;
float range_up_times = 0;

// Number of times left to skip the sensor value
float range_back_skip_counter = 0;
float range_right_skip_counter = 0;
float range_left_skip_counter = 0;
float range_front_skip_counter = 0;
float range_down_skip_counter = 0;
float range_up_skip_counter = 0;

// Number of times we don't catch the value of the sensor
float global_skip_counter = 80;


// Max ranges

float range_min = 1;
float range_max = 2.7;
float range_min_down = 0.3;
float range_max_down = 2.2;
 
/////////////////////////////////////////////////
// Function is called everytime a message is received.
void cb_back(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_back = _msg->sonar().range();
  std::cout <<"DISTANCE BACK: "<<range_back<<"\n";

  if (range_back_skip_counter > 0) { 

    range_back_skip_counter = range_back_skip_counter - 1; 

  } else if (range_back >= range_max) {

       system("python /home/miguel/catkin_ws/src/Firmware/avoidobstacleback.py BACK &");
       range_back_skip_counter = global_skip_counter;
       std::cout <<"Posibility to go back\n";

  } else if (range_back <= range_min) {

       system("python /home/miguel/catkin_ws/src/Firmware/avoidobstacleback.py EVIT &");
       range_back_skip_counter = global_skip_counter;
       std::cout <<"Detected obstacle in the back\n";  
   
  }
  //std::cout <<"range_back_times: "<< range_right_times<<"\n";
  //std::cout <<"range_back_skip_counter: "<< range_right_skip_counter<<"\n";

}


void cb_left(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_left = _msg->sonar().range();
  std::cout <<"DISTANCE LEFT: "<<range_left<<"\n";


  if (range_left_skip_counter > 0) { 

    range_left_skip_counter = range_left_skip_counter - 1; 

  } else if (range_left >= range_max) {

       system("python /home/miguel/catkin_ws/src/Firmware/avoidobstacleleft.py BACK &");
       range_left_skip_counter = global_skip_counter;
       std::cout <<"Posibility to go left\n";

  } else if (range_left <= range_min) {

       system("python /home/miguel/catkin_ws/src/Firmware/avoidobstacleleft.py EVIT &");
       range_left_skip_counter = global_skip_counter;
       std::cout <<"Detected obstacle in the left\n";   
   
  }
  //std::cout <<"range_left_times: "<< range_right_times<<"\n";
  //std::cout <<"range_left_skip_counter: "<< range_right_skip_counter<<"\n";
  
}


void cb_right(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_right = _msg->sonar().range();
  std::cout <<"DISTANCE RIGHT: "<< range_right<<"\n";
 
  if (range_right_skip_counter > 0) { 

    range_right_skip_counter = range_right_skip_counter - 1; 

  } else if (range_right >= range_max) {

       system("python /home/miguel/catkin_ws/src/Firmware/avoidobstacleright.py BACK &");
       range_right_skip_counter = global_skip_counter;
       std::cout <<"Posibility to go right\n";

  } else if (range_right <= range_min) {

       system("python /home/miguel/catkin_ws/src/Firmware/avoidobstacleright.py EVIT &");
       range_right_skip_counter = global_skip_counter;
       std::cout <<"Detected obstacle in the right\n";  
   
  }
  //std::cout <<"range_right_times: "<< range_right_times<<"\n";
  //std::cout <<"range_right_skip_counter: "<< range_right_skip_counter<<"\n";
}


void cb_front(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_front = _msg->sonar().range();
  std::cout <<"DISTANCE FRONT: "<< range_front<<"\n";

  if (range_front_skip_counter > 0) { 

    range_front_skip_counter = range_front_skip_counter - 1; 

  } else if (range_front >= range_max) {

       system("python /home/miguel/catkin_ws/src/Firmware/avoidobstaclefront.py BACK &");
       range_front_skip_counter = global_skip_counter;
       std::cout <<"Posibility to go front\n";

  } else if (range_front <= range_min) {

       system("python /home/miguel/catkin_ws/src/Firmware/avoidobstaclefront.py EVIT &");
       range_front_skip_counter = global_skip_counter;
       std::cout <<"Detected obstacle in the front\n";  
   
  }
  //std::cout <<"range_right_times: "<< range_right_times<<"\n";
  //std::cout <<"range_right_skip_counter: "<< range_right_skip_counter<<"\n";


}


void cb_down(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_down = _msg->sonar().range();
  std::cout <<"DISTANCE DOWN: "<< range_down<<"\n";

  if (range_down_skip_counter > 0) { 

    range_down_skip_counter = range_down_skip_counter - 1; 

  } else if (range_down >= range_max_down) {

       system("python /home/miguel/catkin_ws/src/Firmware/avoidobstacledown.py BACK &");
       range_down_skip_counter = global_skip_counter;
       std::cout <<"Posibility to go down\n";

  } else if (range_down <= range_min_down) {

       system("python /home/miguel/catkin_ws/src/Firmware/avoidobstacledown.py EVIT &");
       range_down_skip_counter = global_skip_counter; 
       std::cout <<"Detected obstacle in the down\n"; 
   
  }

  //std::cout <<"range_right_times: "<< range_right_times<<"\n";
  //std::cout <<"range_right_skip_counter: "<< range_right_skip_counter<<"\n";

}


void cb_up(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_up = _msg->sonar().range();
  std::cout <<"DISTANCE UP: "<< range_up<<"\n";

  if (range_up_skip_counter > 0) { 

    range_up_skip_counter = range_up_skip_counter - 1; 

  } else if (range_up >= range_max) {

       system("python /home/miguel/catkin_ws/src/Firmware/avoidobstacleup.py BACK &");
       range_up_skip_counter = global_skip_counter;
       std::cout <<"Posibility to go up\n";

  } else if (range_up <= range_min) {

       system("python /home/miguel/catkin_ws/src/Firmware/avoidobstacleup.py EVIT &");
       range_up_skip_counter = global_skip_counter;
       std::cout <<"Detected obstacle in the up\n";  
   
  }
  //std::cout <<"range_right_times: "<< range_right_times<<"\n";
  //std::cout <<"range_right_skip_counter: "<< range_right_skip_counter<<"\n";

}










/////////////////////////////////////////////////
int main(int _argc, char **_argv)
{
  // Load gazebo
  gazebo::client::setup(_argc, _argv);

  // Create our node for communication
  gazebo::transport::NodePtr node(new gazebo::transport::Node());
  node->Init();


  // Listen to Gazebo world_stats topic
  gazebo::transport::SubscriberPtr sub_back = node->Subscribe("~/iris/sonar_back/link/sonar_back/sonar", cb_back);
  gazebo::transport::SubscriberPtr sub_left = node->Subscribe("~/iris/sonar_left/link/sonar_left/sonar", cb_left);
  gazebo::transport::SubscriberPtr sub_right = node->Subscribe("~/iris/sonar_right/link/sonar_right/sonar", cb_right);
  gazebo::transport::SubscriberPtr sub_front = node->Subscribe("~/iris/sonar_front/link/sonar_front/sonar", cb_front);
  gazebo::transport::SubscriberPtr sub_down = node->Subscribe("~/iris/sonar_down/link/sonar_down/sonar", cb_down);
  gazebo::transport::SubscriberPtr sub_up = node->Subscribe("~/iris/sonar_up/link/sonar_up/sonar", cb_up);
    

   
  // Busy wait loop...replace with your own code as needed.
  while (true)
    gazebo::common::Time::MSleep(10);

  // Make sure to shut everything down.
  gazebo::client::shutdown();

}
