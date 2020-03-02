#include <k4a/k4a.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <Windows.h>

#define COLOR_HEIGHT_720P 720
#define COLOR_WIDTH_720P 1280

#define DEPTH_NOVF_2X2BIN_HEIGHT 288
#define DEPTH_NOVF_2X2BIN_WIDTH 320

#define DEPTH_NOVF_UNBIN_HEIGHT 576
#define DEPTH_NOVF_UNBIN_WIDTH 640

//WOVFģʽ��֧��30fps
#define DEPTH_WOVF_2X2BIN_HEIGHT 512
#define DEPTH_WOVF_2X2BIN_WIDTH 512

#define DEPTH_WOVF_UNBIN_HEIGHT 1024
#define DEPTH_WOVF_UNBIN_WIDTH 1024


using namespace std;

int main()
{
	uint32_t Kinect_count = k4a::device::get_installed_count();
	if (Kinect_count == 0)
	{
		cout << "δ����Kinect" << endl;
	}
	else cout << "AzureKinect �����ǣ�" << Kinect_count << endl;

	//����Kinect����
	//color_formatĬ��MJPG������OpenCV��BGRA�����ٷ���˵����BGRA������CPU����
	k4a_device_configuration_t Kinect_1_config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
	Kinect_1_config.camera_fps = K4A_FRAMES_PER_SECOND_30;
	Kinect_1_config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
	Kinect_1_config.color_resolution = K4A_COLOR_RESOLUTION_720P;
	Kinect_1_config.depth_mode = K4A_DEPTH_MODE_OFF;

	k4a::device Kinect_1_device = NULL;

	//���������ֶ����Դ�
	Kinect_1_device = k4a::device::open(K4A_DEVICE_DEFAULT);
	//Kinect_1_device = Kinect_1_device.open(K4A_DEVICE_DEFAULT);
	cout << "open Kinect" << endl;

	string Kinect_1_serialnum;
	Kinect_1_serialnum = Kinect_1_device.get_serialnum();
	cout << "Kinect���к��ǣ�" << Kinect_1_serialnum << endl;

	Kinect_1_device.start_cameras(&Kinect_1_config);
	cout << "start cameras" << endl;

	k4a::capture capture;
	k4a::image color_image;
	/*
	//����޷�Ԥ��ȷ���ֱ��ʣ�������ѭ���в���
	//colorFrame = cv::Mat(colorImage.get_height_pixels(), colorImage.get_width_pixels(), CV_8UC4);
	//�����ķ���ȥ����ʼ��
	*/
	cv::Mat color_frame(COLOR_HEIGHT_720P,COLOR_WIDTH_720P,CV_8UC4);

	Sleep(1000);//����1�룬����̫��ᵼ��ǰ�ڳ��� get capture failed
	int while_count = 0;//ѭ������
	while (1)
	{
		cout << while_count++ << endl;
	
		//û̫�����״�����timeout������
		//Kinect_1_device.get_capture(&capture);
		if (Kinect_1_device.get_capture(&capture, std::chrono::milliseconds(0)))
		{
			color_image = capture.get_color_image();
			color_frame.data = color_image.get_buffer();
			cv::imshow("Azure KInect color", color_frame);
			if (cv::waitKey(30) == 'q')
			{
				Kinect_1_device.close();
				break;
			}
		}
		else cout << "get capture failed" << endl;
	}
	return 0;
}