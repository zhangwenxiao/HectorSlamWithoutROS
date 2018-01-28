#ifndef HECTOR_MAPPING_ROS_H__
#define HECTOR_MAPPING_ROS_H__

#include <hokuyoaist/HectorSlamProcessor.h>

#include <hokuyoaist/DataPointContainer.h>
#include <hokuyoaist/MapLockerInterface.h>

#include <boost/thread.hpp>
#include <hokuyoaist/hokuyoaist.h>
#include <fstream>

#define M_PI  3.14159265358979323846
#define ANGLE_MIN -2.35619
#define ANGLE_MAX 2.35619
#define ANGLE_STEP  0.00436332
#define RANGE_MIN 23
#define RANGE_MAX 60000


class HectorDrawings;
class HectorDebugInfoProvider;

class HectorMappingRos
{
public:
  HectorMappingRos();
  ~HectorMappingRos();
  void getMap(std::vector<unsigned char>& map);
  void scanCallback(const hokuyoaist::ScanData& scan);
  bool rosLaserScanToDataContainer(const hokuyoaist::ScanData& scan, hectorslam::DataContainer& dataContainer, float scaleToMap);
protected:
  int lastGetMapUpdateIndex;

  hectorslam::HectorSlamProcessor* slamProcessor;
  hectorslam::DataContainer laserScanContainer;

  double p_update_factor_free_;
  double p_update_factor_occupied_;
  double p_map_update_distance_threshold_;
  double p_map_update_angle_threshold_;

  double p_map_resolution_;
  int p_map_size_;
  double p_map_start_x_;
  double p_map_start_y_;
  int p_map_multi_res_levels_;

  int debug_index;
  std::ofstream data_log_file;
};

#endif
