#include <iostream>
#include <unistd.h>
#include "InputProcessor.hpp"
#include "sha.hpp"
#include <opencv2/opencv.hpp>

#define UNDEFINED 0
#define ENCRYPTION 1
#define DECRYPT 2

int main(int argc,char* argv[]){
    char mode = UNDEFINED;
    char* inpath = nullptr;
    const char* outpath = nullptr;
    char* passwd = nullptr;
    int channel = 4;

    int opt = 0;
    while((opt = getopt(argc,argv,"hv3e:d:p:o:"))!=-1){
        switch(opt){
            case 'h':
                inpproc::help_imgsha();
                break;
            case 'v':
                inpproc::version_imgsha();
                break;
            case 'e':
                if(mode!=UNDEFINED){
                    printf("imgsha:-e cannot coexist with -d.\n");
                    exit(1);
                }
                mode=ENCRYPTION;
                inpath=optarg;
                break;
            case 'd':
                if(mode!=UNDEFINED){
                    printf("imgsha:-d cannot coexist with -e.\n");
                    exit(1);
                }
                mode=DECRYPT;
                inpath=optarg;
                break;
            case 'p':
                if(passwd!=nullptr){
                    printf("imgsha:Cannot set password repeatedly.\n");
                    exit(1);
                }
                passwd=optarg;
                break;
            case 'o':
                if(outpath!=nullptr){
                    printf("imgsha:Cannot set output path repeatedly.\n");
                    exit(1);
                }
                outpath=optarg;
                break;
            case '3':
                channel=3;
                break;
            default:
                inpproc::help_imgsha();
                break;
        }
    }
    if(mode==UNDEFINED){
        inpproc::help_imgsha();
    }

    if(passwd==nullptr){
        printf("imgshu:Must be set password.\n");
        exit(1);
    }
    if(mode==ENCRYPTION){
        if(outpath==nullptr)outpath="sha.png";
        shaPixel::V1(channel,passwd,inpath,outpath,1);
    }
    if(mode==DECRYPT){
        if(outpath==nullptr)outpath="unsha.png";
        shaPixel::V1(channel,passwd,inpath,outpath,-1);
    }
}
