#define DEBUG_MODULE "CONTROLLER"
#include "debug.h"

#include "cfassert.h"
#include "controller.h"
#include "controller_pid.h"
#include "controller_mellinger.h"
#include "controller_pwm.h"

#define DEFAULT_CONTROLLER ControllerTypePID
static ControllerType currentController = ControllerTypeAny;

static void initController();

typedef struct {
  void (*init)(void);
  bool (*test)(void);
  void (*update)(control_t *control, setpoint_t *setpoint, const sensorData_t *sensors, const state_t *state, const uint32_t tick);
  const char* name;
} ControllerFcns;

static ControllerFcns controllerFunctions[] = {
  {.init = 0, .test = 0, .update = 0, .name = "None"}, // Any
  {.init = 0, .test = 0, .update = 0, .name = "PWM"}, //pwm controller
  {.init = controllerPidInit, .test = controllerPidTest, .update = controllerPid, .name = "PID"}, //pid controller
  {.init = controllerMellingerInit, .test = controllerMellingerTest, .update = controllerMellinger, .name = "Mellinger"},
};


void controllerInit(ControllerType controller) {
  if (controller < 0 || controller >= ControllerType_COUNT) {
    return;
  }

  currentController = controller;

  if (ControllerTypeAny == currentController) {
    currentController = DEFAULT_CONTROLLER;
  }

  ControllerType forcedController = CONTROLLER_NAME;
  if (forcedController != ControllerTypeAny) {
    DEBUG_PRINT("Controller type forced\n");
    currentController = forcedController;
  }

  initController();

  DEBUG_PRINT("Using %s (%d) controller\n", controllerGetName(), currentController);
}

ControllerType getControllerType(void) {
  return currentController;
}

static void initController() {
  controllerFunctions[currentController].init();
}

bool controllerTest(void) {
  return controllerFunctions[currentController].test();
}

void controller(control_t *control, setpoint_t *setpoint, const sensorData_t *sensors, const state_t *state, const uint32_t tick) {
  controllerFunctions[currentController].update(control, setpoint, sensors, state, tick);
}

const char* controllerGetName() {
  return controllerFunctions[currentController].name;
}