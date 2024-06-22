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
#include <iostream>
#include <unistd.h>
#include "imgsha.hpp"
#include "sha.hpp"
#include <opencv2/opencv.hpp>
#include "define.hpp"

int main(int argc,char* argv[]){
    char mode = UNDEFINED;
    char* inpath = nullptr;
    const char* outpath = nullptr;
    char* passwd = nullptr;
    int channel = 4;
    
    for(int opt = 0;(opt = getopt(argc,argv,"hv3e:d:p:o:"))!=-1;){
        switch(opt){
            case 'h':
                help();
                break;
            case 'v':
                version();
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
                help();
                break;
        }
    }

    if(mode==UNDEFINED){
        help();
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
