#ifndef _GRIDMAP_H_
#define _GRIDMAP_H_

#include <hokuyoaist/OccGridMapBase.h>
#include <hokuyoaist/GridMapLogOdds.h>
#include <hokuyoaist/GridMapReflectanceCount.h>
#include <hokuyoaist/GridMapSimpleCount.h>

namespace hectorslam {

typedef OccGridMapBase<LogOddsCell, GridMapLogOddsFunctions> GridMap;
}

#endif
