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
		cout << "δ��⵽Kinect" << endl;
		return -1;
	}
	else cout << "AzureKinect����Ϊ" << endl;

	k4a::device Kinect_device = NULL;
	Kinect_device = Kinect_device.open(K4A_DEVICE_DEFAULT);
	cout << "open device" << endl;

	string Kinect_serialnum;
	Kinect_serialnum = Kinect_device.get_serialnum();
	cout << "serialnum is:" << Kinect_serialnum << endl;

	k4a_device_configuration_t Kinect_config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
	Kinect_config.camera_fps = K4A_FRAMES_PER_SECOND_30;
	Kinect_config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
	Kinect_config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
	
	Kinect_device.start_cameras(&Kinect_config);
	cout << "start cameras" << endl;

	k4a::capture capture;
	k4a::image depth_image;
	cv::Mat depth_frame(DEPTH_NOVF_UNBIN_HEIGHT, DEPTH_NOVF_UNBIN_WIDTH, CV_16UC1);
	cv::Mat depth_visual(DEPTH_NOVF_UNBIN_HEIGHT, DEPTH_NOVF_UNBIN_WIDTH, CV_8UC1);
	
	Sleep(1000);
	//Ҳ����ѡ��get capture failed ��ֱ��continue���Ͳ���Ҫ�ȴ�һ��
	int while_count = 0;
	while (1)
	{
		cout << while_count++ << endl;
		if (Kinect_device.get_capture(&capture, std::chrono::milliseconds(0)))
		{
			depth_image = capture.get_depth_image();

			//����1
			const uint16_t *depthData = reinterpret_cast<const uint16_t *>(depth_image.get_buffer());
			depth_frame.data = (uchar*)depthData;
			//���ʻ�������ͼ���м���������
			cout << "depth data [184640]" << depthData[184640] << endl;

			//����2
			//���������������ʾ�����������оͿ��ԣ����ǵڶ����Ǿ��޷����ʻ�����,����1���Է��ʻ�����
			//depth_frame.data = (uchar*)depth_image.get_buffer();
			//cout << "depth data [184640]" << depth_frame.data[184640] << endl;

			depth_frame.convertTo(depth_visual, CV_8U);
			cv::imshow("depth", depth_visual);

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