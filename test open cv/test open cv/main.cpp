// 2022/11 ver
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <ctime> 
#include <windows.h>

using namespace std;
using namespace cv;

char ascii_char[70] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
float unit = (256.0 + 1) / 69;
int x, y;
void show()
{
	Mat srcImage = imread("pic.png", 0);
	Mat resizeImage;
	string txt;
	resize(srcImage, resizeImage, Size(120, 50));
	int rowNumber = resizeImage.rows;
	int colNumber = resizeImage.cols;

	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			txt += ascii_char[int((resizeImage.at<uchar>(i, j)) / unit)];
		}
		txt += '\n';
	}

	//写入txt 
	ofstream file;
	file.open("file.txt");
	if (file.is_open())
	{
		file << txt;
	}
	file.close();
	std::ifstream ifs("file.txt", std::ios::in);
	if (!ifs.is_open()) {
		cout << "Failed to open file.\n";
	}

	std::stringstream ss;
	ss << ifs.rdbuf();
	std::string str(ss.str());
	cout << str;
	ifs.close();
}

void pause()
{
	printf("Press Enter key to continue...");
	fgetc(stdin);
}
int main()
{
	VideoCapture capture;
	capture.open("bad apple.mp4");
	if (!capture.isOpened())
	{
		cout << "could not load video.." << endl;
		pause();
		return -1;
	}
	else
	{

		Size S = Size((int)capture.get(CAP_PROP_FRAME_WIDTH), (int)capture.get(CAP_PROP_FRAME_HEIGHT));
		int fps = capture.get(CAP_PROP_FPS);
		cout << "capture Width:" << S.width << "\tHeight:" << S.height << endl;
		cout << "capture fps: " << fps << endl;

		VideoWriter writer("test.mp4", cv::VideoWriter::fourcc('D', 'I', 'V', 'X'), fps, S, true);


		Mat frame;
		while (capture.read(frame)) {
			Sleep(10);
			imwrite("pic.png", frame);
			show();
			//system("CLS");
			//char c = waitKey(1);
			//if (c == 27) //ESC
			//{
			//	break;
			//}
		}

	}

	return 0;
}