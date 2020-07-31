#ifndef IGL_VIEWER_WITH_NANOGUI
#include <iostream>
int main()
{
  std::cerr<<
    "Error: recompile with LIBIGL_VIEWER_WITH_NANOGUI defined."<<std::endl;
  return EXIT_FAILURE;
}
#else

#include <igl/readOFF.h>
#include <igl/viewer/Viewer.h>
#include <igl/list_to_matrix.h>
#include <nanogui/formhelper.h>
#include <nanogui/screen.h>
#include <iostream>
#include "tutorial_shared_path.h"
#include <sstream> 

//����ͨ������ͷ�ļ�
#include "SerialPort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//opencv�����������ͷ�ļ�
#define  _CRT_SECURE_NO_WARNINGS
#include <opencv2/core/core.hpp> 
#include<opencv2/highgui/highgui.hpp>  
#include"opencv2/imgproc/imgproc.hpp"  
#include<fstream>
#include<ostream>

//libigl��ʾ��������ͷ�ļ�
#include <vector>        
#include <algorithm>      
#include <iomanip>       

using namespace cv;
using namespace std;

//opencv����������趨��
Mat SrcImage;
Mat GrayImage;
Mat BinaryImage;

//����ͨ�����趨��
char* portName = "\\\\.\\COM3";
#define MAX_DATA_LENGTH 255

//Control signals for turning on and turning off the led
//Check arduino code
char ON[] = "ON\n";

//Arduino SerialPort object
SerialPort *arduino;

//�����ؽ� readOFF()��������
Eigen::MatrixXd V;
Eigen::MatrixXi F;
vector<vector<double>> VVV;
vector<double>::iterator it;

void to_GrayImage()
{
	//������ԭͼͬ���ͺ�ͬ��С�ľ���
	GrayImage.create(SrcImage.size(), SrcImage.type());
	//��ԭͼת��Ϊ�Ҷ�ͼ��
	cvtColor(SrcImage, GrayImage, CV_BGR2GRAY);

	namedWindow("�Ҷ�ͼ");
	imshow("�Ҷ�ͼ", GrayImage);
	
	int rowNumber = GrayImage.rows;
	int colNumber = GrayImage.cols;
	
	int j;
	for (int i = 0; i < rowNumber; i++)
	{
		uchar *a = GrayImage.ptr<uchar>(i);
		bool flag = false;
		int count = 0;
		for (j = 0; j < colNumber; j++)
		{
			if (a[j] == 255)
			{
				count++;
				flag = true;
			}
			else
			{
				if (flag)	break;
			}
		}
	}
}

int photo1()			//��һ��ɨ��
{
	Mat  result, frame, img0, img1;

	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		return -1;
	}
	char filename[200];
	int cnt = 0;
	int delay = 60;
	char file[200];
	sprintf(file, "D://SD_DIY//Photo1//test.txt");
	ofstream output(file);
	for (int u = 0; u < 280; u++)
	{
		Mat imag;
		cap >> imag;
		imshow("video", imag);
		sprintf(filename, "D:\\SD_DIY\\Photo1\\pic%d.jpg", ++cnt);
		imwrite(filename, imag);
		char buf[100];
		img0 = imread("D:\\SD_DIY\\Photo1\\pic" + std::string(_itoa(cnt, buf, 10)) + ".jpg", 0);
		//imshow("show", imag);
		namedWindow("ԭͼ");
		imshow("ԭͼ", img0);
		result = img0.clone();
		threshold(img0, result, 200, 255, CV_THRESH_BINARY);
		namedWindow("��ֵ��ͼ��");
		imshow("��ֵ��ͼ��", result);
		
		int rowNumber = result.rows;
		int colNumber = result.cols;
		//vector<pair<int, int>> position;
		int j;
		for (int i = 0; i < rowNumber; i++)
		{
			uchar *a = result.ptr<uchar>(i);
			bool flag = false;
			int count = 0;
			for (j = 0; j < colNumber; j++)
			{
				if (a[j])
				{
					count++;
					flag = true;
				}
				else
				{
					if (flag)
					{
						output << i << "," << ((j - count) + j) / 2 << "\n";
						break;
					}
				}
			}
		}
		//waitKey(delay);
		output << "******" << "\n";
	}
	output.close();
}
int photo2()				//�ڶ���ɨ��
{
	Mat  result, frame, img0, img1;

	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		return -1;
	}
	char filename[200];
	int cnt = 0;
	int delay = 60;
	char file[200];
	sprintf(file, "D://SD_DIY//Photo2//test.txt");
	ofstream output(file);
	for (int u = 0; u < 280; u++)
	{
		Mat imag;
		cap >> imag;
		imshow("video", imag);
		sprintf(filename, "D:\\SD_DIY\\Photo2\\pic%d.jpg", ++cnt);
		imwrite(filename, imag);
		char buf[100];
		img0 = imread("D:\\SD_DIY\\Photo2\\pic" + std::string(_itoa(cnt, buf, 10)) + ".jpg", 0);
		//imshow("show", imag);
		namedWindow("ԭͼ");
		imshow("ԭͼ", img0);
		result = img0.clone();
		threshold(img0, result, 200, 255, CV_THRESH_BINARY);
		namedWindow("��ֵ��ͼ��");
		imshow("��ֵ��ͼ��", result);

		int rowNumber = result.rows;
		int colNumber = result.cols;

		int j;
		for (int i = 0; i < rowNumber; i++)
		{
			uchar *a = result.ptr<uchar>(i);
			bool flag = false;
			int count = 0;
			for (j = 0; j < colNumber; j++)
			{
				if (a[j])
				{
					count++;
					flag = true;
				}
				else
				{
					if (flag)
					{
						output << i << "," << ((j - count) + j) / 2 << "\n";
						break;
					}
				}
			}
		}
		output << "******" << "\n";
		//waitKey(delay);
	}

	output.close();
}
int photo3()				//������ɨ��
{
	Mat  result, frame, img0, img1;

	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		return -1;
	}
	char filename[200];
	int cnt = 0;
	int delay = 60;
	char file[200];
	sprintf(file, "D://SD_DIY//Photo3//test.txt");
	ofstream output(file);
	for (int u = 0; u < 280; u++)
	{
		Mat imag;
		cap >> imag;
		imshow("video", imag);
		sprintf(filename, "D:\\SD_DIY\\Photo3\\pic%d.jpg", ++cnt);
		imwrite(filename, imag);
		char buf[100];
		img0 = imread("D:\\SD_DIY\\Photo3\\pic" + std::string(_itoa(cnt, buf, 10)) + ".jpg", 0);
		//imshow("show", imag);
		namedWindow("ԭͼ");
		imshow("ԭͼ", img0);
		result = img0.clone();
		threshold(img0, result, 200, 255, CV_THRESH_BINARY);
		namedWindow("��ֵ��ͼ��");
		imshow("��ֵ��ͼ��", result);

		int rowNumber = result.rows;
		int colNumber = result.cols;
		//vector<pair<int, int>> position;
		int j;
		for (int i = 0; i < rowNumber; i++)
		{
			uchar *a = result.ptr<uchar>(i);
			bool flag = false;
			int count = 0;
			for (j = 0; j < colNumber; j++)
			{
				if (a[j])
				{
					count++;
					flag = true;
				}
				else
				{
					if (flag)
					{
						output << i << "," << ((j - count) + j) / 2 << "\n";
						break;
					}
				}
			}

		}
		output << "******" << "\n";
	}
	output.close();
}


//ͨ����ȡtxt�ļ���ȡ��ά���꣬������������
//�ļ�����������
void show_pointCloud()
{
	vector<double> W;		//���ݴ��ļ��������������
	double d;
	VVV.clear();
	vector<double> vertex;
	vertex.resize(3);

    ifstream input("D:\\SD_DIY\\Photo2\\test.txt");		//����
	string line;										//��������ÿһ��

	for (int a = 0; a < 280 * 3; ) 
	{
		while (getline(input, line))
		{
			d = stringToNum(line);
			W.push_back(d);
		}
	}
	input.close();
    
    for(it = W.begin();it != W.end();)     
    {
		vertex[0] = *it;
	 	it++;
		vertex[1] = *it;
		it++;
		vertex[2] = *it;
		it++;
		
		VVV.push_back(vertex);
	}
}

//�ַ���ת��Ϊdouble����
double stringToNum(const string& str)
{
	istringstream iss(str);
	double num;
	iss >> num;
	return num;
}

int main(int argc, char *argv[])
{
	bool boolVariable = true;
	float floatVariable = 0.1f;
	enum Orientation { Up = 0, Down, Left, Right } dir = Up;

	//Load a mesh in OFF format
	igl::readOFF(TUTORIAL_SHARED_PATH "/bunny.off", V, F);

	arduino = new SerialPort(portName);

	//Checking if arduino is connected or not
	if (arduino->isConnected()) {
		std::cout << "Connection established at port " << portName << endl;
	}

	// Init the viewer
	igl::viewer::Viewer viewer;

	// Extend viewer menu
	viewer.callback_init = [&](igl::viewer::Viewer& viewer)
	{
		// Add an additional menu window
		viewer.ngui->addWindow(Eigen::Vector2i(210, 10), "3D Scanner");

		viewer.ngui->addButton("First scan", []() {
			//�򿪼�������������� 
			arduino->writeSerialPort(ON, MAX_DATA_LENGTH);
			std::cout << "First scan!\n";
			//opencv�������������
			photo1();
		});

		viewer.ngui->addButton("Second scan", []() {
			arduino->writeSerialPort(ON, MAX_DATA_LENGTH);
			std::cout << "Second scan!\n";
			photo2();
		});

		viewer.ngui->addButton("Third scan", []() {
			arduino->writeSerialPort(ON, MAX_DATA_LENGTH);
			std::cout << "Third scan!\n";
			photo3();
		});

		viewer.ngui->addButton("Point Cloud", []() {
			//��ʾ����
			show_pointCloud();
			std::cout << "Point Cloud!\n";
		});

		// Generate menu
		viewer.screen->performLayout();
		return false;
	};

  igl::list_to_matrix(VVV, V);
  viewer.data.add_points(V, Eigen::RowVector3d(1, 0, 0));
  viewer.core.align_camera_center(V);
  
  // Plot the mesh
  viewer.data.set_mesh(V, F);
  viewer.launch();
}
#endif
