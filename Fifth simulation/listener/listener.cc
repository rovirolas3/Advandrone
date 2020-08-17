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
#include <string>

using namespace std;

// Global values with the range of each sensor
float range_back {};
float range_right {};
float range_left {};
float range_front {};
float range_down {};
float range_up {};

// Global values with the times the drone has moved from the desired position
float range_back_times = 0;
float range_right_times = 0;
float range_left_times = 0;
float range_front_times = 0;
float range_down_times = 0;
float range_up_times = 0;

// Number of times left to skip the sensor value and not overfload
float range_back_skip_counter = 0;
float range_right_skip_counter = 0;
float range_left_skip_counter = 0;
float range_front_skip_counter = 0;
float range_down_skip_counter = 0;
float range_up_skip_counter = 0;

// Number of times we don't catch the value of the sensor
float global_skip_counter = 15;


// Max ranges
float range_max = 4;			// Distance where the drone can go back to the desired position
float range_unblock_movement = 3;	// At that range the drone unblock the possibility to go in this direction
float range_block_movement = 2;		// At that range the drone block the possibility to go in this direction
float range_avoid_obstacle = 1;		// If it detects an object near it goes X distance in the opposite direction
float range_avoid_obstacle_down = 0.3;	// The distance of the down sensor has a minor range

// Path of the files
char pathBack[] = "/home/miguel/catkin_ws/src/Firmware/avoidobstacleback.py"; 
char pathFront[] = "/home/miguel/catkin_ws/src/Firmware/avoidobstaclefront.py";
char pathRight[] = "/home/miguel/catkin_ws/src/Firmware/avoidobstacleright.py";
char pathLeft[] = "/home/miguel/catkin_ws/src/Firmware/avoidobstacleleft.py";
char pathUp[] = "/home/miguel/catkin_ws/src/Firmware/avoidobstacleup.py";
char pathDown[] = "/home/miguel/catkin_ws/src/Firmware/avoidobstacledown.py";

// Some char lists to call on the system function
char pythonstring[] = "python ";
char backstring[] = " BACK &";
char unblockstring[] = " UNBLOCK &";
char evitstring[] = " EVIT &";
char blockstring[] =  " BLOCK &";
 


/////////////////////////////////////////////////
// Function is called everytime a message is received.




// ---------------------------------BACK-----------------------------------
void cb_back(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_back = _msg->sonar().range();
  std::cout <<"DISTANCE BACK: "<<range_back<<"\n";

  // Depending on the distance detected, sends one missage or another to the python script 
  if (range_back_skip_counter > 0) { 

    range_back_skip_counter = range_back_skip_counter - 1; 
/*
  } else if (range_back >= range_max) {

       strcpy (command, pythonstring);
       strcat (command, pathBack);
       strcat (command, backstring);
       system(command);
       range_back_skip_counter = global_skip_counter;
       std::cout <<"Posibility to go back\n";
*/
  } else if (range_back >= range_unblock_movement) {
       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathBack);
       strcat (command, unblockstring);
       system(command);
       range_back_skip_counter = global_skip_counter;
       std::cout <<"Unblocking to go back\n";

  } else if (range_back < range_avoid_obstacle) {
       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathBack);
       strcat (command, evitstring);
       system(command);
       range_back_skip_counter = global_skip_counter;
       std::cout <<"Detected obstacle in the back\n";  
   
  } else if (range_back < range_block_movement) {
       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathBack);
       strcat (command, blockstring);
       system(command);
       range_back_skip_counter = global_skip_counter;
       std::cout <<"Blocking to go back\n";
  }

  //std::cout <<"range_back_times: "<< range_right_times<<"\n";
  //std::cout <<"range_back_skip_counter: "<< range_right_skip_counter<<"\n";

}

// ---------------------------------LEFT-----------------------------------

void cb_left(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_left = _msg->sonar().range();
  std::cout <<"DISTANCE LEFT: "<<range_left<<"\n";

  // Depending on the distance detected, sends one missage or another to the python script 
  if (range_left_skip_counter > 0) { 

    range_left_skip_counter = range_left_skip_counter - 1; 
/*
  } else if (range_left >= range_max) {

       strcpy (command, pythonstring);
       strcat (command, pathLeft);
       strcat (command, backstring);
       system(command);
       range_left_skip_counter = global_skip_counter;
       std::cout <<"Posibility to go left\n";
*/
  } else if (range_left >= range_unblock_movement) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathLeft);
       strcat (command, unblockstring);
       system(command);
       range_left_skip_counter = global_skip_counter;
       std::cout <<"Unblocking to go left\n";

  } else if (range_left < range_avoid_obstacle) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathLeft);
       strcat (command, evitstring);
       system(command);
       range_left_skip_counter = global_skip_counter;
       std::cout <<"Detected obstacle in the left\n";  
   
  } else if (range_left < range_block_movement) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathLeft);
       strcat (command, blockstring);
       system(command);
       range_left_skip_counter = global_skip_counter;
       std::cout <<"Blocking to go left\n";
  }

  //std::cout <<"range_left_times: "<< range_right_times<<"\n";
  //std::cout <<"range_left_skip_counter: "<< range_right_skip_counter<<"\n";
  
}

// ---------------------------------RIGHT-----------------------------------
void cb_right(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_right = _msg->sonar().range();
  std::cout <<"DISTANCE RIGHT: "<< range_right<<"\n";

  // Depending on the distance detected, sends one missage or another to the python script  
  if (range_right_skip_counter > 0) { 

    range_right_skip_counter = range_right_skip_counter - 1; 
/*
  } else if (range_right >= range_max) {

       strcpy (command, pythonstring);
       strcat (command, pathRight);
       strcat (command, backstring);
       system(command);
       range_right_skip_counter = global_skip_counter;
       std::cout <<"Posibility to go right\n";
*/
  } else if (range_right >= range_unblock_movement) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathRight);
       strcat (command, unblockstring);
       system(command);
       range_right_skip_counter = global_skip_counter;
       std::cout <<"Unblocking to go right\n";

  } else if (range_right < range_avoid_obstacle) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathRight);
       strcat (command, evitstring);
       system(command);
       range_right_skip_counter = global_skip_counter;
       std::cout <<"Detected obstacle in the right\n";  
    
  } else if (range_right < range_block_movement) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathRight);
       strcat (command, blockstring);
       system(command);
       range_right_skip_counter = global_skip_counter;
       std::cout <<"Blocking to go right\n";
  }

  //std::cout <<"range_right_times: "<< range_right_times<<"\n";
  //std::cout <<"range_right_skip_counter: "<< range_right_skip_counter<<"\n";
}

// ---------------------------------FRONT-----------------------------------
void cb_front(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_front = _msg->sonar().range();
  std::cout <<"DISTANCE FRONT: "<< range_front<<"\n";

  // Depending on the distance detected, sends one missage or another to the python script 
  if (range_front_skip_counter > 0) { 

    range_front_skip_counter = range_front_skip_counter - 1; 
/*
  } else if (range_front >= range_max) {

       strcpy (command, pythonstring);
       strcat (command, pathFront);
       strcat (command, backstring);
       system(command);
       range_front_skip_counter = global_skip_counter;
       std::cout <<"Posibility to go front\n";
*/
  } else if (range_front >= range_unblock_movement) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathFront);
       strcat (command, unblockstring);
       system(command);
       range_front_skip_counter = global_skip_counter;
       std::cout <<"Unblocking to go front\n";

  } else if (range_front < range_avoid_obstacle) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathFront);
       strcat (command, evitstring);
       system(command);
       range_front_skip_counter = global_skip_counter;
       std::cout <<"Detected obstacle in the front\n";  
   
  } else if (range_front < range_block_movement) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathFront);
       strcat (command, blockstring);
       system(command);
       range_front_skip_counter = global_skip_counter;
       std::cout <<"Blocking to go front\n";
  }

  //std::cout <<"range_right_times: "<< range_right_times<<"\n";
  //std::cout <<"range_right_skip_counter: "<< range_right_skip_counter<<"\n";


}

// ---------------------------------DOWN-----------------------------------
void cb_down(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_down = _msg->sonar().range();
  std::cout <<"DISTANCE DOWN: "<< range_down<<"\n";
  
  // Depending on the distance detected, sends one missage or another to the python script 
  if (range_down_skip_counter > 0) { 

    range_down_skip_counter = range_down_skip_counter - 1; 
/*
  } else if (range_down >= range_max) {

       strcpy (command, pythonstring);
       strcat (command, pathDown);
       strcat (command, backstring);
       system(command);
       range_down_skip_counter = global_skip_counter;
       std::cout <<"Posibility to go down\n";
*/
  } else if (range_down >= range_unblock_movement) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathDown);
       strcat (command, unblockstring);
       system(command);
       range_down_skip_counter = global_skip_counter;
       std::cout <<"Unblocking to go down\n";

  } else if (range_down < range_avoid_obstacle_down) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathDown);
       strcat (command, evitstring);
       system(command);
       range_down_skip_counter = global_skip_counter;
       std::cout <<"Detected obstacle in the down\n";  
   
  } else if (range_down < range_block_movement) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathDown);
       strcat (command, blockstring);
       system(command);
       range_down_skip_counter = global_skip_counter;
       std::cout <<"Blocking to go down\n";
  }

  //std::cout <<"range_right_times: "<< range_right_times<<"\n";
  //std::cout <<"range_right_skip_counter: "<< range_right_skip_counter<<"\n";

}

// ---------------------------------UP-----------------------------------
void cb_up(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_up = _msg->sonar().range();
  std::cout <<"DISTANCE UP: "<< range_up<<"\n";

  // Depending on the distance detected, sends one missage or another to the python script 
  if (range_up_skip_counter > 0) { 

    range_up_skip_counter = range_up_skip_counter - 1; 
/*
  } else if (range_up >= range_max) {

       strcpy (command, pythonstring);
       strcat (command, pathUp);
       strcat (command, backstring);
       system(command);
       range_up_skip_counter = global_skip_counter;
       std::cout <<"Posibility to go up\n";
*/
  } else if (range_up >= range_unblock_movement) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathUp);
       strcat (command, unblockstring);
       system(command);
       range_up_skip_counter = global_skip_counter;
       std::cout <<"Unblocking to go up\n";

  } else if (range_up < range_avoid_obstacle) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathUp);
       strcat (command, evitstring);
       system(command);
       range_up_skip_counter = global_skip_counter;
       std::cout <<"Detected obstacle in the up\n";  
   
  } else if (range_up < range_block_movement) {

       char command[200];
       strcpy (command, pythonstring);
       strcat (command, pathUp);
       strcat (command, blockstring);
       system(command);
       range_up_skip_counter = global_skip_counter;
       std::cout <<"Blocking to go up\n";
  }

  //std::cout <<"range_right_times: "<< range_right_times<<"\n";
  //std::cout <<"range_right_skip_counter: "<< range_right_skip_counter<<"\n";

}










/////////////////////////////////////////////////////////////////////////////






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
