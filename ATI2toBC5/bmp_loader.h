#ifndef BMP_LOADER_H_INCLUDED
#define BMP_LOADER_H_INCLUDED

typedef unsigned char BYTE;
typedef unsigned short US;
typedef unsigned int UINT;
typedef unsigned long UL;
typedef long L;

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <cmath>

using namespace std;

struct rgba_data{
    BYTE b;
    BYTE g;
    BYTE r;
    BYTE a;
};

struct rgb_data{
    BYTE b;
    BYTE g;
    BYTE r;
};

class BMPloader{
    private:

    #pragma pack(2)

    struct FILEheader{
        US type;
        UL fsize;//file size
        US res1;
        US res2;
        UL offset;
    };

    struct INFOheader{
        UL bsize;//bitmap size
        L width;
        L height;
        US plane;
        US bitcount;
        UL com;//compression
        UL sizei;//size image
        L Xpels;
        L Ypels;
        UL clru;
        UL clrI;

    };

    #pragma pack(8)

    L width;
    L height;
    US depth;
    UL row_size;
    BYTE* p_data;

    FILEheader fheader;
    INFOheader iheader;
    UINT cp_size;
    rgba_data* cp;


    public:

    BMPloader(){

    };
    ~BMPloader(){
        delete[] p_data;
        delete[] cp;
    };

    bool open(const char* path);
    bool save(const char* path);
    bool cpix(L x,L y,rgba_data clr);
    rgba_data rpix(L x,L y);
    L bwidth();
    L bheight();

};

bool BMPloader:: open(const char* path){

    ifstream in(path,ios::binary);

    if(!in.is_open()){
        printf("Failed to open file %s\n",path);
        return false;
    }


    in.read((char*)&fheader,sizeof(FILEheader));

    if (fheader.type != 0x4d42) // 0x4d42 = 'BM'
    {
        printf("File %s is not bmp file\n",path);
        return false;
    }

    in.read((char*)&iheader,sizeof(INFOheader));
    if(fheader.offset==54){
        cp=nullptr;
    }
    else {
        cp_size=(fheader.offset-54)/4;
        cp=new rgba_data[cp_size];
        in.read((char*)&cp,cp_size*sizeof(rgba_data));
    }
    width=iheader.width;
    height=iheader.height;
    depth=iheader.bitcount;

    //ul=unsigned long
    row_size=4ul * (iheader.bitcount * iheader.width / 32ul);

    p_data=new BYTE[iheader.sizei]();

    in.read((char*)p_data,iheader.sizei);

    in.close();
    return true;

}


bool BMPloader:: save(const char* path){

    ofstream out(path,ios::binary);

    if (!out.is_open()){
        printf("Failed to save image %s",path);
        return false;
    }

    out.write((char*)&fheader,sizeof(FILEheader));

    out.write((char*)&iheader,sizeof(INFOheader));

    out.write((char*)p_data,iheader.sizei);

    out.close();

    return true;

}

bool BMPloader:: cpix(L x,L y,rgba_data clr){

    int pix_size=iheader.bitcount/8;
    rgba_data* temp=nullptr;
    rgb_data* temp24=nullptr;

    int index;

    //cout<<"当前位图的色深为: "<<iheader.bitcount<<endl;
    if(height<0){

        index= (height-y-1)* row_size + x * pix_size;

    }
    else{

        index= y* row_size + x * pix_size;
    }
    if(pix_size==4){
        temp=(rgba_data*)(p_data+index);
        *temp=clr;
    }
    else{
        rgb_data clr24={clr.b,clr.g,clr.r};

        temp24=(rgb_data*)(p_data+index);
        *temp24=clr24;
    }

    return 1;

}

rgba_data BMPloader:: rpix(L x,L y){

    int pix_size=iheader.bitcount/8;
    int index;

    if(height<0){

        index= (height-y-1)* row_size + x * pix_size;

    }
    else{

        index= y* row_size + x * pix_size;
    }

    rgba_data* r=(rgba_data*)(p_data+index);
    rgba_data load;
    load.r=r->r;
    load.g=r->g;
    load.b=r->b;
    load.a=r->a;
    return load;

}

L BMPloader:: bwidth(){
    return width;
}

L BMPloader:: bheight(){
    return height;
}

#endif // BMP_LOADER_H_INCLUDED
