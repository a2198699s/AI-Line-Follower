#include "ros/ros.h"
#include "rqt_neural_net_control/GetNeuralNetConfig.h"



int main(int argc, char** argv){

	ros::init(argc, argv, "test_node");
	ros::NodeHandle nh;
	
	char topic_name[] = "neural_net_config";
	ros::ServiceClient client = nh.serviceClient<rqt_neural_net_control::GetNeuralNetConfig>(topic_name);

	rqt_neural_net_control::GetNeuralNetConfig srv;
	
	/*============================================================*/
	
	if(client.call(srv)){
		ROS_INFO("Learning Rate: %f\n\r", srv.response.learning_rate);
		ROS_INFO("Loss function: %d\n\r", srv.response.loss_function);
		ROS_INFO("Optimiser: %d\n\r", srv.response.optimiser);
		ROS_INFO("Convolutional Net enabled?: %d\n\r", srv.response.convolutional_net_enabled);
		ROS_INFO("Number of layers: %d\n\r", srv.response.number_of_layers);
		
		for(int i=0; i<srv.response.number_of_layers; i++){
		
			ROS_INFO("Layer %d : Activation %d\n\r", i, srv.response.layer_activations[i]);
		
		}
		
		
	}else{
		ROS_ERROR("FAILED TO CALL THE SERVICE");
		return 1;
	}
	
	return 0;

}
