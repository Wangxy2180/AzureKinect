#include <k4a/k4a.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <Windows.h>

#define DEPTH_NOVF_2X2BIN_HEIGHT 288
#define DEPTH_NOVF_2X2BIN_WIDTH 320

#define DEPTH_NOVF_UNBIN_HEIGHT 576
#define DEPTH_NOVF_UNBIN_WIDTH 640

using namespace std;

int main()
{
	uint32_t Kinect_count = k4a::device::get_installed_count();
	if (Kinect_count == 0)
	{
		cout << "未检测到Kinect" << endl;
		return -1;
	}
	else cout << "AzureKinect个数为" << endl;

	k4a::device Kinect_device = NULL;
	Kinect_device = Kinect_device.open(K4A_DEVICE_DEFAULT);
	cout << "open device" << endl;

	string Kinect_serialnum;
	Kinect_serialnum = Kinect_device.get_serialnum();
	cout << "serialnum is:" << Kinect_serialnum << endl;

	k4a_device_configuration_t Kinect_config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
	Kinect_config.camera_fps = K4A_FRAMES_PER_SECOND_30;
	Kinect_config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;

	Kinect_device.start_cameras(&Kinect_config);
	cout << "start cameras" << endl;

	k4a::capture capture;
	k4a::image ir_image;
	cv::Mat ir_frame(DEPTH_NOVF_UNBIN_HEIGHT, DEPTH_NOVF_UNBIN_WIDTH, CV_16UC1);
	cv::Mat ir_visual(DEPTH_NOVF_UNBIN_HEIGHT, DEPTH_NOVF_UNBIN_WIDTH, CV_8UC1);

	Sleep(1000);
	//也可以选择get capture failed 后直接continue，就不需要等待一秒
	int while_count = 0;
	while (1)
	{
		cout << while_count++ << endl;
		if (Kinect_device.get_capture(&capture, std::chrono::milliseconds(0)))
		{
			ir_image = capture.get_ir_image();

			//代码1
			const uint16_t *irData = reinterpret_cast<const uint16_t *>(ir_image.get_buffer());
			ir_frame.data = (uchar*)irData;
			//访问缓冲区，图像中间的ir数据，最大65535
			cout << "depth data [184640]" << irData[184640] << endl;

			cv::imshow("ir_visual", ir_visual);
			cv::imshow("ir_frame", ir_frame);

			if (cv::waitKey(30) == 'q')
			{
				Kinect_device.stop_cameras();
				Kinect_device.close();
				break;
			}
		}
		else cout << "get capture failed" << endl;
	}

	return 0;
}