#pragma comment(lib,"k4a.lib")
#include <stdio.h>
#include <stdlib.h>
#include <k4a/k4a.h>
//#include <k4a/k4a.hpp>
#include <opencv2/opencv.hpp>
#include <Windows.h>


using namespace std;
using namespace cv;

//��Ȼ��cpp�ļ������ǲ��õ���c api
int main()
{
	uint32_t kinect_count = k4a_device_get_installed_count();
	if (kinect_count == 0)
	{
		cout << "δ��⵽AzureKinect" << endl;
		return -1;
	}
	else cout << "AzureKinect����Ϊ" << kinect_count << endl;

	k4a_device_t Kinect_1_device = NULL;
	if (k4a_device_open(K4A_DEVICE_DEFAULT, &Kinect_1_device) != K4A_RESULT_SUCCEEDED)
	{
		cout << "�豸��ʧ��" << endl;
		return -1;
	}
	else cout << "AzureKinect�򿪳ɹ�" << endl;

	k4a_device_configuration_t Kinect_1_config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
	Kinect_1_config.camera_fps		 = K4A_FRAMES_PER_SECOND_30;
	Kinect_1_config.color_resolution = K4A_COLOR_RESOLUTION_720P;
	Kinect_1_config.depth_mode		 = K4A_DEPTH_MODE_OFF;
	Kinect_1_config.color_format	 = K4A_IMAGE_FORMAT_COLOR_BGRA32;

	if (k4a_device_start_cameras(Kinect_1_device, &Kinect_1_config) != K4A_RESULT_SUCCEEDED)
	{
		cout << "��ʼ���ʧ��" << endl;
		return -1;
	}
	else cout << "��ʼ����ɹ�" << endl;

	k4a_capture_t kinect_capture = NULL;

	k4a_image_t color_image;
	Mat color_frame;

	Sleep(1000);
	//�ȴ�1��
	int while_count = 0;
	uint8_t* color_buffer = NULL;

	while (1)
	{
		cout << while_count++ << endl;
		if (k4a_device_get_capture(Kinect_1_device, &kinect_capture, 0)!=K4A_RESULT_SUCCEEDED)
		{
			cout << "��ȡ����ʧ��" << endl;
			return -1;
		}

		color_image = k4a_capture_get_color_image(kinect_capture);

		int color_image_width_pixel = k4a_image_get_width_pixels(color_image);
		int color_image_height_pixel = k4a_image_get_height_pixels(color_image);

		//�������ֳ�ʼ������������
		//����1
		color_frame = Mat(color_image_height_pixel, color_image_width_pixel, CV_8UC4);
		color_frame.data = k4a_image_get_buffer(color_image);

		//����2
		//color_buffer = k4a_image_get_buffer(color_image);
		//color_frame = Mat(color_image_height_pixel, color_image_width_pixel, CV_8UC4, color_buffer);

		imshow("color", color_frame);
		waitKey(30);
	}

	k4a_capture_release(kinect_capture);
	k4a_device_stop_cameras(Kinect_1_device);
	k4a_device_close(Kinect_1_device);
	return 0;
}