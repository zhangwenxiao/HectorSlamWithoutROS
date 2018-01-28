#include <hokuyoaist/HectorMappingRos.h>
#include <hokuyoaist/GridMap.h>
#include <hokuyoaist/HectorMapMutex.h>
#include <fstream>

HectorMappingRos::HectorMappingRos(): lastGetMapUpdateIndex(-100)
{
  p_map_resolution_ = 25;
  p_map_size_ = 1024;
  p_map_start_x_ = 0.5; 
  p_map_start_y_ = 0.5;
  p_map_multi_res_levels_ = 3;
  p_update_factor_free_ = 0.4;
  p_update_factor_occupied_ = 0.9;
  p_map_update_distance_threshold_ = 0.4;
  p_map_update_angle_threshold_ = 0.9;

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
  data_log_file.close();
}

void HectorMappingRos::scanCallback(const hokuyoaist::ScanData& scan)
{
  if (rosLaserScanToDataContainer(scan, laserScanContainer,slamProcessor->getScaleToMap()))
  {
    slamProcessor->update(laserScanContainer,slamProcessor->getLastScanMatchPose());
  }
}

//需要修改
bool HectorMappingRos::rosLaserScanToDataContainer(const hokuyoaist::ScanData& scan, hectorslam::DataContainer& dataContainer, float scaleToMap)
{
  size_t size = scan.ranges_length();

  float angle = ANGLE_MIN;

  dataContainer.clear();

  dataContainer.setOrigo(Eigen::Vector2f::Zero());

  float maxRangeForContainer = RANGE_MAX - 0.1f;

  for (size_t i = 0; i < size; ++i)
  {
    float dist = *(scan.ranges() + i);

    if ( (dist > RANGE_MIN) && (dist < maxRangeForContainer))
    {
      dist *= scaleToMap;
      dataContainer.add(Eigen::Vector2f(cos(angle) * dist, sin(angle) * dist));
      if(debug_index == 0)
      {
            data_log_file << cos(angle) * dist << " , " << sin(angle) * dist << "\n";
      }
    }
    angle += ANGLE_STEP;
  }

  if(debug_index == 0)
  {
    debug_index++;
  }

  return true;
}

void HectorMappingRos::getMap(std::vector<unsigned char>& map)
{
  const hectorslam::GridMap& gridMap = slamProcessor->getGridMap(0);

  if (lastGetMapUpdateIndex != gridMap.getUpdateIndex())
  {
    map.clear();

    int sizeX = gridMap.getSizeX();
    int sizeY = gridMap.getSizeY();

    int size = sizeX * sizeY;

    map.resize(size);
/*
    if (mapMutex)
    {
      mapMutex->lockMap();
    }
*/
    for(int i=0; i < size; ++i)
    {
      if(gridMap.isFree(i))
      {
        map[i] = 0;
      }
      else if (gridMap.isOccupied(i))
      {
        map[i] = 255;
      }
    }

    Eigen::Vector3f robotPose;
    slamProcessor -> getLastPoseMap(robotPose);

    int x = robotPose[0];
    int y = robotPose[1];

    int robotIndex = x * p_map_size_ + y;

    if(robotIndex >= 0 && robotIndex < size)
      map[robotIndex] = 100;


    lastGetMapUpdateIndex = gridMap.getUpdateIndex();

/*
    if (mapMutex)
    {
      mapMutex->unlockMap();
    }
*/
  }
}
