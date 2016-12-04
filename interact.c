#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/time.h>
#include <fcntl.h>

#include  <vpi_user.h>

static int increment(char *userdata) {
  vpiHandle systfref, args_iter, argh;
  struct t_vpi_value argval;
  int value;

  // Obtain a handle to the argument list
  systfref = vpi_handle(vpiSysTfCall, NULL);
  args_iter = vpi_iterate(vpiArgument, systfref);

  // Grab the value of the first argument
  argh = vpi_scan(args_iter);
  argval.format = vpiIntVal;
  vpi_get_value(argh, &argval);
  value = argval.value.integer;
  vpi_printf("VPI routine received %d\n", value);

  // Increment the value and put it back as first argument
  argval.value.integer = value + 1;
  vpi_put_value(argh, &argval, NULL, vpiNoDelay);

  // Cleanup and return
  vpi_free_object(args_iter);
  return 0;
}

static void _readIn(int *avail, char *data, int waitMs) {
  int stdin = 0;
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(stdin, &fds);
  struct timeval timeout;
  timeout.tv_sec = waitMs / 1000;
  timeout.tv_usec = (waitMs * 1000) % 1000000;
  *avail = select(1, &fds, (fd_set *) 0, (fd_set *) 0, &timeout);
  if (*avail) {
    read(stdin, data, 1);
  }
}

// $readIn(availReg, dataReg, timeoutInMs)
static int readIn(char *userdata) {
  vpiHandle systfref, args_iter;
  vpiHandle argh[3];
  struct t_vpi_value argval;

  // Obtain a handle to the argument list
  systfref = vpi_handle(vpiSysTfCall, NULL);
  args_iter = vpi_iterate(vpiArgument, systfref);
  // XXX how to check number, types of arguments???
  argh[0] = vpi_scan(args_iter);
  argh[1] = vpi_scan(args_iter);
  argh[2] = vpi_scan(args_iter);

  argval.format = vpiIntVal;
  vpi_get_value(argh[2], &argval);
  int timeout = argval.value.integer;

  int avail, data;
  _readIn(&avail, &data, timeout);

  if (avail) {
    // Availability into first argument
    argval.format = vpiIntVal;
    argval.value.integer = avail;
    vpi_put_value(argh[0], &argval, NULL, vpiNoDelay);

    // Data into first argument
    argval.format = vpiIntVal;
    argval.value.integer = data;
    vpi_put_value(argh[1], &argval, NULL, vpiNoDelay);
  }

  // Cleanup and return
  vpi_free_object(args_iter);
  return 0;
}

void register_readIn() {
  s_vpi_systf_data data;
  data.type = vpiSysTask;
  data.tfname = "$read_async";
  data.sizetf = 0;
  data.user_data = 0;
  data.calltf = readIn;
  data.compiletf = 0;
  vpi_register_systf(&data);
}


void register_increment() {
  s_vpi_systf_data data;
  data.type = vpiSysTask;
  data.tfname = "$increment";
  data.sizetf = 0;
  data.user_data = 0;
  data.calltf = increment;
  data.compiletf = 0;
  vpi_register_systf(&data);
}

void (*vlog_startup_routines[])() = {
  //  register_interact,
  register_readIn,
  register_increment,
  0
};
