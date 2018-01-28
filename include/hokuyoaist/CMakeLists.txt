include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost REQUIRED COMPONENTS system thread)


set(hdrs hokuyoaist.h

    hokuyo_errors.h
    scan_data.h
    sensor.h
    sensor_info.h
    utils.h
	GridMap.h
	DataPointContainer.h
	GridMapBase.h
	GridMapCacheArray.h
	GridMapLogOdds.h
	GridMapReflectanceCount.h
	GridMapSimpleCount.h
	HectorMapMutex.h
	HectorMappingRos.h
	HectorSlamProcessor.h
	MapDimensionProperties.h
	MapLockerInterface.h
	MapProContainer.h
	MapRepMultiMap.h
	MapRepresentationInterface.h
	MapReqSingleMap.h
	OccGridMapBase.h
	OccGridMapUtil.h
	OccGridMapUtilConfig.h
	ScanMatcher.h
	UtilFunctions.h
    )
install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

