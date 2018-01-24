#include<stdlib.h>
#include<stdio.h>
#include<highgui.h>
#include<cv.h>
#include<cxcore.h>

int main(int argc,char*argv[])
{
	//创建矩阵
	double a[]= {1,2,3,4,5,6,2,5,4, 
				7,8,5,4,5,5,7,1,8};
	CvMat* M = cvCreateMat(2,3,CV_64FC3);
	cvInitMatHeader(M,2,3,CV_64FC3,a);
	
	//创建图像
	IplImage* img = cvCreateImage(cvGetSize(M),8,3);//cvCreateImage（大小，depth，通道）
	
	int p,q;
	printf("原矩阵\n");
	for(p = 0; p<M->rows; p++){
		for(q = 0; q< M->cols;q++)
		{
			CvScalar scal =cvGet2D(M,p,q);
			printf("%f %f %f",scal.val[0],scal.val[1],scal.val[2]);
		}
		printf("\n");
	}
	//保存图像
    cvGetImage(M,img);//mat类型转换为IplImage类型
	cvSaveImage("img.bmp",img);//只有IplImage类型才能使用cvSaveImage
	cvReleaseMat(&M);
	
	
	IplImage* src = cvLoadImage("img.bmp");
	
	
	//创建CvScalar结构体，命名为s1，存储读取的数值
	CvScalar s1;

	//读取（i，j)位置的数值
	int i = 0;
	int j = 2;//第二行的第一个元素
	
	//方法一：间接方式
	s1 = cvGet2D(src,i,j); // get the (i,j) pixel value
    printf("方法一：%f %f %f\n",s1.val[0],s1.val[1],s1.val[2]);
	
	//方法二：直接方式
	double s21 = ((uchar *)(src->imageData + i*src->widthStep))[3*j];
	double s22 = ((uchar *)(src->imageData + i*src->widthStep))[3*j+1];
	double s23 = ((uchar *)(src->imageData + i*src->widthStep))[3*j+2];
	printf("方法二：%f %f %f\n",s21,s22,s23);

	//方法三：指针直接访问
	int step        = src->widthStep/sizeof(uchar);
    uchar* data     = (uchar *)src->imageData;
    double s31 = data[i*step+3*j];
	double s32 = data[i*(step)+3*j+1];
	double s33 = data[i*(step)+3*j+2];
	printf("方法三：%f %f %f\n",s31,s32,s33);
	
	cvReleaseImage(&src);
	cvDestroyWindow("原图");
	getchar();


	return 0;
	
}