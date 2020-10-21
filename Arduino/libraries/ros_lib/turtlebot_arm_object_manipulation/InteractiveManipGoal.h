#ifndef _ROS_turtlebot_arm_object_manipulation_InteractiveManipGoal_h
#define _ROS_turtlebot_arm_object_manipulation_InteractiveManipGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace turtlebot_arm_object_manipulation
{

  class InteractiveManipGoal : public ros::Msg
  {
    public:
      typedef const char* _frame_type;
      _frame_type frame;

    InteractiveManipGoal():
      frame("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_frame = strlen(this->frame);
      varToArr(outbuffer + offset, length_frame);
      offset += 4;
      memcpy(outbuffer + offset, this->frame, length_frame);
      offset += length_frame;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_frame;
      arrToVar(length_frame, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_frame; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_frame-1]=0;
      this->frame = (char *)(inbuffer + offset-1);
      offset += length_frame;
     return offset;
    }

    const char * getType(){ return "turtlebot_arm_object_manipulation/InteractiveManipGoal"; };
    const char * getMD5(){ return "a054304ca480f0e0c67ec5f261591b09"; };

  };

}
#endif
