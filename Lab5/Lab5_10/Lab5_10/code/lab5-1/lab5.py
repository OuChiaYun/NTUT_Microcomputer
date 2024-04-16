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
    GPIO.setup(output_pin,GPIO.OUT,initial = GPIO.HIGH)
    GPIO.setwarnings(False)
    GPIO.cleanup()
    GPIO.setmode(GPIO.BCM)
    
    GPIO.setup(SPIMOSI,GPIO.OUT)
    GPIO.setup(SPIMISO,GPIO.IN)
    GPIO.setup(SPICLK,GPIO.OUT)
    GPIO.setup(SPICS,GPIO.OUT)

def readadc(adcnum,clockpin,mosipin,misopin,cspin):
    if((adcnum > 7)or (adcnum <0) ):
        return -1
    GPIO.output(cspin,True)

    GPIO.output(clockpin,False)
    GPIO.output(cspin,False)

    commandout = adcnum        
    commandout |= 0x18
    commandout <<=3

    for i in range(5):
        if(commandout & 0x80):
            GPIO.output(mosipin,True)
        else:
            GPIO.output(mosipin,False)
            
        commandout <<=1
        GPIO.output(clockpin,True)
        GPIO.output(clockpin,False)
        
    adcout = 0
    
    for i in range(12):
        GPIO.output(clockpin,True)
        GPIO.output(clockpin,False)
        adcout <<= 1
        
        if(GPIO.input(misopin)):
            adcout |= 0x1

    GPIO.output(cspin,True)
    
    adcout >>=1
    return adcout
 
def main():
    init()
    while True:
        adc_value = readadc(photo_ch,SPICLK,SPIMOSI,SPIMISO,SPICS)
        print(adc_value)
        
        cpptest="gpio.exe" #in linux without suffix .exe
        if adc_value < 400 and os.path.exists(cpptest):
            cpptest="./gpio.exe LED1 off"
            os.system(cpptest)

        if adc_value >= 400 and os.path.exists(cpptest):
            cpptest="./gpio.exe LED1 on"
            os.system(cpptest)
	
	cpptest="gpio2.exe"
        if adc_value < 400 and os.path.exists(cpptest):
            cpptest="./gpio2.exe LED2 on"
            os.system(cpptest)

        if adc_value >= 400 and os.path.exists(cpptest):
            cpptest="./gpio2.exe LED2 off"
            os.system(cpptest)
        time.sleep(1)
        
if __name__ == '__main__':
    try:
        main()
    except:
        print("error")
        
