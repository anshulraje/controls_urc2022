#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist
import os

hostname = "192.168.1.11" 

def check_connection():
    response = os.system("ping -c 1 -W 3 " + hostname)
    if response == 0:
        print(hostname, 'is up!')
    else:
        print("Connection lost, stopped rover")
        pub.publish(Twist())
    rate.sleep()

if __name__ == "__main__":
    rospy.init_node("connection_loss", anonymous=True)
    pub = rospy.Publisher("/rover", Twist, queue_size=10)
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        check_connection()