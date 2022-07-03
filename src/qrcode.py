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
while not rospy.is_shutdown():
    ret, frame = cap.read()
    decoder(frame)