#include<stdlib.h>
#include<stdio.h>
#include<highgui.h>
#include<cv.h>
#include<cxcore.h>

int main(int argc,char*argv[])
{
	//��������
	double a[]= {1,2,3,4,5,6,2,5,4, 
				7,8,5,4,5,5,7,1,8};
	CvMat* M = cvCreateMat(2,3,CV_64FC3);
	cvInitMatHeader(M,2,3,CV_64FC3,a);
	
	//����ͼ��
	IplImage* img = cvCreateImage(cvGetSize(M),8,3);//cvCreateImage����С��depth��ͨ����
	
	int p,q;
	printf("ԭ����\n");
	for(p = 0; p<M->rows; p++){
		for(q = 0; q< M->cols;q++)
		{
			CvScalar scal =cvGet2D(M,p,q);
			printf("%f %f %f",scal.val[0],scal.val[1],scal.val[2]);
		}
		printf("\n");
	}
	//����ͼ��
    cvGetImage(M,img);//mat����ת��ΪIplImage����
	cvSaveImage("img.bmp",img);//ֻ��IplImage���Ͳ���ʹ��cvSaveImage
	cvReleaseMat(&M);
	
	
	IplImage* src = cvLoadImage("img.bmp");
	
	
	//����CvScalar�ṹ�壬����Ϊs1���洢��ȡ����ֵ
	CvScalar s1;

	//��ȡ��i��j)λ�õ���ֵ
	int i = 0;
	int j = 2;//�ڶ��еĵ�һ��Ԫ��
	
	//����һ����ӷ�ʽ
	s1 = cvGet2D(src,i,j); // get the (i,j) pixel value
    printf("����һ��%f %f %f\n",s1.val[0],s1.val[1],s1.val[2]);
	
	//��������ֱ�ӷ�ʽ
	double s21 = ((uchar *)(src->imageData + i*src->widthStep))[3*j];
	double s22 = ((uchar *)(src->imageData + i*src->widthStep))[3*j+1];
	double s23 = ((uchar *)(src->imageData + i*src->widthStep))[3*j+2];
	printf("��������%f %f %f\n",s21,s22,s23);

	//��������ָ��ֱ�ӷ���
	int step        = src->widthStep/sizeof(uchar);
    uchar* data     = (uchar *)src->imageData;
    double s31 = data[i*step+3*j];
	double s32 = data[i*(step)+3*j+1];
	double s33 = data[i*(step)+3*j+2];
	printf("��������%f %f %f\n",s31,s32,s33);
	
	cvReleaseImage(&src);
	cvDestroyWindow("ԭͼ");
	getchar();


	return 0;
	
}