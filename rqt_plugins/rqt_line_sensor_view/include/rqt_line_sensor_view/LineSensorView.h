#pragma once

#include <rqt_gui_cpp/plugin.h>
#include <rqt_line_sensor_view/ui_LineSensorView.h>
#include "QLed.h"

#include <ros/ros.h>
#include <std_msgs/Int16MultiArray.h>

#include <QWidget>
#include <QObject>
#include <QLineEdit>

#define NUMBER_OF_SENSORS 8

namespace linesensorview {

class LineSensorView : public rqt_gui_cpp::Plugin {
Q_OBJECT

public:

  /* ======================================================================== */
  /* Constructor/Destructor                                                   */
  /* ======================================================================== */

  LineSensorView();

  /* ======================================================================== */
  /* Initialize/Shutdown                                                      */
  /* ======================================================================== */

  void initPlugin(qt_gui_cpp::PluginContext& context) override;

  void shutdownPlugin() override;

  /* ======================================================================== */
  /* Settings                                                                 */
  /* ======================================================================== */

  void saveSettings(qt_gui_cpp::Settings& plugin_settings,
                    qt_gui_cpp::Settings& instance_settings) const override;

  void restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
                       const qt_gui_cpp::Settings& instance_settings) override;

private:

  /* ======================================================================== */
  /* Constants                                                                */
  /* ======================================================================== */

  const std::string TAG = "LineSensorView";

  /* ======================================================================== */
  /* Variables                                                                */
  /* ======================================================================== */

  Ui::LineSensorViewWidget ui_;
  QWidget* widget_;
  QLed* led_[NUMBER_OF_SENSORS];
  QLineEdit* displayValue_[NUMBER_OF_SENSORS];

  ros::NodeHandle nh_;
  ros::Subscriber valuesSub_; 
  ros::Subscriber binvaluesSub_;

  /* ======================================================================== */
  /* Methods                                                                  */
  /* ======================================================================== */
  
  void setupROS_();


  /* ======================================================================== */
  /* Events                                                                   */
  /* ======================================================================== */



  /* ======================================================================== */
  /* Callbacks                                                                */
  /* ======================================================================== */

  void rawsensorValuesReceived_(const std_msgs::Int16MultiArray::ConstPtr& msg);
  void binsensorValuesReceived_(const std_msgs::Int16MultiArray::ConstPtr& msg);

protected slots:

  /* ======================================================================== */
  /* Slots                                                                    */
  /* ======================================================================== */



signals:

  /* ======================================================================== */
  /* Signals                                                                  */
  /* ======================================================================== */



};

} // namespace
