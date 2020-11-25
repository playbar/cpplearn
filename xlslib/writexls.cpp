#include <iostream>
#include <xlslib.h>
using namespace xlslib_core;
using namespace std;
int main() {
    workbook wb;
    string label;
    printf("Version: %s\n",wb.version());
    //设置字体
    font_t *t=wb.font("Ubuntu");
    t->SetColor(CLR_RED);
    t->SetItalic(true);
    t->SetHeight(20*15);
    // t->SetBoldStyle(BOLDNESS_BOLD);
    xf_t *xf= wb.xformat();
    xf->SetFillBGColor(CLR_GREEN);
    xf->SetFillFGColor(CLR_RED);
    xf->SetFont(t);
    //第一张表单
    worksheet *ws=wb.sheet("one");
    //第二张表单
    worksheet* ws2=wb.sheet("two");
    ws->MakeActive();
    //设置列宽度,行高度
    ws->defaultColwidth(15);
    ws->defaultRowHeight(25);
    //6行
    for (int i = 0; i < 6; ++i) {
        //6列
        for (int j = 0; j <6 ; ++j) {
            char buf[20]={0};
            sprintf(buf,"%d",i*j);
            label=buf;
            // 写入
            cell_t * cell= ws->label(i,j,label,xf);
            //或者 ws->number(i,j,i*j,xf);
            //设置字体阴影
            cell->fontshadow(true);
            //设置单元格文本对齐
            cell->halign(HALIGN_CENTER);
            cell->valign(VALIGN_CENTER);
            //设置行高度
            ws->rowheight(i,20*15);
        }
    }
    range *ran=ws->rangegroup(1,1,1,1);
    ran->cellcolor(CLR_GREEN);
    //保存到excel文件
    wb.Dump("mynew.xls");
    return 0;
}
