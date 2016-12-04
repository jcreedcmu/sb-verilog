# include  <vpi_user.h>

static int interact_compiletf(char *user_data) {
  return 0;
}

static int interact_calltf(char *user_data) {
  vpi_printf("Interact, World!\n");
  return 0;
}

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

void interact_register() {
  s_vpi_systf_data tf_data;

  tf_data.type      = vpiSysTask;
  tf_data.tfname    = "$interact";
  tf_data.calltf    = interact_calltf;
  tf_data.compiletf = interact_compiletf;
  tf_data.sizetf    = 0;
  tf_data.user_data = 0;
  vpi_register_systf(&tf_data);
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
  interact_register,
  register_increment,
  0
};
