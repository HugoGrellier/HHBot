#ifndef _ROS_turtlebot_arm_object_manipulation_MoveToTargetGoal_h
#define _ROS_turtlebot_arm_object_manipulation_MoveToTargetGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace turtlebot_arm_object_manipulation
{

  class MoveToTargetGoal : public ros::Msg
  {
    public:
      typedef uint8_t _target_type_type;
      _target_type_type target_type;
      typedef const char* _named_target_type;
      _named_target_type named_target;
      enum { JOINT_STATE =  1 };
      enum { POSE_TARGET =  2 };
      enum { NAMED_TARGET =  3 };

    MoveToTargetGoal():
      target_type(0),
      named_target("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->target_type >> (8 * 0)) & 0xFF;
      offset += sizeof(this->target_type);
      uint32_t length_named_target = strlen(this->named_target);
      varToArr(outbuffer + offset, length_named_target);
      offset += 4;
      memcpy(outbuffer + offset, this->named_target, length_named_target);
      offset += length_named_target;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->target_type =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->target_type);
      uint32_t length_named_target;
      arrToVar(length_named_target, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_named_target; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_named_target-1]=0;
      this->named_target = (char *)(inbuffer + offset-1);
      offset += length_named_target;
     return offset;
    }

    const char * getType(){ return "turtlebot_arm_object_manipulation/MoveToTargetGoal"; };
    const char * getMD5(){ return "a0450d6732c71ca58c4402334c28860d"; };

  };

}
#endif
