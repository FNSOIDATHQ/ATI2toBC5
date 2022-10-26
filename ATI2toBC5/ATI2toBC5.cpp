#include "bmp_loader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;


int main(){

    cout<<"��ǰ���ڽ���ATI2��ʽת��BC5��ʽ���� ע�⣡������ֻ֧��BMP��ʽ�����������ת������Ҫ�ֶ���ԭ��DDS��ʽ��"<<endl<<endl;

    BMPloader test;

    string name_in;
    stringstream ss;
    cout<<"������Ҫ��ȡ���ļ�����";
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
                long double uncomb=abs((long double)1-uncomr*uncomr-uncomg*uncomg);//����ȫ��ȷ����ʱֻ��ʹ��abs���������ܼ�С���

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
    cout<<"������Ҫ������ļ�����";
    cin>>name_out;
    char* name_out_c=new char[name_out.length()];
    ss<<name_out;
    ss>>name_out_c;
    test.save(name_out_c);


}
