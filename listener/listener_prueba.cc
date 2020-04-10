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
float global_skip_counter = 200;
 
/////////////////////////////////////////////////
// Function is called everytime a message is received.
void cb_back(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_back = _msg->sonar().range();
  std::cout <<"DISTANCE BACK: "<<range_back<<"\n";
  // ofstream outputFile;
  // outputFile.open("distance_back.txt");
  // outputFile<<range_back;
  // outputFile.close();
}


void cb_left(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_left = _msg->sonar().range();
  std::cout <<"DISTANCE LEFT: "<<range_left<<"\n";
  
}
// create a sensor pointing up

void cb_right(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_right = _msg->sonar().range();
  std::cout <<"DISTANCE RIGHT: "<< range_right<<"\n";
 
  if (range_right_skip_counter > 0) { 

    range_right_skip_counter = range_right_skip_counter - 1; 

  } else if (range_right >= 4) {

       system("python /home/miguel/catkin_ws/src/Firmware/avoidobstacleright.py BACK");
       range_right_skip_counter = global_skip_counter;

  } else if (range_right <= 1) {

       system("python /home/miguel/catkin_ws/src/Firmware/avoidobstacleright.py EVIT");
       range_right_skip_counter = global_skip_counter;  
   
  }
  std::cout <<"range_right_times: "<< range_right_times<<"\n";
  std::cout <<"range_right_skip_counter: "<< range_right_skip_counter<<"\n";
}

/*
void cb_front(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_front = _msg->sonar().range();
  std::cout <<"DISTANCE FRONT: "<< range_front<<"\n";
}
*/

void cb_down(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_down = _msg->sonar().range();
  std::cout <<"DISTANCE DOWN: "<< range_down<<"\n";
  // When the down sonsor is in the range of 2 meters hold
}


void cb_up(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_up = _msg->sonar().range();
  std::cout <<"DISTANCE UP: "<< range_up<<"\n";
  // When the down sonsor is in the range of 2 meters hold
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
  //gazebo::transport::SubscriberPtr sub_back = node->Subscribe("~/iris/sonar_back/link/sonar_back/sonar", cb_back);
  gazebo::transport::SubscriberPtr sub_left = node->Subscribe("~/iris/sonar_left/link/sonar_left/sonar", cb_left);
  //gazebo::transport::SubscriberPtr sub_right = node->Subscribe("~/iris/sonar_right/link/sonar_right/sonar", cb_right);
  //gazebo::transport::SubscriberPtr sub_front = node->Subscribe("~/iris/sonar_model/link/sonar_front/sonar", cb_front);
  //gazebo::transport::SubscriberPtr sub_down = node->Subscribe("~/iris/sonar_down/link/sonar_down/sonar", cb_down);
  //gazebo::transport::SubscriberPtr sub_right = node->Subscribe("~/iris/sonar_up/link/sonar_up/sonar", cb_up);
    

   
  // Busy wait loop...replace with your own code as needed.
  while (true)
    gazebo::common::Time::MSleep(10);

  // Make sure to shut everything down.
  gazebo::client::shutdown();

}
