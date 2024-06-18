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
