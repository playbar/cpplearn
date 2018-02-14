#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <random>
#include <time.h>
#include "cnn.h"
#include "minst.h"

// 以下都是测试函数，可以不用管
// 测试Minst模块是否工作正常
void test_minst(){
	LabelArr testLabel=read_Lable("./data/test-labels.idx1-ubyte");
	ImgArr testImg=read_Img("./data/test-images.idx3-ubyte");
	save_Img(testImg,"./testImgs/");
}
// 测试Mat模块是否工作正常
void test_mat(){
	int i,j;
	nSize srcSize={6,6};
	nSize mapSize={4,4};
	srand((unsigned)time(NULL));
	float** src=(float**)malloc(srcSize.r*sizeof(float*));
	for(i=0;i<srcSize.r;i++){
		src[i]=(float*)malloc(srcSize.c*sizeof(float));
		for(j=0;j<srcSize.c;j++){
			src[i][j]=(((float)rand()/(float)RAND_MAX)-0.5)*2; 
		}
	}
	float** map=(float**)malloc(mapSize.r*sizeof(float*));
	for(i=0;i<mapSize.r;i++){
		map[i]=(float*)malloc(mapSize.c*sizeof(float));
		for(j=0;j<mapSize.c;j++){
			map[i][j]=(((float)rand()/(float)RAND_MAX)-0.5)*2; 
		}
	}

	nSize cov1size={srcSize.c+mapSize.c-1,srcSize.r+mapSize.r-1};
	float** cov1=cov(map,mapSize,src,srcSize,full);
	//nSize cov2size={srcSize.c,srcSize.r};
	//float** cov2=cov(map,mapSize,src,srcSize,same);
	nSize cov3size={srcSize.c-(mapSize.c-1),srcSize.r-(mapSize.r-1)};
	float** cov3=cov(map,mapSize,src,srcSize,valid);

	savemat(src,srcSize,"./data/src.ma");
	savemat(map,mapSize,"./data/map.ma");
	savemat(cov1,cov1size,"./data/cov1.ma");
	//savemat(cov2,cov2size,"./data/cov2.ma");
	savemat(cov3,cov3size,"./data/cov3.ma");

	float** sample=UpSample(src,srcSize,2,2);
	nSize samSize={srcSize.c*2,srcSize.r*2};
	savemat(sample,samSize,"./data/sam.ma");
}
void test_mat1()
{
	int i,j;
	nSize srcSize={12,12};
	nSize mapSize={5,5};
	float** src=(float**)malloc(srcSize.r*sizeof(float*));
	for(i=0;i<srcSize.r;i++){
		src[i]=(float*)malloc(srcSize.c*sizeof(float));
		for(j=0;j<srcSize.c;j++){
			src[i][j]=(((float)rand()/(float)RAND_MAX)-0.5)*2; 
		}
	}
	float** map1=(float**)malloc(mapSize.r*sizeof(float*));
	for(i=0;i<mapSize.r;i++){
		map1[i]=(float*)malloc(mapSize.c*sizeof(float));
		for(j=0;j<mapSize.c;j++){
			map1[i][j]=(((float)rand()/(float)RAND_MAX)-0.5)*2; 
		}
	}
	float** map2=(float**)malloc(mapSize.r*sizeof(float*));
	for(i=0;i<mapSize.r;i++){
		map2[i]=(float*)malloc(mapSize.c*sizeof(float));
		for(j=0;j<mapSize.c;j++){
			map2[i][j]=(((float)rand()/(float)RAND_MAX)-0.5)*2; 
		}
	}
	float** map3=(float**)malloc(mapSize.r*sizeof(float*));
	for(i=0;i<mapSize.r;i++){
		map3[i]=(float*)malloc(mapSize.c*sizeof(float));
		for(j=0;j<mapSize.c;j++){
			map3[i][j]=(((float)rand()/(float)RAND_MAX)-0.5)*2; 
		}
	}

	float** cov1=cov(map1,mapSize,src,srcSize,valid);
	float** cov2=cov(map2,mapSize,src,srcSize,valid);
	nSize covsize={srcSize.c-(mapSize.c-1),srcSize.r-(mapSize.r-1)};
	float** cov3=cov(map3,mapSize,src,srcSize,valid);
	addmat(cov1,cov1,covsize,cov2,covsize);
	addmat(cov1,cov1,covsize,cov3,covsize);


	savemat(src,srcSize,"./data/src.ma");
	savemat(map1,mapSize,"./data/map1.ma");
	savemat(map2,mapSize,"./data/map2.ma");
	savemat(map3,mapSize,"./data/map3.ma");
	savemat(cov1,covsize,"./data/cov1.ma");
	savemat(cov2,covsize,"./data/cov2.ma");
	savemat(cov3,covsize,"./data/cov3.ma");

}
// 测试cnn模块是否工作正常
void test_cnn()
{

	LabelArr testLabel=read_Lable("./data/train-labels-idx1-ubyte");
	ImgArr testImg=read_Img("./data/train-images-idx3-ubyte");

	nSize inputSize={testImg->ImgPtr[0].c,testImg->ImgPtr[0].r};
	int outSize=testLabel->LabelPtr[0].l;

	CNN* cnn=(CNN*)malloc(sizeof(CNN));
	cnnsetup(cnn,inputSize,outSize);

	CNNOpts opts;
	opts.numepochs=1;
	opts.alpha=1;
	int trainNum=5000;
	cnntrain(cnn,testImg,testLabel,opts,trainNum);

	FILE  *fp=NULL;
	fp=fopen("./data/cnnL.ma","wb");
	if(fp==NULL)
		printf("write file failed\n");
	fwrite(cnn->L,sizeof(float),trainNum,fp);
	fclose(fp);
}


/*主函数*/
int main()
{
    test_cnn();

	LabelArr trainLabel=read_Lable("./data/train-labels-idx1-ubyte");
	ImgArr trainImg=read_Img("./data/train-images-idx3-ubyte");
	LabelArr testLabel=read_Lable("./data/t10k-labels-idx1-ubyte");
	ImgArr testImg=read_Img("./data/t10k-images-idx3-ubyte");

	nSize inputSize={testImg->ImgPtr[0].c,testImg->ImgPtr[0].r};
	int outSize=testLabel->LabelPtr[0].l;

	// CNN结构的初始化
	CNN* cnn=(CNN*)malloc(sizeof(CNN));
	cnnsetup(cnn,inputSize,outSize);

	// CNN训练
	/*
	CNNOpts opts;
	opts.numepochs=1;
	opts.alpha=1.0;
	int trainNum=55000;
	cnntrain(cnn,trainImg,trainLabel,opts,trainNum);
	printf("train finished!!\n");
	savecnn(cnn,"minst.cnn");
	// 保存训练误差
	FILE  *fp=NULL;
	fp=fopen("./data/cnnL.ma","wb");
	if(fp==NULL)
		printf("write file failed\n");
	fwrite(cnn->L,sizeof(float),trainNum,fp);
	fclose(fp);
	*/


	// CNN测试
	importcnn(cnn,"minst.cnn");
	int testNum=10000;
	float incorrectRatio=0.0;
	incorrectRatio=cnntest(cnn,testImg,testLabel,testNum);
	printf("test finished!!\n");

	return 0;
}