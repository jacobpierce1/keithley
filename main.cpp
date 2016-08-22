#include "keithley.h"

using namespace std;

int main(int argc, char **argv) {

  // connect to keithley
  bool status = keithley_connect("128.135.52.219");

  if (status == false) {
    cout << "FAIL" << endl;

  }

  output_off();

  
  // disconnect from keithley
  keithley_disconnect();

  return 0;
}
