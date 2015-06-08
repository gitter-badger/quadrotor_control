/** \file quadrotor.cc
    Implements the quadrotor domain, from hector_quadrotor in ROS
    \author Kunal Grover
*/

#include <rl_env/quadrotor.hh>
#include <hector_uav_msgs/Altimeter.h>
#include <ros/ros.h>

Quadrotor::Quadrotor():
  noisy(false),
  wind(false),
  rng(NULL),
  s(2)
{
  reset();
}

Quadrotor::Quadrotor(Random &rand, bool stochastic):
  noisy(stochastic),
  wind(stochastic),
  rng(rand),
  s(2)
{
  reset();
}

const std::vector<float> &Quadrotor::sensation() const { return s; }

float Quadrotor::apply(int action) {
  const quadrotor_action_t effect =
    noisy
    ? add_noise(static_cast<quadrotor_action_t>(action))
    : static_cast<quadrotor_action_t>(action);
  switch(effect) {
  case Z_PLUS:
    // What to do ?
    return -1;
  case Z_MINUS:
    // What to do ?
    return -1
  }
  std::cerr << "Unreachable point reached in Quadrotor::apply!!!\n";
  return 0; // unreachable, I hope
}

bool Quadrotor::terminal() const {
  return current_location == target_location;
}

void Quadrotor::reset() {
  current_location.fill(0.0);
  target_location.fill(0.0);
  std::cout << "Waiting to subscribe to hector";
  // Subscribe for the current location
  ros::TransportHints noDelay = ros::TransportHints().tcpNoDelay(true);
  ros::Subscriber quadrotor_state = node.subscribe("/altimeter", qDepth, listener_altimeter, noDelay);
  std::cout << "Subscribed to hector";
}

int Quadrotor::getNumActions() {
  return 2;
}

Quadrotor::quadrotor_action_t Quadrotor::add_noise(quadrotor_action_t action) {
  // TODO : Need to nodel real noise or get gazebo to do it
  return action;
}

void Quadrotor::apply_wind() {
  // TODO : Need to tell gazebo to apply location
}

void Quadrotor::randomize_target_location() {
  // TODO : Need to set target_location
}

void Quadrotor::setSensation(std::vector<float> newS){
  if (s.size() != newS.size()){
    cerr << "Error in sensation sizes" << endl;
  }

  for (unsigned i = 0; i < newS.size(); i++){
    s[i] = (int)newS[i];
  }
}

std::vector<experience> Quadrotor::getSeedings() {
  // return seedings
  std::vector<experience> seeds;

  if (true)
    return seeds;

  // TODO : How to get seeds ?
}

void Quadrotor::getMinMaxFeatures(std::vector<float> *minFeat,
                                  std::vector<float> *maxFeat){

  minFeat->resize(s.size(), 0.0);
  maxFeat->resize(s.size(), 1.0);

  (*minFeat)[0] = 0.0;
  (*maxFeat)[0] = 4.0;
  (*minFeat)[1] = 0.0;
  (*maxFeat)[1] = 4.0;
}

void Quadrotor::getMinMaxReward(float *minR,
                                float *maxR){

  *minR = -10.0;
  *maxR = 20.0;

}

void listener_altimeter(const hector_uav_msgs::Altimeter::ConstPtr& msg){
  cout<<"callback";
  ROS_INFO("I heard: [%d]", int(msg->altitude));
}