home=$(dirname "$(readlink -f "$0")")
if [[ ${*} == "" ]];then
    build=imgsha
else
    build=${*}
fi

mkdir -p ${home}/opt

echo "Will build:${build}"
for item in ${build};do
    echo "Building:${item}"
    g++ -Wall -Wextra -pedantic ${home}/${item}.cpp -o ${home}/opt/${item} `pkg-config --cflags --libs opencv4 openssl`
done
