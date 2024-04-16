import sys


import Jetson.GPIO as GPIO
import time
import os


SPICLK = 11
SPIMISO = 9
SPIMOSI = 10
SPICS = 8
output_pin = 7
photo_ch = 0


def init():
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(output_pin, GPIO.OUT, initial=GPIO.HIGH)
    GPIO.setwarnings(False)
    GPIO.cleanup()
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(4, GPIO.OUT)
    GPIO.setup(18, GPIO.OUT)

def main():
    init()
   # while True:
 
    GPIO.setwarnings(False)
    # uu = sys.argv



    for i in range(0,int(sys.argv[1])):
	print(i)
        GPIO.output(4,True)
        GPIO.output(18,True) 
        time.sleep(1)

        GPIO.output(4,False)
        GPIO.output(18,False)
	time.sleep(1)
        
            
        

if __name__ == '__main__':
    try:
        main()
    #    GPIO.cleanup()
    except: 
        print("error")
    	GPIO.cleanup()
