#include <stdio.h>
#include <ctype.h>
#include <cv.h>
#include <highgui.h>
#include <curses.h>
#include "get_contour.h"

#define PORT "/dev/ttyACM0" //適宜変更のこと
#include "serial2016.h"

#define CAMERA_CENTER_H 89 //カメラサーボの垂直方向中央値（キャリブレーションに利用）
#define CAMERA_CENTER_V 96 //カメラサーボの垂直方向中央値（キャリブレーションに利用）
#define MOTOR_DEFAULT_L 120 //左モータのデフォルト値（キャリブレーションに利用）
#define MOTOR_DEFAULT_R 134 //右モータのデフォルト値（キャリブレーションに利用）
#define CAMERA_INIT_V 72 //カメラサーボの垂直方向初期値
#define CAMERA_INIT_H 96 //カメラサーボの水平方向初期値
#define rotate 34.0//回転速度
#define speed 12.0

int stage = 1;
int endFlag = 0;
double distance;
int rotateDir;
int color = 1;

void on_mouse(int event, int x, int y, int flags, void *param);

int main(int argc, char **argv)
{
  CvCapture *capture = NULL;
  IplImage *frame;     // キャプチャ画像 (RGB)
  IplImage *frameHSV;   // キャプチャ画像 (HSV)
  IplImage* framePT;    // 透視変換画像 (RGB)
  IplImage* framePTHSV; // 透視変換画像 (HSV)
	
	int i;float *p;
  IplImage* mask;      // 指定値によるmask (１チャネル)
  IplImage* contour;   // GetLargestContour() の結果
  IplImage** frames[] = {&frame, &frameHSV};
  IplImage** framesPT[] = {&framePT, &framePTHSV};
  contourInfo topContoursInfo[CONTOURS];
  int key;

	//hough1変換用変数
	IplImage *frameGray = NULL;
	CvMemStorage *storage;
	CvSeq *circles = NULL;

  init();

  // 実習項目5.0で計測したモーターの中央値をmotor_onに、サーボの中央値をcamera_onにそれぞれセットする
  motor_on(MOTOR_DEFAULT_L, MOTOR_DEFAULT_R); // モーター静止パルス幅のキャリブレーション
  camera_on(CAMERA_CENTER_V,CAMERA_CENTER_H);    // カメラアングルキャリブレーション

  camera_horizontal(CAMERA_INIT_H); // 水平方向のカメラ角度を初期値に
  camera_vertical(CAMERA_INIT_V); // 垂直方向のカメラ角度を初期値に

  // 赤系のHSV色．各自チューニングすること
  uchar minH = 110, maxH = 140;
  uchar minS = 100, maxS = 255;
  uchar minV =  60, maxV = 255;
  CvMat *map_matrix;
  CvPoint2D32f src_pnt[4], dst_pnt[4];

  src_pnt[0] = cvPoint2D32f(181.0, 199.0);
  src_pnt[1] = cvPoint2D32f(110.5, 199.0);
  src_pnt[2] = cvPoint2D32f(104.7, 240.0);
  src_pnt[3] = cvPoint2D32f(184.2, 240.0);
  dst_pnt[0] = cvPoint2D32f(132.5, 240.0);
  dst_pnt[1] = cvPoint2D32f(107.5, 240.0);
  dst_pnt[2] = cvPoint2D32f(107.5, 260.0);
  dst_pnt[3] = cvPoint2D32f(132.5, 260.0);
  map_matrix = cvCreateMat (3, 3, CV_32FC1);
  cvGetPerspectiveTransform (src_pnt, dst_pnt, map_matrix);
  if (argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
    capture = cvCaptureFromCAM(argc == 2 ? argv[1][0] - '0' : -1);
  if (capture == NULL) {
    printf("not find camera\n");
    return -1;
  }
  // 解析速度向上のために画像サイズを下げる
  cvSetCaptureProperty (capture, CV_CAP_PROP_FRAME_WIDTH, 320);
  cvSetCaptureProperty (capture, CV_CAP_PROP_FRAME_HEIGHT, 240);

  frame = cvQueryFrame(capture);
  frameHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
  framePT = cvCreateImage(cvSize(240,270), IPL_DEPTH_8U, 3);
  framePTHSV = cvCreateImage(cvGetSize(framePT), IPL_DEPTH_8U, 3);
  mask = cvCreateImage(cvGetSize(framePT), IPL_DEPTH_8U, 1);
  contour = cvCreateImage(cvGetSize(framePT), IPL_DEPTH_8U, 3);

  cvNamedWindow("src", CV_WINDOW_AUTOSIZE);
  cvNamedWindow("dst", CV_WINDOW_AUTOSIZE);
  cvNamedWindow("contour", CV_WINDOW_AUTOSIZE);
  cvMoveWindow("src", 60,480);
  cvMoveWindow("dst", 380,480);
  cvMoveWindow("contour", 700,480);
  cvSetMouseCallback("src", on_mouse, (void *)frames);
  cvSetMouseCallback("dst", on_mouse, (void *)framesPT);
  cvSetMouseCallback("contour", on_mouse, (void *)framesPT);

  while (1) {
    frame = cvQueryFrame(capture);
	frame = cvQueryFrame(capture);
  	frameGray = cvCreateImage (cvGetSize(frame), IPL_DEPTH_8U, 1);

    cvCvtColor(frame, frameHSV, CV_RGB2HSV);
    cvWarpPerspective (frame, framePT, map_matrix,
    CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll (100));

    cvCvtColor(framePT, framePTHSV, CV_RGB2HSV);
    cvShowImage("src", frame);
    cvShowImage("dst", framePT);
    GetMaskHSV(framePT, mask, minH, maxH, minS, maxS, minV, maxV);
    GetLargestContour(framePT, mask, contour, topContoursInfo);
    cvShowImage("contour", contour);
    key = cvWaitKey(1);

    //if(stage == 4){

	

    // (1) カメラからの入力画像1フレームをframeに格納
    frame = cvQueryFrame(capture);
    cvCvtColor(frame, frameGray, CV_RGB2GRAY); 

    //hough1変換
    // (2)ハフ変換のための前処理（画像をq平滑化しないと誤検出が出やすい）
    cvSmooth (frameGray, frameGray, CV_GAUSSIAN, 11, 0, 0, 0);
    storage = cvCreateMemStorage (0);

    // (3)ハフ変換による円の検出と検出した円の描画
    circles = cvHoughCircles (frameGray, storage, CV_HOUGH_GRADIENT, 
                              1, 3.0, 20.0, 70.0, 10,
                           MAX (frameGray->width, frameGray->height));
 	for (i = 0; i < MIN (3,circles->total); i++) { 
       p = (float *) cvGetSeqElem (circles, i); 
       cvCircle (frame, cvPoint (cvRound (p[0]), cvRound (p[1])), 
     		3, CV_RGB (0,255,0), -1, 8, 0); 
       cvCircle (frame, cvPoint (cvRound (p[0]), cvRound (p[1])), 
     		cvRound (p[2]), CV_RGB (255,0,0), 6-2*i, 8, 0); 
	}	
    ////
    if(topContoursInfo[0].area > 0)
    {
      /// 赤い物体を見つけた場合
      CvBox2D oblique = topContoursInfo[0].oblique; // 認識した物体を囲む長方形
      int x = oblique.center.x;                            // 認識した物体の画面内のx座標(0~239)
      int y = oblique.center.y;
      float angle = oblique.angle;
      float calAngle = angle;
      CvRect horizontal = topContoursInfo[0].horizontal;
      double width = horizontal.width;
      double height = horizontal.height;
      
      distance = (239-y)*0.4+44; 


      switch(stage){
        case 1:
        //目標を視界中央に入れる。
        printf("stage 1\n");
        if(x <= 130 && x >= 120) {
          motor_stop();
	  usleep(1000000);
          stage = 2;
          break;
        }else if(x > 130) { 
          motor(135, 120);
          break; 
        }
        else if(x < 120) {
          motor(120, 135);
          break;
        }


        case 2:
        // 正面回り
        if( -1*angle > 10 && -angle < 80){
          printf("stage 2 \n");
	  printf("a");

          calAngle = width > height ? 90+angle : -angle ;
	  angle = -angle > 45 ? -angle : 90+angle;  
          rotateDir = width > height ? -1 : 1 ;
          
          motor(128 + 10 * rotateDir, 128 - 10 * rotateDir);//正面と垂直方向になるまで回転  
          printf("%f %f\n",-angle, calAngle);
          usleep(angle / rotate * 1000000);
	  printf("a");
	  motor_stop();
	  usleep(500000);
	  //stage = -1;
	  //break;
          motor(150,150);//正面まで移動
          usleep((distance * sin((90 - calAngle) * M_PI / 180) / speed) * 1000000); 
	  //stage = -1;
	  //break;
          motor(128 - 10 * rotateDir, 128 + 10 * rotateDir);//正面に向く
          usleep(90.0 / rotate * 1000000);

          motor_stop();
          stage = 3; 
          break;

        }else{
          stage = 3;
	  break;
        }  


        case 3:
        //目標に接近
        printf("stage 3\n");
        if(x <= 130 && x >= 120) {
	  motor(150,150);
          distance = (240-y)*0.4+44; 
        }else if(x > 130) { 
          motor(135, 120); 
        }
        else if(x < 120) {
          motor(120, 135);
        }
        if(y>=240){
	  //stage = -1;
	  //break;
          usleep(distance / speed * 100000);
          stage = 4;
        }
        break;


        case 5:
        //ステップ4:目標変更
        if(color == 1){ //赤→緑
          minH = 30, maxH = 50;
          minS = 100, maxS = 255;
          minV =  60, maxV = 255;
          color = 2;
          stage = 1;
        }else if(color == 2){ //緑→青
          minH = 0, maxH = 20;
          minS = 100, maxS = 255;
          minV =  60, maxV = 255;
          color = 3;
          stage = 1;
        }else if(color == 3){
          printf("end\n");
          endFlag = 1;
        }
        break;
      } 
    }
    else
    {/// 赤い物体が見つからなかった場合
     	if(stage != 4 )motor(135,120); 
    }
	
    if( stage == 4){
	if(circles->total>1){
		printf("circle\n");
		float *q;
	q = (float*)cvGetSeqElem(circles,1);
	float X = q[0];
	float Y = q[1];
		if(X>120 && X<130 && Y>120){
		motor_stop();
		printf("sss");
		usleep(500000);
		motor(145,145);
		usleep(5000000);
		stage = -1;
	}else if(X<120){
		motor(128-10,128+10);
		usleep(50000);
printf("a\n");	
	}else if(X>130){
printf("b\n");
		motor(128+10,128-10);	
		usleep(50000);
	}
	}
	
    }

    ////
    if (endFlag == 1) break;
    if (key == 'q') break;
	if(stage==-1)break;
  }

  finalize();
  cvDestroyWindow("src");
  cvDestroyWindow("contour");
  cvReleaseImage(&frameHSV);
  cvReleaseImage(&framePTHSV);
  cvReleaseImage(&mask);
  cvReleaseImage(&contour);
  cvReleaseCapture(&capture);
  return 0;
}

void on_mouse(int event, int x, int y, int flags, void *frames)
{
  CvScalar BGR, HSV;
  if (event == CV_EVENT_MOUSEMOVE) {
    IplImage* rgb_image = *(((IplImage***)frames)[0]);
    IplImage* hsv_image = *(((IplImage***)frames)[1]);
    if(y < rgb_image->height && x < rgb_image->width &&
      y < hsv_image->height && x < hsv_image->width)
    {
      BGR = cvGet2D(rgb_image, y, x);
      HSV = cvGet2D(hsv_image, y, x);
      printf("(%3d,%3d): RGB=(%3.0f,%3.0f,%3.0f) HSV=(%3.0f,%3.0f,%3.0f)\n",
             x, y, BGR.val[2], BGR.val[1], BGR.val[0],
             HSV.val[0], HSV.val[1], HSV.val[2]);
    }
  }
}
