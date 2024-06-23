# This file is part of imgtol.
#
# imgtol is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# imgtol is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with imgtol.  If not, see <https://www.gnu.org/licenses/>.
home=$(dirname "$(readlink -f "$0")")
if [[ ${*} == "" ]];then
    build=imgsha
else
    build=${*}
fi

mkdir -p ${home}/opt

#DEBUG
if false;then
    debug="-fsanitize=address -fno-omit-frame-pointer -g"
fi

echo "Will build:${build}"
for item in ${build};do
    echo "Building:${item}"
    g++ ${debug} -Wall -Wextra -pedantic ${home}/${item}.cpp -o ${home}/opt/${item} `pkg-config --cflags --libs opencv4 openssl`
done
