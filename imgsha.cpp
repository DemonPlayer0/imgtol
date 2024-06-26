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
#include "shapixel.hpp"
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include "define.hpp"

int main(int argc,char* argv[]){
    char mode = UNDEFINED;
    char* inpath = nullptr;
    const char* outpath = nullptr;
    char* passwd = nullptr;
    char channel = 4;

    for(int opt = 0;(opt = getopt(argc,argv,"hve:d:p:o:c:"))!=-1;){
        switch(opt){
            case 'h':
                help();
                break;
            case 'v':
                version();
                break;
            case 'e':
                if(mode==ENCRYPTION){
                    printf("imgsha:-e cannot coexist with -e.\n");
                    exit(1);
                }
                if(mode==DECRYPT){
                    printf("imgsha:-e cannot coexist with -d.\n");
                    exit(1);
                }
                mode=ENCRYPTION;
                inpath=optarg;
                break;
            case 'd':
                if(mode==DECRYPT){
                    printf("imgsha:-d cannot coexist with -d.\n");
                    exit(1);
                }
                if(mode==ENCRYPTION){
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
            case 'c':
                if(channel!=0){
                    printf("imgsha:Cannot set the number of channels repeatedly.\n");
                    exit(1);
                }
                channel=atoi(optarg);
                if(channel<=0){
                    printf("imgsha:Invalid channels quantity.\n");
                    exit(0);
                }
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
        shapixel::V1(channel,passwd,inpath,outpath,1);
    }
    if(mode==DECRYPT){
        if(outpath==nullptr)outpath="unsha.png";
        shapixel::V1(channel,passwd,inpath,outpath,-1);
    }
}
