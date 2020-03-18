
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<cstdlib>
#include<fstream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void change_to_binary(char in, char binary_arrry[60],int &index) {

	int t = 0;
	int Gx[5] = { 1,0,0,1,1 };//Gx=10011
	int code[12] = { 0 };
	int temp_char = (int)in;
	for (int i = 7; temp_char != 0; i--)
	{
		code[i] = temp_char % 2;
		temp_char = temp_char / 2;
	}
	int copy_code[12];
	for (int i = 0; i <= 11; i++)copy_code[i] = code[i];
	for (int i = 0; i <= 7; i++)
	{
		if (copy_code[i] == 1)
		{
			for (int k = 0; k <= 4; k++)
			{
				if (copy_code[i + k] != Gx[k])copy_code[i + k] = 1;
				else copy_code[i + k] = 0;
			}
		}
	}
	for (int i = 8; i <= 11; i++)
	{
		code[i] = copy_code[i];
	}
	for (int i = (index % 5) * 12; i <= (index % 5) * 12 + 11; i++)
	{
		binary_arrry[i] = code[i- (index % 5) * 12] + '0';
	}
	index++;
	return;
}

void draw_ROI(Mat& erweima)
{
	//����������λ��
	Point center = Point(10, 10);
	Point start = Point(115, 115);
	rectangle(erweima, start, center, Scalar(0, 0, 0), FILLED);
	center = Point(25, 25);
	start = Point(100, 100);
	rectangle(erweima, start, center, Scalar(255, 255, 255), FILLED);
	center = Point(40, 40);
	start = Point(85, 85);
	rectangle(erweima, start, center, Scalar(0, 0, 0), FILLED);
	center = Point(435, 10);
	start = Point(540, 115);
	rectangle(erweima, start, center, Scalar(0, 0, 0), FILLED);
	center = Point(450, 25);
	start = Point(525, 100);
	rectangle(erweima, start, center, Scalar(255, 255, 255), FILLED);
	center = Point(465, 40);
	start = Point(510, 85);
	rectangle(erweima, start, center, Scalar(0, 0, 0), FILLED);
	center = Point(10, 435);
	start = Point(115, 540);
	rectangle(erweima, start, center, Scalar(0, 0, 0), FILLED);
	center = Point(25, 450);
	start = Point(100, 525);
	rectangle(erweima, start, center, Scalar(255, 255, 255), FILLED);
	center = Point(40, 465);
	start = Point(85, 510);
	rectangle(erweima, start, center, Scalar(0, 0, 0), FILLED);
}
bool makingvideo(string yuan_file, string mudi_file)
{
	using namespace cv;
	
	ifstream read_file(yuan_file);//��.txt�ļ�
	
	Mat my_qrcode(550, 550, CV_8UC3, Scalar(255, 255, 255));
	int locate = 125;//��¼���
	char binary[60];//һ���е�binary
	for (int i = 0; i < 60; i++)
		binary[i] = '0';
	int line = 0;
	int img_index = 1;//��¼�˶��˵ڼ���ͼƬ
	Point left_upper;
	Point upper_right;
	//��ʼ֡
	draw_ROI(my_qrcode);
	imwrite(mudi_file + "/0.bmp", my_qrcode);
	int temp_index = 0;//���ڼ�¼���˼�����ĸ
	while (!read_file.eof())
	{//roopstart
		string tmp;
		getline(read_file, tmp);
		//����������λ��
		draw_ROI(my_qrcode);
		//���bit��Ϣ
		for (unsigned int i = 0; i <= tmp.length() - 1; i++)
		{//stringstate
			char temp_read=tmp[i];//�������ַ�
			change_to_binary(temp_read, binary,temp_index);//���������ַ�תΪ�����ƣ��ѱ��浽����





			if (temp_index % 5 == 0) {//��һ�оʹ�ӡ����ά��
				for (int i = 0; i < 60; i++)
				{
					left_upper = Point(locate + i * 5, locate + line * 5);
					upper_right = Point(locate + i * 5 + 5, locate + line * 5 + 5);
					/*rectangle(src, start, center, Scalar(0, 0, 0), FILLED);*/
					if (binary[i] == '1')rectangle(my_qrcode, left_upper, upper_right, Scalar(0, 0, 0), FILLED);//�ڱ�ʾ1
					if (binary[i] == '0')rectangle(my_qrcode, left_upper, upper_right, Scalar(255, 255, 255), FILLED);//�ױ�ʾ0
				}
				for (int i = 0; i <= 59; i++)binary[i] = '0';//��ӡ�������ʼ������
				line++;//����һ��
			}
			if (line % 60 == 0 && line != 0)//��ʮ���˾ͱ���
			{
				char file_name[10];
				sprintf_s(file_name, "%d", img_index);
				imwrite(mudi_file + "/" + file_name + ".bmp", my_qrcode);
				my_qrcode = Mat(550, 550, CV_8UC3, Scalar(255, 255, 255));
				draw_ROI(my_qrcode);
				img_index++;
				line = 0;
			}


			//for (int i = 0; i < 64; i++)
			//{
			//	left_upper = Point(locate + i * 5, locate + line * 5);
			//	upper_right = Point(locate + i * 5 + 5, locate + line * 5 + 5);
			//	/*rectangle(src, start, center, Scalar(0, 0, 0), FILLED);*/
			//	if (binary[i] == '1')rectangle(my_qrcode, left_upper, upper_right, Scalar(0, 0, 0), FILLED);//�ڱ�ʾ1
			//	if (binary[i] == '0')rectangle(my_qrcode, left_upper, upper_right, Scalar(255, 255, 255), FILLED);//�ױ�ʾ0
			//}
			//line++;
			//if (line % 64 == 0)
			//{
			//	char file_name[10];
			//	sprintf(file_name, "%d", index);
			//	imwrite(mudi_file + "/" + file_name + ".bmp", my_qrcode);
			//	my_qrcode = Mat(570, 570, CV_8UC3, Scalar(255, 255, 255));
			//	draw_ROI(my_qrcode);
			//	index++;
			//	line = 0;
			//}
			//for (int i = 0; i < 64; i++)
			//{
			//	binary[i] = '0';
			//}
		}//stringend
		
	}//roopend
	//����֡
	if (line % 60 != 0)
	{
		if (temp_index % 5 != 5)
		{
			for (int i = 0; i < 60; i++)
			{
				left_upper = Point(locate + i * 5, locate + line * 5);
				upper_right = Point(locate + i * 5 + 5, locate + line * 5 + 5);
				/*rectangle(src, start, center, Scalar(0, 0, 0), FILLED);*/
				if (binary[i] == '1')rectangle(my_qrcode, left_upper, upper_right, Scalar(0, 0, 0), FILLED);//�ڱ�ʾ1
				if (binary[i] == '0')rectangle(my_qrcode, left_upper, upper_right, Scalar(255, 255, 255), FILLED);//�ױ�ʾ0
			}
		}
		char file_name[10];
		sprintf_s(file_name, "%d", img_index);
		imwrite(mudi_file + "/" + file_name + ".bmp", my_qrcode);
		img_index++;
	}
	for (int j = 0; j < 2; ++j)
	{
		char file_name[10];
		sprintf_s(file_name, "%d", img_index);
		my_qrcode = Mat(570, 570, CV_8UC3, Scalar(255, 255, 255));
		draw_ROI(my_qrcode);
		imwrite(mudi_file + "/" + file_name + ".bmp", my_qrcode);
		img_index += 1;
	}
	//const char* stdpath = mudi_file.c_str();
	//char* ffmpegpath = "./ffmpeg.exe"; //ios c++���Կ���c_str()����
	//char* jpg = "/%d.bmp";
	//char* mp4 = "/output.mp4";
	//char cmdcomand[100];
	//sprintf(cmdcomand, "%s -f image2 -r 10 -i %s%s -vcodec mpeg4 %s%s", ffmpegpath, stdpath, jpg, stdpath, mp4);
	//WinExec(cmdcomand, SW_SHOW);
	/* const char* result="./ffmpeg.exe -f image2 -r 10 -i "+stdpathname+"/%d.jpg -vcodec mpeg4 "+stdpathname+"/output.mp4";*/
	/* system(result);//�����������ffmpeg��ͼ��convert��Ƶ */
	return true;
}
int main()
{
	makingvideo("F:\\photo\\photo\\shuru.txt", "F:\\photo\\photo");
	waitKey(0);
	return 0;



}