#include "rqt_line_sensor_view/LineSensorView.h"

#include <pluginlib/class_list_macros.h>
#include <QString>

namespace linesensorview {

/* ========================================================================== */
/* Constructor/Destructor                                                     */
/* ========================================================================== */

LineSensorView::LineSensorView()
    : rqt_gui_cpp::Plugin(),
      widget_(nullptr) {

  setObjectName("LineSensorView");
}

/* ========================================================================== */
/* Initialize/Shutdown                                                        */
/* ========================================================================== */

void LineSensorView::initPlugin(qt_gui_cpp::PluginContext& context) {
  
  /* Could have a setup UI function... FIXME */
  
  widget_ = new QWidget();
  ui_.setupUi(widget_);
  if (context.serialNumber() > 1) {
    widget_->setWindowTitle(widget_->windowTitle() +
        " (" + QString::number(context.serialNumber()) + ")");
  }
  context.addWidget(widget_);
  
  for(int i=0; i<NUMBER_OF_SENSORS; i++){
    
    led_[i] = new QLed();
    led_[i]->setState(Qt::gray);
    ui_.ledLayout->addWidget(led_[i]);  
    
    displayValue_[i] = new QLineEdit();
    displayValue_[i]->setAlignment(Qt::AlignHCenter);
    displayValue_[i]->clear();
    displayValue_[i]->setText("4096");
    
    ui_.valuesLayout->addWidget(displayValue_[i]);
    
  }
  
  setupROS_();
  
  
}

void LineSensorView::shutdownPlugin() {

  //.shutdown() for publishers and subscribers
  for(int i=0; i<NUMBER_OF_SENSORS; i++){
    valuesSub_[i].shutdown();
  }

}

/* ========================================================================== */
/* Settings                                                                   */
/* ========================================================================== */

void LineSensorView::saveSettings(
    qt_gui_cpp::Settings& plugin_settings,
    qt_gui_cpp::Settings& instance_settings) const {
}

void LineSensorView::restoreSettings(
    const qt_gui_cpp::Settings& plugin_settings,
    const qt_gui_cpp::Settings& instance_settings) {
}

/* ========================================================================== */
/* Methods                                                                    */
/* ========================================================================== */

void LineSensorView::setupROS_(){

    valuesSub_[0] = nh_.subscribe("mybot/left_sensor4/image_raw", 1, &LineSensorView::rawsensorValuesReceived1_, this);
    valuesSub_[1] = nh_.subscribe("mybot/left_sensor3/image_raw", 1, &LineSensorView::rawsensorValuesReceived2_, this);
    valuesSub_[2] = nh_.subscribe("mybot/left_sensor2/image_raw", 1, &LineSensorView::rawsensorValuesReceived3_, this);
    valuesSub_[3] = nh_.subscribe("mybot/left_sensor1/image_raw", 1, &LineSensorView::rawsensorValuesReceived4_, this);
    valuesSub_[4] = nh_.subscribe("mybot/right_sensor1/image_raw", 1, &LineSensorView::rawsensorValuesReceived5_, this);
    valuesSub_[5] = nh_.subscribe("mybot/right_sensor2/image_raw", 1, &LineSensorView::rawsensorValuesReceived6_, this);
    valuesSub_[6] = nh_.subscribe("mybot/right_sensor3/image_raw", 1, &LineSensorView::rawsensorValuesReceived7_, this);
    valuesSub_[7] = nh_.subscribe("mybot/right_sensor4/image_raw", 1, &LineSensorView::rawsensorValuesReceived8_, this);

    //valuesSub_[7] = nh_.subscribe<sensor_msgs/Image>("mybot/right_sensor4/image_raw", 1, boost::bind(&LineSensorView::rawsensorValuesReceived_,this, _1, 7),this);

}

/* ========================================================================== */
/* Events                                                                     */
/* ========================================================================== */



/* ========================================================================== */
/* Callbacks                                                                  */
/* ========================================================================== */
  
void LineSensorView::rawsensorValuesReceived1_(const sensor_msgs::Image::ConstPtr& msg){
    displayValue_[0]->clear();
    displayValue_[0]->setText(QString::number(msg->data[0]));
}
void LineSensorView::rawsensorValuesReceived2_(const sensor_msgs::Image::ConstPtr& msg){
    displayValue_[1]->clear();
    displayValue_[1]->setText(QString::number(msg->data[0]));
}
void LineSensorView::rawsensorValuesReceived3_(const sensor_msgs::Image::ConstPtr& msg){
    displayValue_[2]->clear();
    displayValue_[2]->setText(QString::number(msg->data[0]));
}
void LineSensorView::rawsensorValuesReceived4_(const sensor_msgs::Image::ConstPtr& msg){
    displayValue_[3]->clear();
    displayValue_[3]->setText(QString::number(msg->data[0]));
}
void LineSensorView::rawsensorValuesReceived5_(const sensor_msgs::Image::ConstPtr& msg){
    displayValue_[4]->clear();
    displayValue_[4]->setText(QString::number(msg->data[0]));
}
void LineSensorView::rawsensorValuesReceived6_(const sensor_msgs::Image::ConstPtr& msg){
    displayValue_[5]->clear();
    displayValue_[5]->setText(QString::number(msg->data[0]));
}
void LineSensorView::rawsensorValuesReceived7_(const sensor_msgs::Image::ConstPtr& msg){
    displayValue_[6]->clear();
    displayValue_[6]->setText(QString::number(msg->data[0]));
}
void LineSensorView::rawsensorValuesReceived8_(const sensor_msgs::Image::ConstPtr& msg){
    displayValue_[7]->clear();
    displayValue_[7]->setText(QString::number(msg->data[0]));
}


/* ========================================================================== */
/* Slots                                                                      */
/* ========================================================================== */



/* ========================================================================== */
/* Signals                                                                    */
/* ========================================================================== */



} // namespace

PLUGINLIB_EXPORT_CLASS(linesensorview::LineSensorView,
                       rqt_gui_cpp::Plugin)
