#include "keithley.h"

#define DEST_IP "128.135.52.219"


int sockid = 0;
struct sockaddr_in dest_addr;

/* connects with Keithley at IP address iaddr */
bool keithley_connect(const char *ipaddr) {

  // creating socket
  sockid = socket(AF_INET, SOCK_STREAM, 0);

  // check for socket errors
  if (sockid == -1) {
    std::cout << "Unable to create socket\n";
    return false;
  }
  
  // setting up structs
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(5025); // destination port 80
  dest_addr.sin_addr.s_addr = inet_addr(DEST_IP); // destination IP 128.135.52.219
  memset(&(dest_addr.sin_zero), '\0', 8); // zero the rest of the struct

  // attempting to connect to the Keithley
  if (connect(sockid, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) == -1) {
    std::cout << "Unable to connect socket to ipaddr; exiting";
  }
  return true;
}

/* disconnects from Keithley device */
bool keithley_disconnect() {

  if (close(sockid) == -1) {
    std::cout << "Unable to close socket\n";
    return false;
  }

  return true;

}

/* turns the output ON with voltage set by output_voltage */
bool output_on() {

  const char *message = ":OUTP ON\n";
  // first, try sending 
  int bytes = send(sockid, message, strlen(message), 0);
  cout << "Bytes written: " << bytes << endl;
  cout << "errno: " << errno << endl;
  
  return true;

}

/* turns the output OFF */
bool output_off() {

  const char *message = ":OUTP OFF\n";
  // first, try sending 
  int bytes = send(sockid, message, strlen(message), 0);
  cout << "Bytes written: " << bytes << endl;
  return true;
}

/* Sets the output voltage of the Keithley. */
/* NB: it does NOT turn the output on */
void set_voltage(float voltage) {
  const char *message = (":SOUR:VOLT " + to_string(voltage) + "\n").c_str();
  send(sockid, message, 30, 0);
  return;
}

/* measures the current currently on the output */
float measure_current() {

  return 0;
}



bool test() {
  const char *message = ":OUTP:ON\n";

  // first, try sending 
  int bytes = send(sockid, message, strlen(message), 0);
  cout << "Bytes written: " << bytes << endl;
  cout << "errno: " << errno << endl;

  //next try sendto
  // const struct sockaddr *to = (const struct sockaddr *) &dest_addr;
  // bytes = sendto(sockid, message, strlen(message)+1, 0, to, sizeof(to));
  // cout << "Bytes written by sendto: " << bytes << endl;
  // cout << "errno: " << errno << endl;
  
  // // attempt to receive
  // void *buffer;
  // bytes = recv(sockid, buffer, 100, 0);
  // cout << "status of recv: " << bytes << endl;
  // cout << "errno: " << errno << endl;
  
  return true;
}




void happy_birthday() {
  vector<int> freqz {523,523,587,523,698,659,0,523,523,587,523,785,698,0,523,523,1047,880,698,659,587,0,1047,1047,880,698,785,698};
  for (auto f : freqz) {
    if (f == 0) usleep (4e5);
    else {
      const char *message = (":SYST:BEEP "+to_string(f)+ ", 0.1\n").c_str();
      send(sockid, message, 30, 0);
      usleep(4e5);
    }
  }
  return;
}


void beep() {
  for (auto i : "012") send(sockid, ":SYST:BEEP 1000, .4\n", 30, 0);
  usleep(3e5);
  return;
}


// note: pause_time is given in seconds 
void sweep(float start, float stop, float step, float pause_time, string file_name = "") {

  // set voltage and current as functions to be set and recorded
  send(sockid, ":TRAC:CLE\n", 30, 0);
  send(sockid, ":SOUR:FUNC VOLT\n", 30, 0);
  send(sockid, ":SOUR:VOLT:RANG 80\n", 30, 0);
  send(sockid, ":SENS:FUNC \"CURR\"\n", 30, 0);
  send(sockid, ":SENS:CURR:RANG 500e-6\n", 30, 0);
  output_on();

  // loop: set voltage and read the current according to input parameters
  int num_steps = round((stop-start)/step); 
  for (int i=0; i<num_steps; i++) {

    // set voltage;
    float voltage = start + i*step;
    cout << voltage << endl;
    set_voltage(voltage);
    
    // sleep and read
    unsigned int usleep_time = pause_time * 10e6;
    usleep(usleep_time);
    send(sockid, ":READ? \"defbuffer1\", FORM, READ\n", 30, 0);
  }
  
  // save to usb if applicable and return
  if (file_name != "") write_to_usb(file_name);
  return;
}


void write_to_usb(string file_name) {
  cout << "INFO: saving defbuffer1 to USB drive as '" + file_name + "'";
  const char *message = ("TRAC:SAVE \"/usb1/" + file_name + ".csv\", \"defbuffer1\"\n").c_str();
  int status = send(sockid, message, 30, 0);
  usleep(6e6);

  // error handling (usually doesn't work)
  if (status <= 0) cout << "WARNING: unsuccessful write to usb drive" << endl;
}


int main() {
  cout << "test" << endl;
  return 0;
}
