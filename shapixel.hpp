// This file is part of imgtol.
//
// imgtol is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// imgtol is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with imgtol.  If not, see <https://www.gnu.org/licenses/>.
#include <opencv2/opencv.hpp>
#include <openssl/sha.h>
#include <iostream>

static inline void sha(unsigned long long code[4],int height,int width){
    unsigned int hashcode[10];
    hashcode[8]=height;
    hashcode[9]=width;
    memcpy(hashcode,code,4*sizeof(unsigned long long));
    SHA256(reinterpret_cast<const unsigned char*>(hashcode),sizeof(unsigned int)*10,reinterpret_cast<unsigned char*>(code));
}

namespace shapixel{
    template<int channel_const>
    inline void scanPixel(cv::Mat image,unsigned long long shapasswd[4],const int delta){
        const int width = image.cols;
        const int height = image.rows;

        printf("width:%d,height:%d\n",width,height);

        for(int y = 0;y<height;y++){
            for(int x = 0;x<width;x++){
                sha(shapasswd,x,y);
                cv::Vec<uchar,channel_const> pixel = image.at<cv::Vec<uchar,channel_const>>(y,x);
                for(int i = 0;i<channel_const;i++){
                    pixel[i]+=(shapasswd[i]*delta);
                }
                image.at<cv::Vec<uchar,channel_const>>(y,x)=pixel;
            }
        }
    }
//    struct Range{
//        unsigned int rx;
//        unsigned int ry;
//        unsigned int x1;
//        unsigned int y1;
//        unsigned int x2;
//        unsigned int y2;
//    };
    inline void V1(char channel,const char* passwd,const char* inpath,const char* outputpath,int delta){
        cv::Mat image = cv::imread(inpath,cv::IMREAD_UNCHANGED);
        if(image.empty()){
            printf("imgsha:Can't get image for path.\n");
            exit(2);
        }
        if(channel>image.channels()){
            printf("The number of custom channels is too large,automatically set to:%d\n",(channel=image.channels()));
        }

        unsigned long long shapasswd[4];
        SHA256(reinterpret_cast<const unsigned char*>(passwd),strlen(passwd),reinterpret_cast<unsigned char*>(shapasswd));

        if(channel==4)scanPixel<4>(image,shapasswd,delta);
        if(channel==3)scanPixel<3>(image,shapasswd,delta);
        if(channel==2)scanPixel<2>(image,shapasswd,delta);
        if(channel==1)scanPixel<1>(image,shapasswd,delta);

        printf("finish.\n");

        if(!cv::imwrite(outputpath,image)){
            printf("imgshu:Can't write image for %s\n",outputpath);
            exit(255);
        }
    }
}
