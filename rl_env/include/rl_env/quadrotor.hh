/** \file quadrotor.hh
    Defines the quadrotor domain, from hector_quadrotor in ROS
    \author Kunal Grover
*/

#ifndef _TAXI_H_
#define _TAXI_H_

#include <set>
#include <array>
#include <rl_common/Random.h>
#include <rl_common/core.hh>
#include "gridworld.hh"
#include <hector_uav_msgs/Altimeter.h>

/** This class defines the Quadrotor domain. */
class Quadrotor: public Environment {
public:
  /** Creates a Quadrotor domain.
      \param stochastic Whether to use nondeterministic actions and wind
  */
  Quadrotor(Random &rand, bool stochastic);

  /** Creates a deterministic Taxi domain.
  */
  Quadrotor();

  virtual ~Quadrotor();

  virtual const std::vector<float> &sensation() const;
  virtual float apply(int action);

  virtual bool terminal() const;
  virtual void reset();
  virtual int getNumActions();
  virtual void getMinMaxFeatures(std::vector<float> *minFeat, std::vector<float> *maxFeat);
  virtual void getMinMaxReward(float* minR, float* maxR);
  virtual std::vector<experience> getSeedings();
  void setSensation(std::vector<float> newS);

protected:
  typedef std::array<float,5> coord_t;
  enum quadrotor_action_t {Z_PLUS, Z_MINUS};
  coord_t current_location, target_location;

private:
  const bool noisy;
  Random &rng;

  std::vector<float> s;
  const bool wind;

  ros::Subscriber hector_altitude;

  /** Corrupts a movement action.
      \param action The intended action
      \return The action actually executed */
  quadrotor_action_t add_noise(quadrotor_action_t action);

  /** If the domain is noisy, then potentially change the destination.  */
  void apply_wind();

  /** Randomly assign what the target location is */
  void randomize_target_location();

  /** Listens to the uav message Altimeter */
  void listener_altimeter(const hector_uav_msgs::Altimeter::ConstPtr& msg);
};

#endif
