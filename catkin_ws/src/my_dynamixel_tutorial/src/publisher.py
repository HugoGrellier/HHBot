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

    def __init__(self, motor_name):
        rospy.init_node('speed_controller', anonymous=False)
        self.name = motor_name
        self.turn_counter = 0 
        self.turn_flag = 0
        self.first_turn_flag = 1
        self.begin_pos = 0
        self.speed_pub = rospy.Publisher('/'+self.name+'/command', Float64, queue_size=1)
        self.state_sub = rospy.Subscriber('/'+self.name+'/state', JointState, self.state_callback)
        rospy.loginfo('Waiting for speed command')
        rospy.Rate(1).sleep() #wait for publisher to synchronize

        

    def state_callback(self, data):
        if self.first_turn_flag:
            if data.current_pos < 5 :
                self.begin_pos = data.current_pos
            else :
                self.begin_pos = 5.2
            self.first_turn_flag = 0

        motor_pos = data.current_pos
        
        if motor_pos > self.begin_pos and self.turn_flag == 1:
            self.turn_flag = 0
            self.turn_counter += 1
            rospy.loginfo("" + str(self.name) + " : " + str(self.turn_counter))

        if motor_pos == 0:
            self.turn_flag = 1
    
    def turn_watcher(self, count):
        while not rospy.is_shutdown():
            print(self.turn_counter)
            if self.turn_counter == count:
                self.speed_controller(0)
                return


    def speed_controller(self,speed):
        # self.turn_counter = 0 
        s = Float64()
        s.data = speed
        self.speed_pub.publish(s)
    
    # def run(self, objb,objg ):
    #     while not rospy.is_shutdown():
    #         if self.turn_counter == counterb:
    #             self.speed_controller(0)

def turn_watcher(obj1 , count1, obj2 , count2):
    while ((obj1.turn_counter <= count1) and (obj2.turn_counter <= count2)):
        if obj1.turn_counter == count1:
            obj1.speed_controller(0)
        if obj2.turn_counter == count2:
            obj2.speed_controller(0)
        if obj1.turn_counter == count1 and obj2.turn_counter == count2:
            return


def glass_up(glass_controller):
        glass_controller.speed_controller(-4)
        glass_controller.turn_watcher(0)

def bottle_up(bottle_controller):
        bottle_controller.speed_controller(-5)
        bottle_controller.turn_watcher(1)

def glass_down(glass_controller):
        glass_controller.speed_controller(4)
        glass_controller.turn_watcher(4)

def bottle_down(bottle_controller):
        bottle_controller.speed_controller(5)
        bottle_controller.turn_watcher(8)



if __name__ == '__main__':
    try:
        glass_controller = Joint_Controller('joint1_controller')
        bottle_controller = Joint_Controller('joint2_controller')
        glass_controller.speed_controller(2)
        bottle_controller.speed_controller(2)
        turn_watcher(glass_controller,2,bottle_controller,2)
        #glass_down(glass_controller)
        #bottle_down(bottle_controller)


        # spin() simply keeps python from exiting until this node is stopped
        rospy.spin()
    except rospy.ROSInterruptException:
        pass

