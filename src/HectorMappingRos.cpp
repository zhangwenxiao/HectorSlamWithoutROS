#include "HectorMappingRos.h"
#include "GridMap.h"
#include "HectorMapMutex.h"
#include <fstream>

HectorMappingRos::HectorMappingRos(): lastGetMapUpdateIndex(-100)
{
  p_map_resolution_ = 0.025;//0.025
  p_map_size_ = 1024;
  p_map_start_x_ = 0.5; 
  p_map_start_y_ = 0.5;
  p_map_multi_res_levels_ = 3;
  p_update_factor_free_ = 0.4;
  p_update_factor_occupied_ = 0.9;
  p_map_update_distance_threshold_ = 0.4;
  p_map_update_angle_threshold_ = 0.9;

  p_sqr_laser_min_dist_ = static_cast<float>(0.4 * 0.4);
  p_sqr_laser_max_dist_ = static_cast<float>(30 * 30);
  p_laser_z_min_value_ = static_cast<float>(-1.0);
  p_laser_z_max_value_ = static_cast<float>(1.0);

  slamProcessor = new hectorslam::HectorSlamProcessor(static_cast<float>(p_map_resolution_), 
                                                      p_map_size_, p_map_size_, 
                                                      Eigen::Vector2f(p_map_start_x_, p_map_start_y_), 
                                                      p_map_multi_res_levels_);
  slamProcessor->setUpdateFactorFree(p_update_factor_free_);
  slamProcessor->setUpdateFactorOccupied(p_update_factor_occupied_);
  slamProcessor->setMapUpdateMinDistDiff(p_map_update_distance_threshold_);
  slamProcessor->setMapUpdateMinAngleDiff(p_map_update_angle_threshold_);

  debug_index = 0;
  data_log_file.open("dataContainer_log.txt");
}

HectorMappingRos::~HectorMappingRos()
{
  delete slamProcessor;

  std::map<std::string, boost::numeric::ublas::matrix<double>*>::iterator it;
  it = unit_vector_map_.begin();
  while (it != unit_vector_map_.end())
   {
     delete (*it).second;
     it++;
   }

  data_log_file.close();
}
//modify this function
void HectorMappingRos::laserToPointCloud(const hokuyoaist::ScanData& scan_in, PointCloud& cloud_out, double range_cutoff)
{
  size_t size = scan_in.ranges_length();

  int beginIndex = (ANGLE_MAX_DATA - ANGLE_MAX) / ANGLE_STEP;

  boost::numeric::ublas::matrix<double> ranges(2, size - 2 * beginIndex);

  //dataGet.clear();
  //dataGet.resize(size - 2 * beginIndex);
  //int indexForDataGet = 0;

  unsigned int indexForRanges = 0;
  for (unsigned int index = beginIndex; index < size - beginIndex; index++)
  {

    ranges(0,indexForRanges) = (double) *(scan_in.ranges() + index) / 1000.0;
    ranges(1,indexForRanges) = (double) *(scan_in.ranges() + index) / 1000.0;

    //dataGet[indexForDataGet++] = (double) *(scan_in.ranges() + index) / 1000.0 * slamProcessor->getScaleToMap();

    indexForRanges++;
  }

  //dataGet.resize(indexForDataGet);

  boost::numeric::ublas::matrix<double> output = element_prod(ranges, 
                                                                                                                getUnitVectors_(ANGLE_MIN, ANGLE_MAX, ANGLE_STEP, 
                                                                                                                                            size - 2 * beginIndex));

  cloud_out.points.resize (size - 2 * beginIndex);

  if (range_cutoff < 0)
    range_cutoff = RANGE_MAX;
  else
    range_cutoff = std::min(range_cutoff, (double)RANGE_MAX); 

  unsigned int count = 0;
  for (unsigned int index = 0; index< size - 2 * beginIndex; index++)
  {
   if ((ranges(0,index) < range_cutoff) && (ranges(0,index) >= RANGE_MIN)) //if valid or preservative
   {
       
     cloud_out.points[count].x = output(0,index);
     cloud_out.points[count].y = output(1,index);
     cloud_out.points[count].z = 0.0;
     
     count++;
   }
  }

  cloud_out.points.resize (count);
}

void HectorMappingRos::scanCallback(const hokuyoaist::ScanData& scan, bool usePointCloud, std::vector<float>& getData)
{
  if(!usePointCloud)
  {
    if (rosLaserScanToDataContainer(scan, laserScanContainer,slamProcessor->getScaleToMap()))
      slamProcessor->update(laserScanContainer,slamProcessor->getLastScanMatchPose());
  }
  else
  {
      PointCloud laser_point_cloud;
      laserToPointCloud(scan, laser_point_cloud, 30);
      if(rosPointCloudToDataContainer(laser_point_cloud, laserScanContainer, slamProcessor->getScaleToMap()))
        slamProcessor->update(laserScanContainer,slamProcessor->getLastScanMatchPose());
  }
  getData = dataGet;
}

const boost::numeric::ublas::matrix<double>& HectorMappingRos::getUnitVectors_(double angle_min, double angle_max, double angle_increment, unsigned int length)
  {
    boost::mutex::scoped_lock guv_lock(this->guv_mutex_);

    //construct string for lookup in the map
    std::stringstream anglestring;
    anglestring <<angle_min<<","<<angle_max<<","<<angle_increment<<","<<length;
    std::map<std::string, boost::numeric::ublas::matrix<double>* >::iterator it;
    it = unit_vector_map_.find(anglestring.str());
    //check the map for presense
    if (it != unit_vector_map_.end())
     return *((*it).second);     //if present return

    boost::numeric::ublas::matrix<double> * tempPtr = new boost::numeric::ublas::matrix<double>(2,length);
    for (unsigned int index = 0;index < length; index++)
     {
       (*tempPtr)(0,index) = cos(angle_min + (double) index * angle_increment);
       (*tempPtr)(1,index) = sin(angle_min + (double) index * angle_increment);
     }
    //store 
    unit_vector_map_[anglestring.str()] = tempPtr;
    //and return
    return *tempPtr;
  };
//modify this function
bool HectorMappingRos::rosPointCloudToDataContainer(PointCloud& pointCloud, hectorslam::DataContainer& dataContainer, float scaleToMap)
{
  size_t size = pointCloud.points.size();

  dataContainer.clear();

  Eigen::Vector3f laserPos (Eigen::Vector3f::Zero());//雷达坐标系在机器人坐标系中的位置
  dataContainer.setOrigo(Eigen::Vector2f(laserPos.x(), laserPos.y())*scaleToMap);

  dataGet.clear();
  dataGet.resize(size);
  int indexForDataGet = 0;

  for (size_t i = 0; i < size; ++i)
  {

    const Point& currPoint(pointCloud.points[i]);

    float dist_sqr = currPoint.x*currPoint.x + currPoint.y* currPoint.y;
    

    if ( (dist_sqr > p_sqr_laser_min_dist_) && (dist_sqr < p_sqr_laser_max_dist_) ){

      if ( (currPoint.x < 0.0f) && (dist_sqr < 0.50f)){
        continue;
      }

      float pointPosLaserFrameZ = currPoint.z - laserPos.z();

      if (pointPosLaserFrameZ > p_laser_z_min_value_ && pointPosLaserFrameZ < p_laser_z_max_value_)
      {
        dataContainer.add(Eigen::Vector2f(currPoint.x, currPoint.y) * scaleToMap);
        dataGet[indexForDataGet++] = sqrt(dist_sqr) * scaleToMap;
      }
    }
  }

  dataGet.resize(indexForDataGet);
  return true;
}

//需要修改
bool HectorMappingRos::rosLaserScanToDataContainer(const hokuyoaist::ScanData& scan, hectorslam::DataContainer& dataContainer, float scaleToMap)
{
  size_t size = scan.ranges_length();

  int beginIndex = (ANGLE_MAX_DATA - ANGLE_MAX) / ANGLE_STEP;

  float angle = ANGLE_MIN;

  dataContainer.clear();

  dataContainer.setOrigo(Eigen::Vector2f::Zero());

  float maxRangeForContainer = RANGE_MAX - 0.1f;

  dataGet.clear();//
  dataGet.resize(size - 2 * beginIndex);//
  int indexForDataGet = 0;//

  for (size_t i = beginIndex; i < size - beginIndex; ++i)
  {
    float dist = *(scan.ranges() + i);
    dist = dist /  1000;//mm => m

    if ( (dist > RANGE_MIN) && (dist < maxRangeForContainer))
    {
      dist *= scaleToMap;
      dataGet[indexForDataGet++] = dist;//
      dataContainer.add(Eigen::Vector2f(cos(angle) * dist, sin(angle) * dist));
    }
    angle += ANGLE_STEP;
  }

  dataGet.resize(indexForDataGet);//

  return true;
}

void HectorMappingRos::getMap(std::vector<unsigned char>& map, float& angle)
{
  const hectorslam::GridMap& gridMap = slamProcessor->getGridMap(0);
  MapLockerInterface* mapMutex = slamProcessor->getMapMutex(0);

  if (lastGetMapUpdateIndex != gridMap.getUpdateIndex())
  {
    map.clear();

    int sizeX = gridMap.getSizeX();
    int sizeY = gridMap.getSizeY();

    int size = sizeX * sizeY;

    map.resize(size);

    if (mapMutex)
    {
      mapMutex->lockMap();
    }

    for(int i=0; i < size; ++i)
    {
      if(!gridMap.isUpdated(i))
      {
        map[i] = 10;//not updated
      }
      else if(gridMap.isFree(i))
      {
        map[i] = 200;
      }
      else if(gridMap.isOccupied(i))
      {
        map[i] = 0;
      }
    }

    Eigen::Vector3f robotPose;
    slamProcessor -> getLastPoseMap(robotPose);

    int x = robotPose[0];
    int y = robotPose[1];
    angle = robotPose[2];

    int robotIndex = y * sizeX + x;

    if(robotIndex >= 0 && robotIndex < size)
      map[robotIndex] = 100;//robot coordinate


    lastGetMapUpdateIndex = gridMap.getUpdateIndex();

    if (mapMutex)
    {
      mapMutex->unlockMap();
    }

  }
}

void HectorMappingRos::getPose(Eigen::Vector3f& poseUpdateMap, Eigen::Vector3f& poseUpdateWorld, Eigen::Vector3f& poseMatch)
{
  slamProcessor -> getLastPoseMap(poseUpdateMap);
  poseUpdateWorld = slamProcessor -> getLastMapUpdatePose();
  poseMatch = slamProcessor -> getLastScanMatchPose();
}
