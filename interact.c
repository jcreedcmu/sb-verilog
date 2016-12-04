# include  <vpi_user.h>

static int interact_compiletf(char *user_data) {
  return 0;
}

static int interact_calltf(char *user_data) {
  vpi_printf("Interact, World!\n");
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

void (*vlog_startup_routines[])() = {
  interact_register,
  0
};
