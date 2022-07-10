#!/usr/bin/env python3
import rospy
import cv2
from pyzbar.pyzbar import decode

def decoder(image):
    gray_img = cv2.cvtColor(image,0)
    barcode = decode(gray_img)

    for obj in barcode:

        barcodeData = obj.data.decode("utf-8")
        print("Barcode: "+barcodeData)

cap = cv2.VideoCapture(0)

if __name__ == "__main__":
    rospy.init_node("qrcode", anonymous=True)
    print("Ready!")
    while not rospy.is_shutdown():
        rate = rospy.Rate(20)
        ret, frame = cap.read()
        decoder(frame)
        rate.sleep()