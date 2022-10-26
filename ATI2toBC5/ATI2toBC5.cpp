#include "bmp_loader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;


int main(){

    cout<<"当前正在进行ATI2格式转换BC5格式操作 注意！本程序只支持BMP格式的输入输出，转换后还需要手动还原成DDS格式。"<<endl<<endl;

    BMPloader test;

    string name_in;
    stringstream ss;
    cout<<"请输入要读取的文件名：";
    cin>>name_in;
    char* name_in_c=new char[name_in.length()];
    ss<<name_in;
    ss>>name_in_c;

    test.open(name_in_c);
    //test.open("test.bmp");

    //cout<<test.bwidth()<<endl;
    //cout<<test.bheight()<<endl;

    for(int i=0;i<test.bwidth();i++)
    for(int j=0;j<test.bheight();j++){
            rgba_data curclr;
            curclr=test.rpix(i,j);
            curclr.a=curclr.r;
            //if(i==1&&j==1){
                /*
                double uncomr=(double)(2*curclr.r-1)/256;
                double uncomg=(double)(2*curclr.g-1)/256;
                double uncomb=(sqrt(1-uncomr*uncomr-uncomg*uncomg)+1)/2*256;
                */

                long double uncomr=(long double)curclr.r/(255/2);
                uncomr=uncomr-1;
                long double uncomg=(long double)curclr.g/(255/2);
                uncomg=uncomg-1;
                long double uncomb=abs((long double)1-uncomr*uncomr-uncomg*uncomg);//不完全正确，暂时只是使用abs函数尽可能减小误差

                //if(i==1&&j==1)cout<<uncomb<<endl;

                uncomb=(sqrt(uncomb)+1.0)*(255.0/2.0);

                curclr.b=uncomb;
                //cout<<uncomr<<' '<<uncomg<<' '<<uncomb<<endl;
            //}

            //curclr.b=sqrt(255-curclr.r*curclr.r-curclr.g*curclr.g);
            curclr.r=0;

            test.cpix(i,j,curclr);
    }


    string name_out;
    ss.clear();
    cout<<"请输入要保存的文件名：";
    cin>>name_out;
    char* name_out_c=new char[name_out.length()];
    ss<<name_out;
    ss>>name_out_c;
    test.save(name_out_c);


}
