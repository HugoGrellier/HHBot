#ifndef _ROS_turtlebot_arm_object_manipulation_MoveToTargetAction_h
#define _ROS_turtlebot_arm_object_manipulation_MoveToTargetAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "turtlebot_arm_object_manipulation/MoveToTargetActionGoal.h"
#include "turtlebot_arm_object_manipulation/MoveToTargetActionResult.h"
#include "turtlebot_arm_object_manipulation/MoveToTargetActionFeedback.h"

namespace turtlebot_arm_object_manipulation
{

  class MoveToTargetAction : public ros::Msg
  {
    public:
      typedef turtlebot_arm_object_manipulation::MoveToTargetActionGoal _action_goal_type;
      _action_goal_type action_goal;
      typedef turtlebot_arm_object_manipulation::MoveToTargetActionResult _action_result_type;
      _action_result_type action_result;
      typedef turtlebot_arm_object_manipulation::MoveToTargetActionFeedback _action_feedback_type;
      _action_feedback_type action_feedback;

    MoveToTargetAction():
      action_goal(),
      action_result(),
      action_feedback()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->action_goal.serialize(outbuffer + offset);
      offset += this->action_result.serialize(outbuffer + offset);
      offset += this->action_feedback.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->action_goal.deserialize(inbuffer + offset);
      offset += this->action_result.deserialize(inbuffer + offset);
      offset += this->action_feedback.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "turtlebot_arm_object_manipulation/MoveToTargetAction"; };
    const char * getMD5(){ return "5584817ba7b85e65b829587a64ddba4f"; };

  };

}
#endif
