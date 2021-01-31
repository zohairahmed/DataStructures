/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

// Create map for TileImages and their average color, then use KDTree to
// find the nearest neighbors and add the tileImage to the MosaicCanvas
MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    MosaicCanvas * mc = new MosaicCanvas(theSource.getRows(),
                                         theSource.getColumns());

    // KDTree<3> tileMap(theTiles); need a vector of the average colors
    std::map<Point<3>, TileImage *> tiles;
    vector<Point<3>> tileAvgColors;
    for (size_t i = 0; i < theTiles.size(); i++){
      tiles[convertToXYZ(theTiles[i].getAverageColor())] = &theTiles[i];
      tileAvgColors.push_back(convertToXYZ(theTiles[i].getAverageColor()));
    }

    KDTree<3> tileColors(tileAvgColors);

    for (int i = 0; i < mc->getRows(); i++){
      for (int j = 0; j < mc->getColumns(); j++){
        mc->setTile(i, j, tiles[tileColors.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i, j)))]);
      }
    }

    return mc;
}
