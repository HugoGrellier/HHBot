#ifndef _ROS_turtlebot_arm_object_manipulation_ObjectDetectionResult_h
#define _ROS_turtlebot_arm_object_manipulation_ObjectDetectionResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace turtlebot_arm_object_manipulation
{

  class ObjectDetectionResult : public ros::Msg
  {
    public:
      uint32_t obj_names_length;
      typedef char* _obj_names_type;
      _obj_names_type st_obj_names;
      _obj_names_type * obj_names;

    ObjectDetectionResult():
      obj_names_length(0), obj_names(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->obj_names_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->obj_names_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->obj_names_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->obj_names_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->obj_names_length);
      for( uint32_t i = 0; i < obj_names_length; i++){
      uint32_t length_obj_namesi = strlen(this->obj_names[i]);
      varToArr(outbuffer + offset, length_obj_namesi);
      offset += 4;
      memcpy(outbuffer + offset, this->obj_names[i], length_obj_namesi);
      offset += length_obj_namesi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t obj_names_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      obj_names_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      obj_names_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      obj_names_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->obj_names_length);
      if(obj_names_lengthT > obj_names_length)
        this->obj_names = (char**)realloc(this->obj_names, obj_names_lengthT * sizeof(char*));
      obj_names_length = obj_names_lengthT;
      for( uint32_t i = 0; i < obj_names_length; i++){
      uint32_t length_st_obj_names;
      arrToVar(length_st_obj_names, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_obj_names; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_obj_names-1]=0;
      this->st_obj_names = (char *)(inbuffer + offset-1);
      offset += length_st_obj_names;
        memcpy( &(this->obj_names[i]), &(this->st_obj_names), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return "turtlebot_arm_object_manipulation/ObjectDetectionResult"; };
    const char * getMD5(){ return "02736298050f9335208931f532635983"; };

  };

}
#endif
