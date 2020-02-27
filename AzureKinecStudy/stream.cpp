#pragma comment(lib,"k4a.lib")
#include <stdio.h>
#include <stdlib.h>
#include <k4a/k4a.h>
//#include <k4a/k4a.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//虽然是cpp文件，但是采用的是c api
int main()
{
	uint32_t kinect_count = k4a_device_get_installed_count();
	if (kinect_count == 0)
	{
		cout << "未检测到AzureKinect" << endl;
		return;
	}
	else cout << "AzureKinect个数为" << kinect_count << endl;

	k4a_device_t Kinect_1_device = NULL;
	if (k4a_device_open(K4A_DEVICE_DEFAULT, &Kinect_1_device) != K4A_RESULT_SUCCEEDED)
	{
		cout << "设备打开失败" << endl;
		return;
	}
	else cout << "AzureKinect打开成功" << endl;

	k4a_device_configuration_t Kinect_1_config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
	Kinect_1_config.camera_fps		 = K4A_FRAMES_PER_SECOND_30;
	Kinect_1_config.color_resolution = K4A_COLOR_RESOLUTION_720P;
	Kinect_1_config.depth_mode		 = K4A_DEPTH_MODE_WFOV_UNBINNED;

	if (k4a_device_start_cameras(Kinect_1_device, &Kinect_1_config) != K4A_RESULT_SUCCEEDED)
	{
		cout << "开始相机失败" << endl;
		return;
	}
	else cout << "开始相机成功" << endl;


	k4a_image_t color_image;
	k4a_image_t depth_image;
	k4a_image_t ir_image;

	k4a_capture_t kinect_capture;

	Mat color_frame;
	Mat depth_frame;
	Mat ir_frame;

	while (1)
	{
		if (k4a_device_get_capture(Kinect_1_device, &kinect_capture, 0)!=K4A_RESULT_SUCCEEDED)
		{
			cout << "获取捕获失败" << endl;
			return;
		}

		color_image = k4a_capture_get_color_image(kinect_capture);
		depth_image = k4a_capture_get_depth_image(kinect_capture);
		ir_image = k4a_capture_get_ir_image(kinect_capture);

		color_frame
	}




	k4a_capture_release(kinect_capture);
	k4a_device_stop_cameras(Kinect_1_device);
	k4a_device_close(Kinect_1_device);
	return 0;
}