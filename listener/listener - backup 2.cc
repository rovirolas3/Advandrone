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

using namespace std;

float range_back {};
float range_right {};
float range_left {};
float range_front {};
float range_down {};


 
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


void cb_right(ConstSonarStampedPtr &_msg)
{
  // Dump the message contents to stdout.
  range_right = _msg->sonar().range();
  std::cout <<"DISTANCE RIGHT: "<< range_right<<"\n";
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
  gazebo::transport::SubscriberPtr sub_back = node->Subscribe("~/iris/sonar_model/link/sonar_back/sonar", cb_back);
  gazebo::transport::SubscriberPtr sub_left = node->Subscribe("~/iris/sonar_model/link/sonar_left/sonar", cb_left);
  gazebo::transport::SubscriberPtr sub_right = node->Subscribe("~/iris/sonar_model/link/sonar_right/sonar", cb_right);
  //gazebo::transport::SubscriberPtr sub_front = node->Subscribe("~/iris/sonar_model/link/sonar_front/sonar", cb_front);
  gazebo::transport::SubscriberPtr sub_down = node->Subscribe("~/iris/sonar_model/link/sonar_down/sonar", cb_down);
    

   
  // Busy wait loop...replace with your own code as needed.
  while (true)
    gazebo::common::Time::MSleep(10);

  // Make sure to shut everything down.
  gazebo::client::shutdown();

}
