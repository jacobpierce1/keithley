#include "keithley.h"

using namespace std;

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
  cout << "errno: " << errno << endl;

  return true;
}

/* Sets the output voltage of the Keithley. */
/* NB: it does NOT turn the output on */
bool output_voltage() {

  return true;
}

/* measures the current currently on the output */
float measure_current() {

  return 0;
}

/* performs a sweep from start_volt to end_volt */
/* with voltage step step_size and writes the result */
/* into the file pointed to by filename */
bool sweep(float start_volt, float end_volt, float step_size, std::string filename) {
  
  return true;
}


bool test() {
  const char *message = ":OUTP:ON";

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
