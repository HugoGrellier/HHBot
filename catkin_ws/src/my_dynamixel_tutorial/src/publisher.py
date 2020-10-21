#!/usr/bin/env python
import roslib
roslib.load_manifest('my_dynamixel_tutorial')

import rospy
import actionlib
from std_msgs.msg import Float64
import trajectory_msgs.msg
import control_msgs.msg
from trajectory_msgs.msg import JointTrajectoryPoint
from control_msgs.msg import JointTrajectoryAction, JointTrajectoryGoal, FollowJointTrajectoryAction, FollowJointTrajectoryGoal
from dynamixel_msgs.msg import JointState

class Joint_Controller:
    turn_counter = 0 
    turn_flag = 0
    first_turn_flag = 1
    begin_pos = 0

    def __init__(self, motor_name):
        rospy.init_node('speed_controller', anonymous=True)
        self.name = motor_name
        self.speed_pub = rospy.Publisher('/'+self.name+'/command', Float64, queue_size=1)
        self.state_sub = rospy.Subscriber('/'+self.name+'/state', JointState, self.state_callback)
        rospy.loginfo('Waiting for speed command')
        rospy.Rate(1).sleep() #wait for publisher to synchronize

        

    def state_callback(self, data):
        if self.first_turn_flag:
            self.begin_pos = data.current_pos
            self.first_turn_flag = 0

        motor_pos = data.current_pos
        
        if motor_pos > self.begin_pos and self.turn_flag == 1:
            self.turn_flag = 0
            self.turn_counter += 1
            rospy.loginfo(self.turn_counter)

        if motor_pos == 0:
            self.turn_flag = 1
    
    def turn_watcher(self, count):
        while not rospy.is_shutdown():
            if self.turn_counter == count:
                self.speed_controller(0)
                

    def speed_controller(self,speed):
        s = Float64()
        s.data = speed
        self.speed_pub.publish(s)
    
    def run(self, objb,objg ):
        while not rospy.is_shutdown():
            if self.turn_counter == counterb:
                self.speed_controller(0)


if __name__ == '__main__':
    try:
        glass_controller = Joint_Controller('joint1_controller')
        bottle_controller = Joint_Controller('joint2_controller')
        glass_controller.speed_controller(-3)
        bottle_controller.speed_controller(-3)
        glass_controller.turn_watcher(3)
        bottle_controller.turn_watcher(3)
        # spin() simply keeps python from exiting until this node is stopped
        rospy.spin()
    except rospy.ROSInterruptException:
        pass