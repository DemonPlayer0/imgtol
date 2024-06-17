namespace inpproc{
    using namespace std;
    inline void help_imgsha(){
        cout <<
R"(usage:imgsha [-e[-b]|-d[-o]]

-h
    Get help text.
-v
    Get version code and info.
-e <path>
    Encryption a image.
-d <path>
    Decrypt a image.
-p <password>
    Set encryption or decrypt password.
-o <path>
    Set output path.
-3
    Disable alpha channel.
)" << endl;
        exit(0);
    }
    inline void version_imgsha(){
        cout <<
R"(imgsha classic version

--ART IS NOT A MOSAIC--
)" << endl;
        exit(0);
    }
}
