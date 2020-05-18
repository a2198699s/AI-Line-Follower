
#include "../include/image_subscriber_nn/nn_interface.h"
#define SPEED 0.2

int idx = 0;
bool flag = false;
double sensor_weights[4] = {4,3,2,1};
NeuralNetworkInterface *NeuralNetworkInterface::interface=0;

float sensor_values[8];

void NeuralNetworkInterface::sensor_callback(const sensor_msgs::Image::ConstPtr& msg, int index){
	sensor_values[index] = (1-msg->data[0]/255.0);
	idx++;
	if(idx==8){
		idx=0;
		flag = true;
	}else{
		flag = false;
	}
}

void NeuralNetworkInterface::update_sensor_weights(vector<double> weights){
	for (int i=0; i<4; i++){
		sensor_weights[i] = weights[i];
	}
}


float NeuralNetworkInterface::calc_error(){
	float error = 0;
	for (int i=0; i<4; i+=1){
		error += sensor_weights[i] * (sensor_values[7-i] - sensor_values[i]); //Compare pairs of sensor values
	}
	return error;
}

void NeuralNetworkInterface::set_current_interface(NeuralNetworkInterface* subclass){
	interface = subclass;
}

void NeuralNetworkInterface::image_callback(cv_bridge::CvImageConstPtr cv_ptr, bool is_colour){
	
	cv::Mat_<float_t> input_img = cv_ptr->image;
	if (is_colour)
		cvtColor(input_img, input_img, CV_BGR2GRAY);

	if (!input_img.isContinuous())
		input_img = input_img.clone();
	float scale = 1.0/255.0;
	vec_t nn_input;
	transform(input_img.begin(),input_img.end(),back_inserter(nn_input), [=](float_t c) {return 1-(c * scale);}); //normalise input image
	int n = interface->buff_len;
	while(--n!=0 && sensor_values[n]==sensor_values[0]);
	if (n==0){
		interface->send_command(0, SPEED);
		return;
	}
	
	if (sensor_values[1]>(0.2+sensor_values[4]) || sensor_values[0]>(0.2+sensor_values[4])){
		float command = (sensor_values[0]>(0.2+sensor_values[4])) ? -0.7 : -0.4;
		interface->send_command(command, SPEED);
		interface->train_cycle(command,nn_input);
		return;
	}
	else if (sensor_values[6]>(0.2+sensor_values[3]) || sensor_values[7]>(0.2+sensor_values[3])){
		float command = (sensor_values[7]>(0.2+sensor_values[3])) ? 0.7 : 0.4;
		interface->send_command(command, SPEED);
		interface->train_cycle(command,nn_input);
		return;
	}
	
	float command = interface->predict(nn_input);
	command = (command>1) ? 1 : command;
	command = (command<-1) ? -1 : command;
	interface->send_command(command, SPEED);
	if(!interface->start_learning){
		if(interface->buff_idx == interface->buff_len-1){
			interface->start_learning = true;
		}
		interface->output_buffer[interface->buff_idx] = command;
		interface->update_img_buffer(nn_input);
		interface->buff_idx = (interface->buff_idx+1)%interface->buff_len;
		return;
	}
	
	flag = false;
	interface->train_cycle(command,nn_input);
	
}

void NeuralNetworkInterface::train_cycle(float command, vec_t nn_input){
	if (this->start_learning){
			flag = false;
			float error = calc_error();
			cout<<error<<endl;
			this->publish_error(abs(error));
			this->publish_command(command);
			this->train(error, 3);

			this->output_buffer[this->buff_idx] = command;
			this->update_img_buffer(nn_input);
			this->buff_idx = (this->buff_idx+1)%this->buff_len;
	}
}
	
void NeuralNetworkInterface::send_command(float command, float speed){
	geometry_msgs::Twist motors_msg;
	motors_msg.linear.x = speed;
	motors_msg.angular.z = command;
	this->publish_motor(motors_msg);
	
}

auto cbtime = std::chrono::high_resolution_clock::now();
bool started = false;
void callback_img_test(const sensor_msgs::ImageConstPtr& msg){
	auto finish = std::chrono::high_resolution_clock::now();
	if (started){
		std::chrono::duration<double> elapsed = finish -cbtime;
		cout << "Time: " << elapsed.count() <<endl;
	}else{
		started = true;
	}
	cbtime = finish;
}

	

