/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    //bfs traversal to find the minimum edge weight
        //set all vertex labels to "UNEXPLORED"
    for(Vertex v: graph.getVertices())
    {
        graph.setVertexLabel(v, "UNEXPLORED");
    }
        //set all edge labels to "UNEXPLORED"
    for(Edge e: graph.getEdges())
    {
        graph.setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }
        //initialization for queue and starting vertex
    Vertex start_traversal = graph.getStartingVertex();
    queue<Vertex> q_;
    graph.setVertexLabel(start_traversal, "VISITED");
    q_.push(start_traversal);
        //need to be updated during traversal, now set to a large number
    int min_weight = 100000000;
    Edge min_edge;
    //starting traversal
    while(!q_.empty())
    {
        Vertex v = q_.front();
        q_.pop();
        //check every adjacent vertex
        for(Vertex w: graph.getAdjacent(v))
        {
            //set the vertex label to "VISITED" if unexplored
            //set the edge label to "DISCOVERY" if unexplored
            if(graph.getVertexLabel(w) == "UNEXPLORED")
            {
                graph.setEdgeLabel(v, w, "DISCOVERY");
                graph.setVertexLabel(w, "VISITED");
                q_.push(w);
                if(graph.getEdgeWeight(v, w) < min_weight)
                {
                    min_weight = graph.getEdgeWeight(v, w);
                    min_edge = graph.getEdge(v, w);
                }
            }
            //if the neighbor is already visited, set the edge label to "CROSS"
            else if(graph.getEdgeLabel(v, w) == "UNEXPLORED")
            {
                graph.setEdgeLabel(v, w, "CROSS");
                if(graph.getEdgeWeight(v, w) < min_weight)
                {
                   min_edge = graph.getEdge(v, w);
                    min_weight = graph.getEdgeWeight(v, w);
                }
            }
        }

    }
    //label
    graph.setEdgeLabel(min_edge.source, min_edge.dest, "MIN");
    return min_weight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    //copy previous bfs code
    //use unordered_map to store parent
    unordered_map<Vertex, Vertex> p_;
    //bfs traversal to find the minimum edge weight
        //set all vertex labels to "UNEXPLORED"
    for(Vertex v: graph.getVertices())
    {
        graph.setVertexLabel(v, "UNEXPLORED");
    }
        //set all edge labels to "UNEXPLORED"
    for(Edge e: graph.getEdges())
    {
        graph.setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }
        //initialization for queue and starting vertex
    Vertex start_traversal = start;
    queue<Vertex> q_;
    graph.setVertexLabel(start_traversal, "VISITED");
    q_.push(start_traversal);
        //need to be updated during traversal, now set to a large number

    //starting traversal
    while(!q_.empty())
    {
        Vertex v = q_.front();
        q_.pop();
        //check every adjacent vertex
        for(Vertex w: graph.getAdjacent(v))
        {
            //set the vertex label to "VISITED" if unexplored
            //set the edge label to "DISCOVERY" if unexplored
            if(graph.getVertexLabel(w) == "UNEXPLORED")
            {
                graph.setEdgeLabel(v, w, "DISCOVERY");
                graph.setVertexLabel(w, "VISITED");
                q_.push(w);
                //store parent
                p_.insert({w, v});
            }
            //if the neighbor is already visited, set the edge label to "CROSS"
            else if(graph.getEdgeLabel(v, w) == "UNEXPLORED")
            {
                graph.setEdgeLabel(v, w, "CROSS");
            }
        }
    }
    //find end point in pair
    int count_ =0;
    Vertex find_ = end;
    while (find_!=start)
    {
        Vertex parent = p_.find(find_)->second;
        graph.setEdgeLabel(parent, find_, "MINPATH");
        find_ = parent;
        count_++;
    }
    //over, reach start
    return count_;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    //set every vetex as a set
    int vertex_size = graph.getVertices().size();
    DisjointSets forests;
    for (int i=0;i<vertex_size;i++)
    {
        forests.addelements(1);
    }
    //use vector as PQ
    vector<Edge> edges_ = graph.getEdges();
    sort(edges_.begin(), edges_.end());
    //terminate when one set only
    while(forests.size(0) != vertex_size)
    {
        //pop the smallest edge
        Edge remomve_= edges_.front();
        edges_.erase(edges_.begin());
        //not in same set
        if(forests.find(remomve_.source) != forests.find(remomve_.dest))
        {
            //union
            forests.setunion(remomve_.source, remomve_.dest);
            //label it
            graph.setEdgeLabel(remomve_.source, remomve_.dest, "MST");
        }
    }

}

