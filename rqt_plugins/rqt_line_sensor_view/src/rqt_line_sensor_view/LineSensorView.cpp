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
  valuesSub_.shutdown();

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

    valuesSub_ = nh_.subscribe("line_sensor_values/raw", 1, &LineSensorView::rawsensorValuesReceived_, this);
    binvaluesSub_ = nh_.subscribe("line_sensor_values/bin", 1, &LineSensorView::binsensorValuesReceived_,this);
}

/* ========================================================================== */
/* Events                                                                     */
/* ========================================================================== */



/* ========================================================================== */
/* Callbacks                                                                  */
/* ========================================================================== */
  
void LineSensorView::rawsensorValuesReceived_(const std_msgs::Int16MultiArray::ConstPtr& msg){
  
  if(msg->data.size()==NUMBER_OF_SENSORS){
      
    for(int i=0; i<NUMBER_OF_SENSORS; i++){
      displayValue_[i]->clear();
      displayValue_[i]->setText(QString::number(msg->data[i]));
    }  
  }
}

void LineSensorView::binsensorValuesReceived_(const std_msgs::Int16MultiArray::ConstPtr& msg){
  
  if(msg->data.size()==NUMBER_OF_SENSORS){
      
    for(int i=0; i<NUMBER_OF_SENSORS; i++){
      
      if(msg->data[i]){
        led_[i]->setState(Qt::black);
      }
      else{
        led_[i]->setState(Qt::white);
      }
    }  
  }
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
