#ifndef _HECTOR_SLAM_H_
#define _HECTOR_SLAM_H_

#include <hokuyoaist/CellOfMap.h>
#include <hokuyoaist/GridMap.h>
#include <hokuyoaist/scan_data.h>
#include <Eigen/Geometry>
#include <Eigen/LU>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>
#include <iostream>

#define M_PI	3.14159265358979323846
#define ANGLE_MIN	-2.35619
#define ANGLE_MAX	2.35619
#define ANGLE_STEP	0.00436332
#define RANGE_MIN	23
#define RANGE_MAX	60000

class HectorSlam
{
public:
	HectorSlam();
	//生成地图
	void createMap(float mapResolution);
	//把雷达扫描数据保存到dataContainer中，dataContainer中坐标点为机器人坐标系下的坐标，
	//且乘以地图缩放比例
	bool laserScanToDataContainer(const hokuyoaist::ScanData& data);
	//雷达扫描数据从这个接口传进来
	void processDataFromLaser(const hokuyoaist::ScanData& data);
	//更新机器人在世界坐标系下的姿态，如果姿态变化量大于阈值，还要更新地图
	void update(const Eigen::Vector3f& poseHintWorld);
	//更新地图
	void updateByScan(const Eigen::Vector3f& newPoseEstimateWorld);
	//更新地图核心函数
	void updateByScanCore(GridMap& gridMap, const std::vector<Eigen::Vector2f>& scanPoint, const Eigen::Vector3f& robotPoseWorld);
	//bresenham算法画线
	inline void updateLineBresenhami(GridMap& gridMap, const Eigen::Vector2i& beginMap, const Eigen::Vector2i& endMap);

  	inline void bresenhamCellOcc(GridMap& gridMap, unsigned int offset);

	inline void bresenhamCellFree(GridMap& gridMap, unsigned int offset);
  	//breseham的2D画线算法
  	inline void bresenham2D(GridMap& gridMap, 
  							unsigned int abs_da, unsigned int abs_db, 
  							int error_b, 
  							int offset_a, int offset_b, 
  							unsigned int offset);
	//匹配点云
	Eigen::Vector3f matchData(const Eigen::Vector3f& beginEstimateWorld);
	//匹配点云的算法核心函数
	Eigen::Vector3f matchDataCore(const Eigen::Vector3f& beginEstimateWorld,
								  const GridMap& gridMap,
								  const std::vector<Eigen::Vector2f>& scanPoint, 
								  int maxIterations);
	//计算hessian矩阵，并估计t时刻机器人的姿态
	bool estimateTransformationLogLh(Eigen::Vector3f& estimate, 
									 const GridMap& gridMap, 
									 const std::vector<Eigen::Vector2f>& scanPoint);
	//计算hessian矩阵
	void getCompleteHessianDerivs(const Eigen::Vector3f& pose, 
								  const GridMap& gridMap,
								  const std::vector<Eigen::Vector2f>& scanPoint, 
								  Eigen::Matrix3f& H, 
								  Eigen::Vector3f& dTr);
	//获得这个坐标点的值，用到插值算法
	Eigen::Vector3f interpMapValueWithDerivatives(const GridMap& gridMap, const Eigen::Vector2f& coords);

	inline int sign(int x);
	//把角度限制在-180 ~ 180范围内
	float normalize_angle(float angle);
	//把雷达扫描点坐标从高分辨率地图 => 低分辨率地图
	void setDataFromHighToLow(const std::vector<Eigen::Vector2f>& originData, std::vector<Eigen::Vector2f>& aimData, float factor);
	//判断机器人姿态变化量是否大于阈值
	bool poseDifferenceLargerThanThreshold(const Eigen::Vector3f& newPoseEstimateWorld);

	void getMap(std::vector<bool>& map); 
private:
	float p_map_resolution;//一个栅格对应的实际距离
	int p_map_size;//栅格地图一个轴的栅格数目
	float p_map_start_x;//世界坐标轴原点在地图坐标轴的位置，0.5代表中间
	float p_map_start_y;//同上
	int p_map_multi_res_levels;//多分辨率地图的数目
	float p_map_update_distance_threshold;//更新地图的距离增量阈值
	float p_map_update_angle_threshold;//更新地图的角度增量阈值
	float p_sqr_laser_min_dist;//小于此距离的扫描点丢弃
	float p_sqr_laser_max_dist;//大于此距离的扫描点丢弃
	float p_laser_z_min_value;//低于此高度的扫描点丢弃
	float p_laser_z_max_value;//高于此高度的扫描点丢弃

	std::vector<GridMap> mapContainer;//保存地图,下标0对应的地图分辨率最高，随着下标增加依次变低
	std::vector<std::vector<Eigen::Vector2f> > dataContainer;//保存转换后的雷达数据

	Eigen::Vector3f lastScanMatchPose;//上次扫描匹配时机器人在世界坐标系下的姿态
	Eigen::Vector3f lastMapUpdatePose;//上次地图更新时机器人在世界坐标系下的姿态
};

#endif
