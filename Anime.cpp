#include <opencv2/opencv.hpp>
#include <dirent.h>	//directry
#include <string.h>	//strcmp

using namespace std;
using namespace cv;

void detectAndDisplay(Mat image);

CascadeClassifier face_cascade;

int main(void){
	//カスケードのロード
	face_cascade.load("lbpcascade_animeface.xml");
	string path = "rawdata/";
	DIR *dp;       // ディレクトリへのポインタ
	dirent* entry; // readdir() で返されるエントリーポイント

	dp = opendir(path.c_str());
	if (dp==NULL) exit(1);
	do {
		entry = readdir(dp);
		if (entry != NULL && strcmp(entry->d_name,"..") && strcmp(entry->d_name,".")){
			std::cout << entry->d_name<<"\t";
			string fp = path + entry->d_name;
			Mat image;
			image = imread(fp);
			detectAndDisplay(image);
		}
	} while (entry != NULL);
	// waitKey(0);
	return 0;
}

//認識と表示を行う関数
void detectAndDisplay(Mat image){
	vector<Rect> faces;
	Mat frame_gray;

	//画像のグレースケール化
	cvtColor(image, frame_gray, COLOR_BGR2GRAY );
	//ヒストグラムの平坦化
	equalizeHist(frame_gray, frame_gray);
	//顔の認識
	face_cascade.detectMultiScale(frame_gray, faces);
	//顔を丸で囲む
	for(int i = 0; i<faces.size(); i++){
		static int exfnum=0;
		// Point center(faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
		// ellipse(image, center, Size(faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar(255, 0, 255), 2, 8, 0);
		Mat cut_img(image,Rect(faces[i].x,faces[i].y,faces[i].width,faces[i].height));
		std::string fname = "ex_face/" + std::to_string(exfnum++) + ".jpg";
		// imshow(fname, image);
		imwrite(fname,cut_img);
		cout<<i<<endl;
	}
}
