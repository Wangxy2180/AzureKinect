#pragma comment(lib,"k4a.lib")

#include <k4a/k4a.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	//获取连接的Kinect设备数
	int Kinect_count = k4a_device_get_installed_count();
	if (Kinect_count == 0)
	{
		printf("AzureKinect尚未连接至设备\n");
		return;
	}
	else printf("AzureKInect设备数为：%d", Kinect_count);

	//打开Kinect设备
	k4a_device_t Kinect_1 = NULL;
	k4a_device_open(K4A_DEVICE_DEFAULT, Kinect_1);

	//获取序列号，确保能用
	//先获取序列号size，再申请空间
	size_t serial_number_size = 0;
	k4a_device_get_serialnum(Kinect_1, NULL, &serial_number_size);

	char* serial_number = (char*)malloc(serial_number_size);
	k4a_device_get_serialnum(Kinect_1, serial_number, &serial_number_size);
	printf("序列号为%s\n", serial_number);
	free(serial_number);

	//进行相机配置
	k4a_device_configuration_t Kinect_1_config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
	Kinect_1_config.color_resolution = K4A_COLOR_RESOLUTION_720P;
	Kinect_1_config.camera_fps		 = K4A_FRAMES_PER_SECOND_30;

	//根据给定配置打开箱机
	k4a_device_start_cameras(Kinect_1, &Kinect_1_config);

	//这其中开始对其进行各种处理

	//关闭摄像机和设备
	k4a_device_stop_cameras(Kinect_1);
	k4a_device_close(Kinect_1);
}
