/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

        //return pointer of the canvas
    MosaicCanvas* return_ptr  = new MosaicCanvas(theSource.getRows(),theSource.getColumns());

    //1st:vector for tree building
        //the Kd-tree contains points of average color of each tile in the tiles vector
        //therefore we coudl find the nearest color by searching the 3d kd-tree
    vector<Point<3>> tiles_to_point;
        //convert average color to point and pushback to the vector
        //construct the tree using the vector of points
                    // for(unsigned i=0;i<= theTiles.size()-1;i++)
                    // {
                    //     Point<3> point_convert= convertToLAB(theTiles[i].getAverageColor());
                    //     tiles_to_point.push_back(point_convert);
                    // }
    KDTree<3> tree_search(tiles_to_point);
    //2nd:construct a map
    map<Point<3> , int > tile_avg_map;

    for(unsigned i=0;i<= theTiles.size()-1;i++)
    {
        Point<3> point_convert= convertToLAB(theTiles[i].getAverageColor());
        tiles_to_point.push_back(point_convert);
        tile_avg_map[point_convert] = i;
        // tile_avg_map.insert(make_pair(point_convert,i));
    }

    //3rd:produce new picture

    for(int i=0;i<=theSource.getRows()-1;i++)
    {
        for(int j=0; j<=theSource.getColumns()-1;j++)
        {
            // return_ptr->setTile( i,j,get_match_at_idx(tree_search,tile_avg_map,theTiles,theSource, i,j));
    HSLAPixel avg = theSource.getRegionColor(i,j);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree_search.findNearestNeighbor(avgPoint);

    // map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    // if (it == tile_avg_map.end())
    //     cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;


    int index = tile_avg_map[nearestPoint];
    return_ptr->setTile(i,j,&theTiles[index]);
        }
    }

    return return_ptr;
    // return NULL;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
