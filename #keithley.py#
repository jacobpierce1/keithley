import socket
import time

class Keithley:

    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect(("128.135.52.219", 5025))

    def output_on(self):
        self.sock.send(":OUTP ON\n")
        return True

    def output_off(self):
        self.sock.send(":OUTP OFF\n")
        return True

    def set_voltage(self, volt):
        self.sock.send(":SOURce:VOLT " + str(volt) + "\n")
        return True

    def music(self):
        for i in range(100, 4000, 250):
            self.sock.send(":SYST:BEEP "+str(i)+", 0.5\n")
        return True

    def beep(self):
        for i in range(3): 
            self.sock.send(":SYST:BEEP 1000, .4\n")
            time.sleep(.2)
        return True;

    def happy_birthday(self):
        freqz = [523,523,587,523,698,659,0,523,523,587,523,785,698,0,523,523,1047,880,698,659,587,0,1047,1047,880,698,785,698]
        for f in freqz:
            if f == 0:
                time.sleep(0.4)
            else:
                self.sock.send(":SYST:BEEP "+str(f)+", 0.1\n")
                time.sleep(0.4)
        return True

    def int_sweep(self, start, stop, step):
        numsteps = int((stop-start)/float(step))
        self.sock.send(":SOUR:FUNC VOLT\n")
        self.sock.send(":SOUR:VOLT:RANG 70\n")
        self.sock.send(":SENS:FUNC \"CURR\"\n")
        self.sock.send(":SENS:CURR:RANG 500e-6\n")
        self.sock.send(":SOUR:SWE:VOLT:LIN "+str(start)+", "+str(stop)+", "+str(numsteps)+", 1, 1, FIXED, OFF\n")
        self.sock.send(":INIT\n")

    def ext_sweep(self, start, stop, step, pause_time=.3):
        numsteps = int((stop-start)/float(step))
        self.sock.send(":TRAC:CLE\n")
        self.sock.send(":SOUR:FUNC VOLT\n")
        self.sock.send(":SOUR:VOLT:RANG 80\n")
        self.sock.send(":SENS:FUNC \"CURR\"\n")
        self.sock.send(":SENS:CURR:RANG 500e-6\n")
        self.output_on()

        for i in range(1, numsteps+1):
            v = start + i*step
            print "Testing voltage: "+str(v)
            self.set_voltage(v)
            
            # pause and then read
            if (i==1): time.sleep(5)
            else: time.sleep(pause_time)
            
            self.sock.send(":READ? \"defbuffer1\", FORM, READ\n")
            
        self.output_off()
        print "INFO: finished taking data"


    def write_to_usb(self, file_name):
        print "INFO: saving defbuffer1 to USB drive as '" + file_name + "'"
        self.beep()
        status = self.sock.send('TRAC:SAVE "/usb1/' + file_name + '.csv", "defbuffer1"\n')
        time.sleep(6)
        if (status <= 0): print ("WARNING: unsuccessful write to usb")
    # def measure_resistance(self):
    #     self.set_voltage(2)
        
        

k = Keithley()

#k.set_voltage(27)
k.ext_sweep(20,30, 40E-3, 3)
k.write_to_usb("sensl4_10_4")
