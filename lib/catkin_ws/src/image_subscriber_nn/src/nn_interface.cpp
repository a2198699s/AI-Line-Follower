
#include "../include/image_subscriber_nn/nn_interface.h"
#define SPEED 0.2

int idx = 0;
bool flag = false;
//std::mutex sensor_mtx;
//std::condition_variable cond_v;
int sensor_weights[3] = {3,2,1};
gradient_descent opt;

float sensor_values[8];
void NeuralNetworkInterface::construct_cnn() {
    //network<sequential> net;
    float_t epsilon = 1.0;
    this->newcnn << conv(9, 9, 3, 1, 3) << relu() // 3 feature maps: forward, left, right
        << max_pool(7, 7, 3, 2) << relu() // in:28x28x6, 2x2pooling
        << fc(3 * 3 * 3, 12) << relu()   // in:14x14x6, out:120
        << fc(12, 1) << lrelu(epsilon);   //No support for linear activation - uses leaky relu with unit gradient instead
    assert(this->newcnn.in_data_size() == 9 * 9);
    //cout << this->newcnn.in_data_size() << endl;
    assert(this->newcnn.out_data_size() == 1);
    
    
    //this->optimiser = opt;
    //this->newcnn = net;
}

void NeuralNetworkInterface::sensor_callback(const sensor_msgs::Image::ConstPtr& msg, int index){
	//std::shared_lock<std::mutex> lck(sensor_mtx);
	sensor_values[index] = (1-msg->data[0]/255.0);
	//TODO have a better way to check for recpetion of all sensor values...
	idx++;
	if(idx==8){
		//cout<<"sens"<<endl;
		idx=0;
		flag = true;
		cout << "Sensor values: "<<sensor_values[0] <<" " <<sensor_values[1] <<" "<<sensor_values[2] <<" "<<sensor_values[3] <<" "<<sensor_values[4] <<" "<<sensor_values[5] <<" "<<sensor_values[6] <<" "<<sensor_values[7] << endl;
		//cond_v.notify_all();
	}else{
		flag = false;
	}
}


void callback0(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 0);}
void callback1(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 1);}
void callback2(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 2);}
void callback3(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 3);}
void callback4(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 4);}
void callback5(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 5);}
void callback6(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 6);}
void callback7(const sensor_msgs::Image::ConstPtr& msg){NeuralNetworkInterface::sensor_callback(msg, 7);}


float NeuralNetworkInterface::calc_error(){
	//while (!flag){}; //TODO: Change from busy waiting
	//std::shared_lock<std::mutex> lck(sensor_mtx);
	//while(!flag){} ;//cond_v.wait(lck);
	float error = sensor_values[4] - sensor_values[3]; //Compare two central sensor values
	for (int i=0; i<3; i+=1){
		error -= sensor_weights[i] * sensor_values[i]; //Negative values for turn left
		error += sensor_weights[i] * sensor_values[7-i]; //Positive values for turn right
	}
	//this->sensor_values[]; // 3 and 4 are central sensors
	return error;
}

//vec_t nn_input;
//nn_input.push_back(val);
void NeuralNetworkInterface::image_callback(const sensor_msgs::ImageConstPtr& msg){
	//cout<<"c"<<endl;
	//auto start = std::chrono::high_resolution_clock::now();
	cv_bridge::CvImageConstPtr cv_ptr;
	try{
		if (enc::isColor(msg->encoding))
			cv_ptr = cv_bridge::toCvShare(msg, enc::RGB8);
		else
			cv_ptr = cv_bridge::toCvShare(msg, enc::MONO8);
	}
	catch(cv_bridge::Exception& e){
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}
	
	cv::Mat_<float_t> input_img = cv_ptr->image;
	if (enc::isColor(msg->encoding))
		cvtColor(input_img, input_img, CV_BGR2GRAY);
	
	//input_img.convertTo(input_img, CV_64F);
	if (!input_img.isContinuous())
		input_img = input_img.clone();
	//imwrite("LinefollowInput.jpg", input_img);
	float scale = 1.0/255.0;
	vec_t nn_input;
	transform(input_img.begin(),input_img.end(),back_inserter(nn_input), [=](float_t c) {return 1-(c * scale);});
	/*cout << "Input values: ";
	for(int i=0; i<81;i++){
		if(i%9==0)
			cout<<endl;
		cout<<" "<<nn_input[i];
	}
	cout<<endl;
	*/
	//cout << "Input values: "<<nn_input[0] <<" " <<nn_input[1] <<" "<<nn_input[2] <<" "<<nn_input[3] <<" "<<nn_input[4] <<" "<<nn_input[5] <<" "<<nn_input[6] <<" "<<nn_input[7] << endl;
	//int rows = input_img.rows;
	//int cols = input_img.cols;
	
	//tiny_dnn::float_t *ptr = input_img.ptr<tiny_dnn::float_t>(0);
	//tiny_dnn::vec_t out_vector = tiny_dnn::vec_t(ptr, ptr+rows*cols);
	//double *nn_image = input_img.ptr<double>(0);
	//cout << typeid(this->newcnn.predict(nn_input)[0]).name()<<endl;
	
	if (sensor_values[1]>0.1 || sensor_values[0]>0.1){
		send_command(-1, SPEED);
		cout << "edgel"<<endl;
		return;
	}
	else if (sensor_values[6]>0.1 || sensor_values[7]>0.1){
		send_command(1, SPEED);
		cout << "edger"<<endl;
		return;
	}
	
	//this->output_buffer[this->buffer_idx] = command;
	float command = this->newcnn.predict(nn_input)[0];
	this->send_command(command, SPEED);
	
	
	if(!start_learning){
		if(this->buff_idx == 2){
			start_learning = true;
		}
		this->output_buffer[this->buff_idx] = command;
		this->image_buffer[this->buff_idx] = nn_input;
		this->buff_idx = (this->buff_idx+1)%3;
		return;
	}
	
	
	//cout<<"Command: " << command <<endl;
	
	//wait for sensors to be over the place that the camera last saw. 0.165m at 0.2m/s. wait 0.825s
	//wait(16.5
	//cout << "Sensor values: "<<sensor_values[0] <<" " <<sensor_values[1] <<" "<<sensor_values[2] <<" "<<sensor_values[3] <<" "<<sensor_values[4] <<" "<<sensor_values[5] <<" "<<sensor_values[6] <<" "<<sensor_values[7] << endl;
	
	flag = false;
	float error = calc_error();
	cout << "Command: "<<command<<" Label: " << command + error <<endl;
	vec_t label_vec;
	vector<vec_t> input_image {{image_buffer[this->buff_idx]}};
	//cout<< "label: "<< (command+error) << endl;
	label_vec.push_back(this->output_buffer[this->buff_idx]+error);
	vector<vec_t> input_label {{label_vec}};
	size_t batch_size = 1;
	/*cout<<"sizes:"<<endl;
	cout<<input_image.size()<<endl;
	cout<<input_image[0].size()<<endl;
	cout<<input_label.size()<<endl;
	cout<<input_label[0][0]<<endl;
	*/
	this->newcnn.fit<mse>(opt, input_image, input_label, batch_size, 3);

	this->output_buffer[this->buff_idx] = command;
	this->image_buffer[this->buff_idx] = nn_input;
	this->buff_idx = (this->buff_idx+1)%3;
	/*
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish -start;
	cout<<"Time: " <<elapsed.count()<<endl;
	*/
	//double *nn_image = input_img.ptr<double>(0);
	/*	
	this->neural_net->setInputs(nn_image);
	this->neural_net->propInputs();
	this->neural_net->setLocalError(0);
	this->neural_net->propGlobalErrorBackwardLocally();
	*/
}
	
void NeuralNetworkInterface::send_command(float command, float speed){
	cout<<"COMMAND: " << command <<endl;
	geometry_msgs::Twist motors_msg;
	motors_msg.linear.x = speed;
	motors_msg.angular.z = command;
	this->motor_pub.publish(motors_msg);
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
	
int main(int argc, char **argv){
	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	ros::Subscriber sub[8];
	/*
	int layers = 4;
	int neurons[layers] = {81,40,10,1};
	int nInputs = 81;
	double learning_rate = 0.001;
	Net* neural_net = new Net(layers, neurons, nInputs);
	neural_net->initNetwork(Neuron::W_ONES, Neuron::B_NONE, Neuron::Act_Sigmoid);
	neural_net->setLearningRate(learning_rate);
	*/
	ros::Publisher motors_pub = n.advertise<geometry_msgs::Twist>("mybot/cmd_vel", 1);
	NeuralNetworkInterface* interface = new NeuralNetworkInterface(motors_pub);//neural_net
	interface->construct_cnn();
	image_transport::ImageTransport it(n);
	image_transport::Subscriber img_sub = it.subscribe("/mybot/camera1/image_raw", 1, &NeuralNetworkInterface::image_callback, interface); //&NeuralNetworkInterface::image_callback, interface
	
	sub[0] = n.subscribe("mybot/left_sensor4/image_raw", 1, callback0);
	sub[1] = n.subscribe("mybot/left_sensor3/image_raw", 1, callback1);
	sub[2] = n.subscribe("mybot/left_sensor2/image_raw", 1, callback2);
	sub[3] = n.subscribe("mybot/left_sensor1/image_raw", 1, callback3);
	sub[4] = n.subscribe("mybot/right_sensor1/image_raw", 1, callback4);
	sub[5] = n.subscribe("mybot/right_sensor2/image_raw", 1, callback5);
	sub[6] = n.subscribe("mybot/right_sensor3/image_raw", 1, callback6);
	sub[7] = n.subscribe("mybot/right_sensor4/image_raw", 1, callback7);
	
	ros::Rate r(60);
	ros::spin();
	return 1;
	/*
	ros::Rate loop_rate(60);
	while(ros::ok()){
		if(flag){
			flag = false;
			geometry_msgs::Twist motors_msg;
			//calculateMotorSpeeds(motors_msg);
			//motors_msg.linear.y = 100.0;
			motors_msg.linear.x = 0.2;
			motors_msg.angular.z = interface->command;
			motors_pub.publish(motors_msg);
		}
	
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
	*/
}
