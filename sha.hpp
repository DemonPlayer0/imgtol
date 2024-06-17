#include <opencv2/opencv.hpp>
#include <openssl/sha.h>
#include <iostream>

#define DEBUG 1

static inline void sha(unsigned long long code[4],int height,int width){
    unsigned int hashcode[10];
    hashcode[8]=height;
    hashcode[9]=width;
    memcpy(hashcode,code,4*sizeof(unsigned long long));
    SHA256(reinterpret_cast<const unsigned char*>(hashcode),sizeof(unsigned int)*10,reinterpret_cast<unsigned char*>(code));
}

namespace shaPixel{
//    struct Range{
//        unsigned int rx;
//        unsigned int ry;
//        unsigned int x1;
//        unsigned int y1;
//        unsigned int x2;
//        unsigned int y2;
//    };
    inline void V1(const char channel,const char* passwd,const char* inpath,const char* outputpath,int delta){
        cv::Mat image = cv::imread(inpath);
        if(image.empty()){
            printf("imgsha:Can't get image for path.\n");
            exit(2);
        }

        unsigned long long shapasswd[4];
        SHA256(reinterpret_cast<const unsigned char*>(passwd),strlen(passwd),reinterpret_cast<unsigned char*>(shapasswd));

        const int width = image.cols;
        const int height = image.rows;
        #ifdef DEBUG
        printf("width:%d,height:%d\n",width,height);
        #endif
        if(channel==4)
        for(int y = 0;y<height;y++){
            for(int x = 0;x<width;x++){
                sha(shapasswd,x,y);
                cv::Vec4b pixel = image.at<cv::Vec4b>(y,x);
                for(int i = 0;i<4;i++){
                    pixel[i]+=(shapasswd[i]*delta);
                }
                image.at<cv::Vec4b>(y,x)=pixel;
            }
        }

        if(channel==3)
        for(int y = 0;y<height;y++){
            for(int x = 0;x<width;x++){
                sha(shapasswd,x,y);
                cv::Vec3b pixel = image.at<cv::Vec3b>(y,x);
                for(int i = 0;i<3;i++){
                    pixel[i]+=shapasswd[i];
                }
                image.at<cv::Vec3b>(y,x)=pixel;
            }
        }
        #ifdef DEBUG
        printf("finish.\n");
        #endif
        if(!cv::imwrite(outputpath,image)){
            printf("imgshu:Can't write image for %s\n",outputpath);
            exit(255);
        }
    }
}
