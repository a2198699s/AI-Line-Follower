#pragma once

#include <rqt_gui_cpp/plugin.h>
#include <rqt_line_sensor_view/ui_LineSensorView.h>
#include "QLed.h"

#include <ros/ros.h>
#include <sensor_msgs/Image.h>

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
  ros::Subscriber valuesSub_[NUMBER_OF_SENSORS];


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

  //TODO find a way of only using one function
  //https://answers.ros.org/question/63991/how-to-make-callback-function-called-by-several-subscriber/?answer=63998#post-id-63998 ... tried this but doesn't work :(
  void rawsensorValuesReceived1_(const sensor_msgs::Image::ConstPtr& msg);
  void rawsensorValuesReceived2_(const sensor_msgs::Image::ConstPtr& msg);
  void rawsensorValuesReceived3_(const sensor_msgs::Image::ConstPtr& msg);
  void rawsensorValuesReceived4_(const sensor_msgs::Image::ConstPtr& msg);
  void rawsensorValuesReceived5_(const sensor_msgs::Image::ConstPtr& msg);
  void rawsensorValuesReceived6_(const sensor_msgs::Image::ConstPtr& msg);
  void rawsensorValuesReceived7_(const sensor_msgs::Image::ConstPtr& msg);
  void rawsensorValuesReceived8_(const sensor_msgs::Image::ConstPtr& msg);

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
