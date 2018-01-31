#include <flexiport/flexiport.h>
#include <hokuyoaist/hokuyoaist.h>
#include <hokuyoaist/hokuyo_errors.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <cv.h>
#include <highgui.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <hokuyoaist/HectorMappingRos.h>

hokuyoaist::Sensor laser; // Laser scanner object
HectorMappingRos hector_slam; //hector slam object
IplImage* LaserImage;
IplImage* LaserImage2;


std::string port_options("type=serial,device=/dev/ttyACM0,timeout=1");
double start_angle(0.0), end_angle(0.0);
int first_step(-1), last_step(-1);
int multiecho_mode(0);
unsigned int speed(0), cluster_count(1);
bool get_intensities(false), get_new(false), verbose(false);

typedef boost::mutex::scoped_lock scoped_lock;
const int BUF_SIZE = 5;

boost::mutex io_mutex;

class buffer
{
public:
        buffer(): p(0), c(0), full(0){}

        void put(hokuyoaist::ScanData& data)
        {
                scoped_lock lock(mutex);
                if(full == BUF_SIZE)
                {
                    /*
                        {
                                scoped_lock lock(io_mutex);
                                std::cout << "Buffer is full. Clean it..." << std::endl;
                        }
                        */
                        p = 0;
                        c = 0;
                        full = 0;
                }
                buf[p] = data;
                p = (p + 1) % BUF_SIZE;
                full++;
                cond.notify_one();
        }

        hokuyoaist::ScanData get()
        {
                scoped_lock lk(mutex);
                if(full == 0)
                {
                         {
                                //scoped_lock lock(io_mutex);
                                //std::cout << "Buffer is empty. Waiting..." << std::endl;

                                
                        }
                        while(full == 0)
                        cond.wait(lk);
                }
                hokuyoaist::ScanData result = buf[c];
                c = (c + 1) % BUF_SIZE;
                full--;
                return result;
        }
private:
        boost::mutex mutex;
        boost::condition cond;
        unsigned int p, c, full;
        hokuyoaist::ScanData buf[BUF_SIZE];
};

buffer buf;

void laserDataWriter()//读雷达数据的线程
{
        while(1)
        {
                hokuyoaist::ScanData data;

                if((first_step == -1 && last_step == -1) &&
                    (start_angle == 0.0 && end_angle == 0.0))
                {
                    // Get all ranges
                    if(get_new)
                    {
                        laser.get_new_ranges(data, -1, -1, cluster_count);
                    }
                    else if(get_intensities)
                    {
                        laser.get_new_ranges_intensities(data, -1, -1, cluster_count);
                    }
                    else
                    {
                        laser.get_ranges(data, -1, -1, cluster_count);
                    }
                }
                else if(first_step != -1 || last_step != -1)
                {
                    
                    // Get by step
                    if(get_new)
                    {
                        laser.get_new_ranges(data, first_step, last_step,
                                cluster_count);
                    }
                    else if(get_intensities)
                    {
                        laser.get_new_ranges_intensities(data, first_step, last_step,
                                cluster_count);
                    }
                    else
                    {
                        laser.get_ranges(data, first_step, last_step, cluster_count);
                    }
                }
                else
                {
                    
                    // Get by angle
                    if(get_new)
                    {
                        laser.get_new_ranges_by_angle(data, start_angle, end_angle,
                                cluster_count);
                    }
                    else if(get_intensities)
                    {
                        laser.get_new_ranges_intensities_by_angle(data, start_angle,
                                end_angle, cluster_count);
                    }
                    else
                    {
                        laser.get_ranges_by_angle(data, start_angle, end_angle,
                                cluster_count);
                    }
                }

                buf.put(data);
        }
}

void showLaserDataInPic(const hokuyoaist::ScanData& data)
{
                            cvZero(LaserImage2);
                            cvShowImage("Laser2", LaserImage2);
                            cvWaitKey(2);

                            int x,y;
                            double theta,rho;
                            unsigned char * pPixel = 0;
                            int halfWidth  = 512;
                            int halfHeight = 512;
                            theta = ANGLE_MIN_DATA;

                            for (int i = 0; i < data.ranges_length();i++)
                            {
                                rho = *(data.ranges() + i);

                                x = (int)rho*cos(theta) / 10 + 512;
                                y = (int)-rho*sin(theta) /10 + 512;

                                if (x >= 0 && x < 1024 && y >= 0 && y < 1024)
                                {
                                    pPixel = (unsigned char*)LaserImage2->imageData + y*LaserImage2->widthStep + x;
                                    *pPixel = 255;
                                }
                                theta += ANGLE_STEP;
                            }

                            cvCircle(LaserImage2, cvPoint(512,512),3, 255, -1, 8,0);
                            cvLine(LaserImage2, cvPoint(512, 512), cvPoint(600, 512), 255);
                            cvLine(LaserImage2, cvPoint(512,512), cvPoint(512, 424), 255);

                            cvShowImage("Laser2",LaserImage2);
                            cvWaitKey(2);
}

void showLaserDataInPic(const std::vector<float>& data)
{
                            cvZero(LaserImage2);
                            cvShowImage("Laser2", LaserImage2);
                            cvWaitKey(2);

                            int x,y;
                            double theta,rho;
                            unsigned char * pPixel = 0;
                            int halfWidth  = 512;
                            int halfHeight = 512;
                            theta = ANGLE_MIN;

                            for (int i = 0; i < data.size();i++)
                            {
                                rho = data[i];

                                x = (int)rho*cos(theta)  + 512;
                                y = (int)-rho*sin(theta) + 512;

                                if (x >= 0 && x < 1024 && y >= 0 && y < 1024)
                                {
                                    pPixel = (unsigned char*)LaserImage2->imageData + y*LaserImage2->widthStep + x;
                                    *pPixel = 255;
                                }
                                theta += ANGLE_STEP;
                            }

                            cvCircle(LaserImage2, cvPoint(512,512),3, 255, -1, 8,0);
                            cvLine(LaserImage2, cvPoint(512, 512), cvPoint(600, 512), 255);
                            cvLine(LaserImage2, cvPoint(512,512), cvPoint(512, 424), 255);

                            cvShowImage("Laser2",LaserImage2);
                            cvWaitKey(2);
}

void mapReader()//显示地图的线程last modify
{
        LaserImage = cvCreateImage(cvSize(1024, 1024), IPL_DEPTH_8U, 1);//new opencv image used for show laser points
        cvNamedWindow("Laser", 1);

        std::vector<unsigned char> map;
        unsigned char * pPixel = NULL;
        int x, y;
        int robotindex;
        float angle;

        while(1)
        {
                cvZero(LaserImage);
                cvShowImage("Laser", LaserImage);
                cvWaitKey(2);

                hector_slam.getMap(map, angle);

                size_t size = map.size();

                for(size_t i = 0; i < size; i++)
                {
                    x = i % 1024;
                    y = i / 1024;
                    pPixel = (unsigned char*)LaserImage -> imageData + y * LaserImage -> widthStep + x;
                    if(map[i] != 100)
                        *pPixel = map[i];
                    else
                    {
                        robotindex = i;
                    }        
                }

                int robotX = robotindex % 1024;
                int robotY = robotindex / 1024;
                cvCircle(LaserImage, cvPoint(robotX, robotY), 3, 255, -1, 8, 0);
                cvLine(LaserImage, cvPoint(robotX, robotY), cvPoint(robotX + (int)(cos(angle) * 20), robotY + (int)(sin(angle) * 20)), 255);
                cvLine(LaserImage, cvPoint(robotX, robotY), cvPoint(robotX + (int)(cos(angle + M_PI / 2) * 20), robotY + (int)(sin(angle + M_PI / 2) * 20)), 255);

                cvShowImage("Laser", LaserImage);
                cvWaitKey(10);
        }
}

void laserDataReader()//雷达数据处理进程(hector slam)
{
    //LaserImage2 = cvCreateImage(cvSize(1024, 1024), IPL_DEPTH_8U, 1);//new opencv image used for show laser points
    //cvNamedWindow("Laser2", 1);

	while(1)
	{

		hokuyoaist::ScanData data = buf.get();


                            //std::cout << data.as_string() << std::endl;
//show raw data
                            //showLaserDataInPic(data);                    

//show raw data
                            Eigen::Vector3f poseMap = Eigen::Vector3f::Zero();
                            Eigen::Vector3f poseUpdate = Eigen::Vector3f::Zero();
                            Eigen::Vector3f poseMatch = Eigen::Vector3f::Zero();
                            std::vector<float> dataContainer;

		hector_slam.scanCallback(data, true, dataContainer);
                            hector_slam.getPose(poseMap, poseUpdate, poseMatch);

                            std::cout << "poseMap: " << poseMap[0] << " , " << poseMap[1] << " , " << poseMap[2] << std::endl;
                            std::cout << "poseUpdate: " << poseUpdate[0] << " , " << poseUpdate[1] << " , " << poseUpdate[2] << std::endl;
                            std::cout << "poseMatch: " << poseMatch[0] << " , " << poseMatch[1] << " , " << poseMatch[2] << std::endl;

                            //showLaserDataInPic(dataContainer);//last modify                    
	}
}

int main(int argc, char **argv)
{
#if defined(WIN32)
    port_options = "type=serial,device=COM4,timeout=1";
#else
    int opt;
    // Get some options from the command line
    while((opt = getopt(argc, argv, "b:c:e:f:il:m:no:s:u:vh")) != -1)
    {
        switch(opt)
        {
            case 'c':
                sscanf(optarg, "%d", &cluster_count);
                break;
            case 'e':
                sscanf(optarg, "%lf", &end_angle);
                break;
            case 'f':
                sscanf(optarg, "%d", &first_step);
                break;
            case 'i':
                get_intensities = true;
                break;
            case 'l':
                sscanf(optarg, "%d", &last_step);
                break;
            case 'm':
                sscanf(optarg, "%d", &speed);
                break;
            case 'n':
                get_new = true;
                break;
            case 'o':
                port_options = optarg;
                break;
            case 's':
                sscanf(optarg, "%lf", &start_angle);
                break;
            case 'u':
                sscanf(optarg, "%d", &multiecho_mode);
                break;
            case 'v':
                verbose = true;
                break;
            case '?':
            case 'h':
            default:
                std::cout << "Usage: " << argv[0] << " [options]\n\n";
                std::cout << "-c count\tCluster count.\n";
                std::cout << "-e angle\tEnd angle to get ranges to.\n";
                std::cout << "-f step\t\tFirst step to get ranges from.\n";
                std::cout << "-i\t\tGet intensity data along with ranges.\n";
                std::cout << "-l step\t\tLast step to get ranges to.\n";
                std::cout << "-m speed\tMotor speed.\n";
                std::cout <<
                    "-n\t\tGet new ranges instead of latest ranges.\n";
                std::cout <<
                    "-o options\tPort options (see flexiport library).\n";
                std::cout << "-s angle\tStart angle to get ranges from.\n";
                std::cout << "-u mode\tMulti-echo detection:\n";
                std::cout << "\t\t0: Off (default), 1: Front, 2: Middle, "
                    "3: Rear, 4: Average\n";
                std::cout <<
                    "-v\t\tPut the hokuyoaist library into verbose mode.\n";
                return 1;
        }
    }
#endif // defined(WIN32)

    try
    {
        
        // Set the laser to verbose mode (so we see more information in the
        // console)
        if(verbose)
        {
            laser.set_verbose(true);
        }

        // Open the laser
        laser.open(port_options);

        // Calibrate the laser time stamp
        std::cout << "Calibrating laser time\n";
        laser.calibrate_time();
        std::cout << "Calculated offset: " << laser.time_offset() << "ns\n";
        std::cout << "Calculated drift rate: " << laser.drift_rate() << '\n';
        std::cout << "Calculated skew alpha: " << laser.skew_alpha() << '\n';

        // Turn the laser on
        laser.set_power(true);
        // Set the motor speed
        try
        {
            laser.set_motor_speed(speed);
        }
        catch(hokuyoaist::MotorSpeedError &e)
        {
            std::cerr << "Failed to set motor speed: " << e.what() << '\n';
        }
        catch(hokuyoaist::ResponseError &e)
        {
            std::cerr << "Failed to set motor speed: " << e.what() << '\n';
        }
        // Set multiecho mode
        switch(multiecho_mode)
        {
            case 1:
                laser.set_multiecho_mode(hokuyoaist::ME_FRONT);
                break;
            case 2:
                laser.set_multiecho_mode(hokuyoaist::ME_MIDDLE);
                break;
            case 3:
                laser.set_multiecho_mode(hokuyoaist::ME_REAR);
                break;
            case 4:
                laser.set_multiecho_mode(hokuyoaist::ME_AVERAGE);
                break;
            case 0:
            default:
                laser.set_multiecho_mode(hokuyoaist::ME_OFF);
                break;
        }

        // Get some laser info
        std::cout << "Laser sensor information:\n";
        hokuyoaist::SensorInfo info;
        laser.get_sensor_info(info);
        std::cout << info.as_string();
        //add

        boost::thread thrd1(&laserDataWriter);//雷达数据获取
        boost::thread thrd2(&laserDataReader);//hector_slam
        boost::thread thrd3(&mapReader);//opencv显示地图
        thrd1.join();
        thrd2.join();
        thrd3.join();

        // Close the laser
        laser.close();
    }
    catch(hokuyoaist::BaseError &e)
    {
        std::cerr << "Caught exception: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

