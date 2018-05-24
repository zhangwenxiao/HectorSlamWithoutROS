#ifndef HECTOR_MAPPING_ROS_H__
#define HECTOR_MAPPING_ROS_H__

#include "HectorSlamProcessor.h"

#include "DataPointContainer.h"
#include "MapLockerInterface.h"

#include <boost/thread.hpp>
#include "hokuyoaist.h"
#include <fstream>

#include "boost/numeric/ublas/matrix.hpp"
#include "boost/thread/mutex.hpp"
#include <Eigen/Core>

#define M_PI  3.14159265358979323846
#define ANGLE_MIN_DATA -2.35619
#define ANGLE_MAX_DATA 2.35619
#define ANGLE_MIN -1.57079637051
#define ANGLE_MAX 1.56643295288
#define ANGLE_STEP  0.00436332309619
#define RANGE_MIN 0.0230000000447
#define RANGE_MAX 60.0

struct Point
{
  float x;
  float y;
  float z;
};

struct PointCloud
{
  std::vector<Point> points;
};


class HectorDrawings;
class HectorDebugInfoProvider;

class HectorMappingRos
{
public:
  HectorMappingRos();
  ~HectorMappingRos();
  void getPose(Eigen::Vector3f& poseUpdateMap, Eigen::Vector3f& poseUpdateWorld, Eigen::Vector3f& poseMatch);
  void getMap(std::vector<unsigned char>& map, float& angle);
  void scanCallback(const hokuyoaist::ScanData& scan, bool usePointCloud, std::vector<float>& getData);
  bool rosLaserScanToDataContainer(const hokuyoaist::ScanData& scan, hectorslam::DataContainer& dataContainer, float scaleToMap);
  void laserToPointCloud(const hokuyoaist::ScanData& scan_in, PointCloud& cloud_out, double range_cutoff);
  bool rosPointCloudToDataContainer(PointCloud& pointCloud, hectorslam::DataContainer& dataContainer, float scaleToMap);
  const boost::numeric::ublas::matrix<double>& getUnitVectors_(double angle_min, double angle_max, double angle_increment, unsigned int length);
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

  float p_sqr_laser_min_dist_;
  float p_sqr_laser_max_dist_;
  float p_laser_z_min_value_;
  float p_laser_z_max_value_;

  std::map<std::string,boost::numeric::ublas::matrix<double>* > unit_vector_map_;
  boost::mutex guv_mutex_;

  int debug_index;
  std::ofstream data_log_file;
  std::vector<float> dataGet;
};

#endif
