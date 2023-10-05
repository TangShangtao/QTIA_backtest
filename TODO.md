开发环境注意事项记录
1.gcc 11.2.0(存在多版本gcc时, 需指定正确版本的gcc, 在.bashrc中添加:
export LD_LIBRARY_PATH="/usr/local/lib64:$LD_LIBRARY_PATH"
export CC="/usr/local/bin/gcc"
export CXX="/usr/local/bin/g++")
2.cmake 3.27
3.可以连接github
TODO
找一个Ubuntu高点的发行版, 支持apt-get安装gcc 11.2.0和cmake 3.27
兼容msvc
