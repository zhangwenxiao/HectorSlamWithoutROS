重构ros官方hector_slam代码
目的是使hector_slam算法脱离ROS平台

Linux版本:ubuntu14.04
cmake版本:3.9.6

使用方法:
创建build目录:
    mkdir build
进入build，依次执行:
    cmake ..
    make
    ./hectorslam

-------------------大改动------------------
重新整理目录，目前不再需要额外安装驱动
