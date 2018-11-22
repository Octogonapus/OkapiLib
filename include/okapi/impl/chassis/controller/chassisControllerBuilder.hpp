/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once

#include "okapi/api/chassis/controller/chassisControllerIntegrated.hpp"
#include "okapi/api/chassis/controller/chassisControllerPid.hpp"
#include "okapi/api/chassis/model/skidSteerModel.hpp"
#include "okapi/api/chassis/model/xDriveModel.hpp"
#include "okapi/api/util/logging.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/device/motor/motor.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include "okapi/impl/device/rotarysensor/integratedEncoder.hpp"
#include "okapi/impl/util/timeUtilFactory.hpp"

namespace okapi {
class ChassisControllerBuilder {
  public:
  /**
   * A builder that creates ChassisControllers. Use this to create your ChassisController.
   */
  ChassisControllerBuilder();

  /**
   * Sets the motors using a skid-steer layout.
   *
   * @param ileft The left motor.
   * @param iright The right motor.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withMotors(const Motor &ileft, const Motor &iright);

  /**
   * Sets the motors using a skid-steer layout.
   *
   * @param ileft The left motor.
   * @param iright The right motor.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withMotors(const MotorGroup &ileft, const MotorGroup &iright);

  /**
   * Sets the motors using a skid-steer layout.
   *
   * @param ileft The left motor.
   * @param iright The right motor.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withMotors(const std::shared_ptr<AbstractMotor> &ileft,
                                       const std::shared_ptr<AbstractMotor> &iright);

  /**
   * Sets the motors using an x-drive layout.
   *
   * @param itopLeft The top left motor.
   * @param itopRight The top right motor.
   * @param ibottomRight The bottom right motor.
   * @param ibottomLeft The bottom left motor.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withMotors(const Motor &itopLeft,
                                       const Motor &itopRight,
                                       const Motor &ibottomRight,
                                       const Motor &ibottomLeft);

  /**
   * Sets the motors using an x-drive layout.
   *
   * @param itopLeft The top left motor.
   * @param itopRight The top right motor.
   * @param ibottomRight The bottom right motor.
   * @param ibottomLeft The bottom left motor.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withMotors(const MotorGroup &itopLeft,
                                       const MotorGroup &itopRight,
                                       const MotorGroup &ibottomRight,
                                       const MotorGroup &ibottomLeft);

  /**
   * Sets the motors using an x-drive layout.
   *
   * @param itopLeft The top left motor.
   * @param itopRight The top right motor.
   * @param ibottomRight The bottom right motor.
   * @param ibottomLeft The bottom left motor.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withMotors(const std::shared_ptr<AbstractMotor> &itopLeft,
                                       const std::shared_ptr<AbstractMotor> &itopRight,
                                       const std::shared_ptr<AbstractMotor> &ibottomRight,
                                       const std::shared_ptr<AbstractMotor> &ibottomLeft);

  /**
   * Sets the sensors. The default sensors are the motor's integrated encoders.
   *
   * @param ileft The left side sensor.
   * @param iright The right side sensor.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withSensors(const ADIEncoder &ileft, const ADIEncoder &iright);

  /**
   * Sets the sensors. The default sensors are the motor's integrated encoders.
   *
   * @param ileft The left side sensor.
   * @param iright The right side sensor.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withSensors(const IntegratedEncoder &ileft,
                                        const IntegratedEncoder &iright);

  /**
   * Sets the sensors. The default sensors are the motor's integrated encoders.
   *
   * @param ileft The left side sensor.
   * @param iright The right side sensor.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withSensors(const std::shared_ptr<ContinuousRotarySensor> &ileft,
                                        const std::shared_ptr<ContinuousRotarySensor> &iright);

  /**
   * Sets the PID controller gains, causing the builder to generate a ChassisControllerPID. Uses the
   * angle controller's gains for the turn controller's gains.
   *
   * @param idistanceGains The distance controller's gains.
   * @param iangleGains The angle controller's gains.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withGains(const IterativePosPIDController::Gains &idistanceGains,
                                      const IterativePosPIDController::Gains &iangleGains);

  /**
   * Sets the PID controller gains, causing the builder to generate a ChassisControllerPID.
   *
   * @param idistanceGains The distance controller's gains.
   * @param iangleGains The angle controller's gains.
   * @param iturnGains The turn controller's gains.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withGains(const IterativePosPIDController::Gains &idistanceGains,
                                      const IterativePosPIDController::Gains &iangleGains,
                                      const IterativePosPIDController::Gains &iturnGains);

  /**
   * Sets the gearset.
   *
   * @param igearset The gearset.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withGearset(const AbstractMotor::GearsetRatioPair &igearset);

  /**
   * Sets the chassis dimensions.
   *
   * @param iscales The dimensions.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withDimensions(const ChassisScales &iscales);

  /**
   * Sets the max velocity. Overrides the max velocity of the gearset.
   *
   * @param imaxVelocity The max velocity.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withMaxVelocity(double imaxVelocity);

  /**
   * Set the max voltage.
   *
   * @param imaxVoltage The max voltage.
   * @return An ongoing builder.
   */
  ChassisControllerBuilder &withMaxVoltage(double imaxVoltage);

  /**
   * Builds the ChassisController. Throws a std::runtime_exception if no motors were set.
   *
   * @return A fully built ChassisController.
   */
  std::shared_ptr<ChassisController> build();

  private:
  Logger *logger;

  struct SkidSteerMotors {
    std::shared_ptr<AbstractMotor> left;
    std::shared_ptr<AbstractMotor> right;
  };

  struct XDriveMotors {
    std::shared_ptr<AbstractMotor> topLeft;
    std::shared_ptr<AbstractMotor> topRight;
    std::shared_ptr<AbstractMotor> bottomRight;
    std::shared_ptr<AbstractMotor> bottomLeft;
  };

  bool hasMotors{false};  // Used to verify motors were passed
  bool isSkidSteer{true}; // Whether to use SkidSteerMotors or XDriveMotors
  SkidSteerMotors skidSteerMotors;
  XDriveMotors xDriveMotors;

  bool sensorsSetByUser{false}; // Used so motors don't overwrite sensors set manually
  std::shared_ptr<ContinuousRotarySensor> leftSensor;
  std::shared_ptr<ContinuousRotarySensor> rightSensor;

  bool hasGains{false}; // Whether gains were passed, no gains means CCI
  IterativePosPIDController::Gains distanceGains;
  IterativePosPIDController::Gains angleGains;
  IterativePosPIDController::Gains turnGains;

  AbstractMotor::GearsetRatioPair gearset = AbstractMotor::gearset::red;
  ChassisScales scales = {1, 1};

  bool maxVelSetByUser{false}; // Used so motors don't overwrite maxVelocity
  double maxVelocity{600};

  double maxVoltage{12000};

  std::shared_ptr<ChassisControllerPID> buildCCPID();
  std::shared_ptr<ChassisControllerIntegrated> buildCCI();
  std::shared_ptr<SkidSteerModel> makeSkidSteerModel();
  std::shared_ptr<XDriveModel> makeXDriveModel();
};
} // namespace okapi
