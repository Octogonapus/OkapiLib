/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef _OKAPI_ASYNCPOSPIDCONTROLLER_HPP_
#define _OKAPI_ASYNCPOSPIDCONTROLLER_HPP_

#include "api.h"
#include "okapi/control/async/asyncPositionController.hpp"
#include "okapi/control/iterative/posPidController.hpp"
#include "okapi/device/abstractMotor.hpp"

namespace okapi {
class AsyncPosPIDController;

class AsyncPosPIDControllerParams : public AsyncPositionControllerParams {
  public:
  AsyncPosPIDControllerParams(const AbstractMotor &imotor, const PosPIDControllerParams &iparams);

  const AbstractMotor &motor;
  const PosPIDControllerParams &params;
};

class AsyncPosPIDController : public AsyncPositionController {
  public:
  AsyncPosPIDController(const AbstractMotor &imotor, const RotarySensor &isensor,
                        const PosPIDControllerParams &iparams);

  AsyncPosPIDController(const AbstractMotor &imotor, const RotarySensor &isensor, const double ikP,
                        const double ikI, const double ikD, const double ikBias = 0);

  virtual ~AsyncPosPIDController();

  /**
   * Sets the target for the controller.
   */
  virtual void setTarget(const double itarget) override;

  /**
   * Returns the last calculated output of the controller. Default is 0.
   */
  double getOutput() const override;

  /**
   * Returns the last error of the controller.
   */
  double getError() const override;

  /**
   * Set time between loops in ms. Default does nothing.
   *
   * @param isampleTime time between loops in ms
   */
  void setSampleTime(const uint32_t isampleTime) override;

  /**
   * Set controller output bounds. Default does nothing.
   *
   * @param imax max output
   * @param imin min output
   */
  void setOutputLimits(double imax, double imin) override;

  /**
   * Resets the controller so it can start from 0 again properly. Keeps configuration from
   * before.
   */
  void reset() override;

  /**
   * Change whether the controll is off or on. Default does nothing.
   */
  void flipDisable() override;

  protected:
  const AbstractMotor &motor;
  const RotarySensor &sensor;
  PosPIDController controller;
  uint32_t prevTime;
  pros::Task task;

  static void trampoline(void *context);
  void step();
};
} // namespace okapi

#endif
