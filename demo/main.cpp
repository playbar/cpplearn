#include <iostream>
#include "CTest.h"
#include <sys/types.h>
#include <unistd.h>
#include <map>
#include <fcntl.h>

/*
 * open函数用来打开一个设备，他返回的是一个整型变量，如果这个值等于-1，说明打开文件出现错误，如果为大于0的值
 参考格式 if(fd=open("/dev/ttys0",O_RDWR | O_NOCTTY | O_NDELAY))<0 {printf("cannot open"};
 int open(const char *pathname, int oflag, …/*, mode_t mode * / ) ;
 打开的操作类型有如下几种
   1) O_RDONLY 只读打开
   2) O_WRONLY 只写打开
   3) O_RDWR 读、写打开
   4) O_APPEND 每次写时都加到文件的尾端
   5) O_CREAT 若此文件不存在则创建它。使用此选择项时，需同时说明第三个参数mode，用其说明该新文件的存取许可权位。
   6) O_EXCL 如果同时指定了O_CREAT，而文件已经存在，则出错。这可测试一个文件是否存在，如果不存在则创建此文件成为一个原子操作。
   7) O_TRUNC 如果此文件存在，而且为只读或只写成功打开，则将其长度截短为0。
   8) O_NOCTTY 如果p a t h n a m e指的是终端设备，则不将此设备分配作为此进程的控制终端。
   9) O_NONBLOCK 如果p a t h n a m e指的是一个F I F O、一个块特殊文件或一个字符特殊文件，则此选择项为此文件的本次打开操作和后续的I / O操作设置非阻塞方式。
   10)O_SYNC 使每次w r i t e都等到物理I / O操作完成。
   这些控制字都是通过“或”符号分开（|）
 */
void testopenfile()
{
    const std::string param_file = "version.txt";
    int fd = open("/dev/ttys0",O_RDWR | O_NOCTTY | O_NDELAY);
    int fd1 = open(param_file.c_str(), O_RDONLY);
    if( fd < 0 )
    {
        printf("cannot open");
    } else{
        printf("fd : %d \n", fd);
    }
    return;
}

void testmap()
{
    map<person,int> m;
    person p1("Tom1",20);
    person p2("Tom2",22);
    person p3("Tom3",22);
    person p4("Tom4",23);
    person p5("Tom5",24);
    m.insert(make_pair(p3, 100));
    m.insert(make_pair(p4, 100));
    m.insert(make_pair(p5, 100));
    m.insert(make_pair(p1, 100));
    m.insert(make_pair(p2, 100));

    for(map<person, int>::iterator iter = m.begin(); iter != m.end(); iter++)
    {
        cout<<iter->first.name<<"\t"<<iter->first.age<<endl;
    }
    return;
}

void testStr()
{
    char line[] = "selinuxfs /sys/fs/selinux selinuxfs rw,relatime 0 0";
    if (strstr(line, "selinuxfs")) {
        strtok(line, " ");
        char* selinux_dir = strtok(NULL, " ");
        char* selinux_path = strcat(selinux_dir, "/enforce");
        FILE* fp_selinux = fopen(selinux_path, "w");
        char* buf = "0"; // set selinux to permissive
        printf("fp_selinux:%0x", fp_selinux);
        if( fp_selinux != NULL ) {
            fwrite(buf, strlen(buf), 1, fp_selinux);
            fclose(fp_selinux);
        }
    }
    return;
}

struct Rect
{
    int left;
    int top;
    int right;
    int bottom;
};

int rect_intersects_rect(Rect rect1, Rect rect2) {
    return !(rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top);

}

size_t SysStrlcpy(char *dst, const char *src, size_t siz)
{
    char *d = dst;
    const char *s = src;
    size_t n = siz;

    /* Copy as many bytes as will fit */
    if (n != 0) {
        while (--n != 0) {
            if ((*d++ = *s++) == '\0')
                break;
        }
    }

    /* Not enough room in dst, add NUL and traverse rest of src */
    if (n == 0) {
        if (siz != 0)
            *d = '\0';		/* NUL-terminate dst */
        while (*s++)
            ;
    }

    return(s - src - 1);	/* count does not include NUL */
}

void test_strncpy(){
    char dest1[20];
    char src1[] = "abc";
    int n1 = 3;
    char dest2[20]="*******************";
    char src2[] = "abcxyz";
    int n2 = strlen(src2)+1;
    char dest3[100] = "http://see.xidian.edu.cn/cpp/shell/";
    char src3[6] = "abcxy";  // 没有'\0'
    int n3 = 20;
    char dest4[100] = "http://see.xidian.edu.cn/cpp/u/yuanma/";
    char src4[] = "abc\0defghigk";
    int n4 = strlen(src3);
    strncpy(dest1, src1, n1);  // n1小于strlen(str1)+1，不会追加'\0'
    strncpy(dest2, src2, n2);  // n2等于strlen(str2)+1，恰好可以把src2末尾的'\0'拷贝到dest2
    strncpy(dest3, src3, n3);  // n3大于strlen(str3)+1，循环拷贝str3
    strncpy(dest4, src4, n4);  // src4中间出现'\0'
    printf("dest1=%s\n", dest1);
    printf("dest2=%s, dest2[15]=%c\n", dest2, dest2[10]);
    printf("dest3=%s\n", dest3);
    printf("dest4=%s, dest4[6]=%d, dest4[20]=%d, dest4[90]=%d\n", dest4, dest4[6], dest4[20], dest4[90]);

}

void test_snprintf()
{
    char str[5] = {};
    printf("%s \n", str);
    int ret = snprintf(str, 5, "%s", "abcdefg");
    printf("%d\n",ret);
    printf("%s \n",str);
}

/// <summary>
/// 获取图片空白处坐标
/// </summary>
/// <param name="imagePdf">图片的路径</param>
///  <param name="isize">二维码的宽度尺寸</param>
/// <returns>//[0]是x坐标，[1]是y坐标</returns>
public int[] GetSize(string strImagePdfUrl, int isize)
{
   // isize++;
    int iret[2];
    System.Drawing.Bitmap bmp = new System.Drawing.Bitmap(strImagePdfUrl);

    //1.判断高度是否满足
    int iboolheith = 0;//判断是否跳出 width 遍历
    int boolweigh = 0; //该列高度是否满足条件
    int icountWeigh = 0; //统计宽度白色区域
    int boolblack = 0;  //判断宽度是否满足时，有黑点
    int boolok = 0; //全部满足条件
    for (int a = 0; a < bmp.Width; a++)
    {//图片的坐标原点在左上角
        int icountHeigh = 0; //统计高度白色区域
        if (boolweigh == 0)  //该列高度是不满足条件
        {
            for (int j = 0; j < bmp.Height; j++)
            {
                //获取该点的像素的RGB的颜色
                System.Drawing.Color color = bmp.GetPixel(a, j);
                bmp.GetPixel(a, j);

                //测试用例
                if (a == 78 && j == 167)
                {
                  //  MessageBox.Show("R:" + color.B + " G:" + color.G + " B:" + color.B);
                }

                if (color.B == 255 && color.R == 255 && color.G == 255)
                {//该点像素是白色
                    icountHeigh++;
                    if (icountHeigh > isize)
                    { //二维码图片高度和宽度相等
                        iret[0] = a; //宽
                        iret[1] = j; //高
                        iboolheith = 1; //该列高度满足条件
                        break;  //跳出循环 height
                    }
                } //end if value > average
                else
                {
                    icountHeigh = 0; //不是连续的白色区域，清空计数
                }
            }//enf for j
        }


        if (iboolheith == 1) //该列高度满足条件
        {  ////2.判断宽度是否满足
            for (int t = iret[0]+1; t < bmp.Width - iret[0]; t++)
            {//宽度往右遍历
                int icImgheight = 0;
                icountHeigh = 0;
                for (int m = iret[1]; m>0; m--)
                {// 高度往上遍历（图片的坐标原点在左上角，）

                    if (icImgheight > isize)
                    {
                        icountHeigh = 0;
                        break; //超出高度范围
                    }
                    icImgheight++;
                    //获取该点的像素的RGB的颜色
                    System.Drawing.Color color = bmp.GetPixel(t, m);
                    if (color.B == 255 && color.R == 255 && color.G == 255)
                    {//改点像素为白色
                        icountHeigh++;
                        if (icountHeigh > isize)
                        { //该列的高度满足条件
                            boolweigh = 1;
                            icountHeigh = 0;
                            boolblack = 0;
                            break;  //跳出循环 m = iret[1]
                        }
                    }
                    else
                    {
                        boolweigh = 0;
                        icountWeigh = 0;
                        icountHeigh = 0;
                        boolblack = 1; //有黑点
                        break;  //跳出循环for m = iret[1]
                    }
                }//end for m = iret[1]
                if (boolweigh == 1)
                {//该列的高度满足条件，列的计算++
                    icountWeigh++;
                    boolweigh = 0;
                }
                if (icountWeigh > isize)
                {//宽度满足条件
                    iret[0] = t;
                    boolok = 1;
                    break;  //跳出循环 wdith
                }
                if (boolblack == 1)
                {//有黑点
                    boolblack = 0;
                    break; //跳出循环wdith  for  t = iret[0]
                }
            }//end for t = iret[0]

        }//end if iboolheith =1

        if (boolok == 1)
        {//宽和高的条件都满足
            boolok = 0;
            break;
        }

    }//end for a 最外层的宽度遍历

    return iret;
}

int main() {
    test_snprintf();
    test_strncpy();
    testopenfile();
    char *pdata = "abcdefg";
    char temp[30];
    SysStrlcpy(temp, pdata, 30);
    Rect rect1 = {361, 468, 393, 500};
    Rect rect2 = {362, 469, 392, 499};
    Rect rect3 = { 10, 10, 40, 40};
    Rect rect4 = {350, 469, 392, 499};

    int re = rect_intersects_rect(rect1, rect4);

    testmap();
    testStr();
    CTest a;
    std::cout << "Hello, World!" << std::endl;
    pid_t pid = getpid();
    depth_1();
    return 0;
}