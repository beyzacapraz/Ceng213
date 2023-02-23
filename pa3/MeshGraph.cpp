#include "MeshGraph.h"
#include "BinaryHeap.h"

// For printing
#include <fstream>
#include <iostream>
#include <sstream>

MeshGraph::MeshGraph(const std::vector<Double3>& vertexPositions,
                     const std::vector<IdPair>& edges)
{
    int v_size = vertexPositions.size();
    for(int i = 0; i < v_size ;i++){
        struct Vertex new_vertex;
        new_vertex.id = i;
        new_vertex.position3D = vertexPositions[i];
        vertices.push_back(new_vertex);
    }
    for(int j = 0; j < v_size; j++){
        std::list<Vertex*> edge_list;
        for(int k = 0; k < edges.size(); k++){
            if(vertices[j].id == edges[k].vertexId0){
                int index = edges[k].vertexId1;
                edge_list.push_back(&vertices[index]);
            }
            if(vertices[j].id == edges[k].vertexId1){
                int index = edges[k].vertexId0;
                edge_list.push_back(&vertices[index]);
            }
        }
        adjList.push_back(edge_list);
    }
}

double MeshGraph::AverageDistanceBetweenVertices() const // boþ olma durumu?
{
    double D_e,sum = 0;int edge_size;
    for(int i = 0; i < vertices.size(); i++){
        std::list<Vertex*>::const_iterator it = adjList[i].begin();
        for(int j = 0; j < adjList[i].size(); j++){
            sum += Double3::Distance(vertices[i].position3D,(*it) -> position3D);
            it++;
        }
    }
    edge_size = TotalEdgeCount();
    D_e = (sum / 2) / edge_size;
    return D_e;
    
}

double MeshGraph::AverageEdgePerVertex() const
{
    return (double)TotalEdgeCount()/TotalVertexCount();
}

int MeshGraph::TotalVertexCount() const
{
    return vertices.size();
}

int MeshGraph::TotalEdgeCount() const
{
    int edge_count = 0;
    for(int i = 0; i < vertices.size(); i++){
        edge_count += adjList[i].size();
    }
    return edge_count / 2;
}
int MeshGraph::index_vertex(int vertexId) const
{
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].id == vertexId) return i;
    }
    return -1;
}
int MeshGraph::VertexEdgeCount(int vertexId) const
{
    int Id = vertexId;
    int b = index_vertex(Id);
    if( b != -1) return adjList[b].size();
    else return b;
}

void MeshGraph::ImmediateNeighbours(std::vector<int>& outVertexIds,
                                    int vertexId) const
{
    int b = index_vertex(vertexId);
    if(b != -1){
        std::list<Vertex*>::const_iterator it = adjList[b].begin();
        for(int i = 0; i < adjList[b].size();i++){
            outVertexIds.push_back((*it) -> id);
            it++;
        }
    }
    
}

void MeshGraph::PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                     int vertexIdFrom, int vertexIdTo,
                                     const Color& color) const
{
    BinaryHeap priority_heap;
    std::vector<double> distance(vertices.size(),INFINITY);
    std::vector<int> previous(vertices.size(),-1);
    int  outUniqueId; double outWeight;
    int b = index_vertex(vertexIdFrom); int c = index_vertex(vertexIdFrom);
    if(b != -1 && c != -1){
        outputColorAllVertex.resize(vertices.size());
        for(int i = 0; i < vertices.size();i++){
            outputColorAllVertex[i].r = 0;
            outputColorAllVertex[i].g = 0;
            outputColorAllVertex[i].b = 0;
        }
        for(int j = 0; j < vertices.size(); j++){
            if(j == vertexIdFrom){
                priority_heap.Add(j,0);
                distance[j] = 0;
            }
            else{
                priority_heap.Add(j,INFINITY);
            }
        }
        while(priority_heap.HeapSize()){
            priority_heap.PopHeap(outUniqueId,outWeight);
            std::list<Vertex*>::const_iterator it = adjList[outUniqueId].begin();
            for(int k = 0; k < adjList[outUniqueId].size();k++){
                double new_distance,weight;
                weight = Double3::Distance(vertices[outUniqueId].position3D,(*it) -> position3D);
                new_distance = distance[outUniqueId] + weight;
                if(new_distance < distance[(*it) -> id]){
                    distance[(*it) -> id] = new_distance;
                    previous[(*it) -> id] = outUniqueId;
                    priority_heap.ChangePriority((*it) -> id,new_distance);
                }
                it++;
            }
        }
        
        while(1){
            outputColorAllVertex[vertexIdTo] = color;
            if(previous[vertexIdTo] == -1) break;
            vertexIdTo = previous[vertexIdTo];
            
        }
     
    }
     
   
}
void MeshGraph::SortImmediateNeighbours(std::vector<int>& outVertexIds,
                                    int vertexId) const
{
    int b = index_vertex(vertexId);
    if(b != -1){
        std::list<Vertex*>::const_iterator it = adjList[b].begin();
        std::list<int> mylist;
        for(int j=0;j<adjList[b].size();it++,j++){
            mylist.push_back((*it)->id);
        }
        mylist.std::list<int>::sort();
        std::list<int>::const_iterator ite = mylist.begin();
        for(int i = 0; i < adjList[b].size();i++){
            outVertexIds.push_back(*ite);
            ite++;
        }
    }
    
}
double MeshGraph::filter_function(FilterType type,double alpha,double distance) const{
    if(type ==  FILTER_GAUSSIAN){
        double value;
        value = -pow(distance,2)/pow(alpha,2);
        return exp(value);
        
    }
    else{
        if(-alpha <= distance && distance <= alpha  ) return 1;
        else return 0;
    }
}

void MeshGraph::PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                    int vertexId, const Color& color,
                                    int maxDepth, FilterType type,
                                    double alpha) const
{
    BinaryHeap priority_heap;
    std::vector<double> distance(vertices.size(),INFINITY);
    std::vector<int> depth(vertices.size(),-1);
    std::vector<bool> visited(vertices.size(),false);
    int  outUniqueId; double outWeight,count=1;
    int b = index_vertex(vertexId);
    if(maxDepth >=0 && b != -1 ){
        outputColorAllVertex.resize(vertices.size());
        for(int i = 0; i < vertices.size();i++){
            outputColorAllVertex[i].r = 0;
            outputColorAllVertex[i].g = 0;
            outputColorAllVertex[i].b = 0;
        }
        priority_heap.Add(vertexId,0);
        distance[vertexId] = 0;
        visited[vertexId] = true;
        depth[vertexId] = 0;
        for(int j = 0; j < maxDepth;){//??
            std::vector<int> neighbours;
            priority_heap.PopHeap(outUniqueId,outWeight);
            SortImmediateNeighbours(neighbours, outUniqueId);
            if(depth[outUniqueId] < maxDepth){
                for(int k = 0; k < neighbours.size(); k++){
                    double new_distance,weight;
                    if(visited[neighbours[k]]);
                    else{
                        weight = Double3::Distance(vertices[outUniqueId].position3D,vertices[neighbours[k]].position3D);
                        new_distance = distance[outUniqueId] + weight;
                        visited[neighbours[k]] = true;
                        depth[neighbours[k]] = depth[outUniqueId]+1;//?
                        distance[neighbours[k]] = new_distance;
                        priority_heap.Add(neighbours[k],count++);
                    }

                }
            }
            else j++;
        }
        for(int l = 0; l < vertices.size();l++){
            if(visited[l]){
                Double3 c;
                c.x = color.r;c.y = color.g; c.z = color.b;
                c.x *= filter_function(type,alpha,distance[l]); c.x = floor(c.x);
                c.y *= filter_function(type,alpha,distance[l]); c.y = floor(c.y);
                c.z *= filter_function(type,alpha,distance[l]); c.z = floor(c.z);
                outputColorAllVertex[l].r = c.x; outputColorAllVertex[l].g = c.y; outputColorAllVertex[l].b = c.z;
            }
        }
            
    }

}

void MeshGraph::PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                      int vertexId, const Color& color,
                                      int maxDepth, FilterType type,
                                      double alpha) const
{
    BinaryHeap priority_heap;
    std::vector<double> distance(vertices.size(),INFINITY);
    std::vector<int> depth(vertices.size(),-1);
    std::vector<bool> visited(vertices.size(),false);
    int  outUniqueId; double outWeight,count=1;
    int b = index_vertex(vertexId);
    if(maxDepth >=0 && b != -1 ){
        outputColorAllVertex.resize(vertices.size());
        for(int i = 0; i < vertices.size();i++){
            outputColorAllVertex[i].r = 0;
            outputColorAllVertex[i].g = 0;
            outputColorAllVertex[i].b = 0;
        }
        priority_heap.Add(vertexId,0);
        distance[vertexId] = 0;
        visited[vertexId] = true;
        depth[vertexId] = 0;
        for(int j = 0; j < maxDepth;){//??
            std::vector<int> neighbours;
            priority_heap.PopHeap(outUniqueId,outWeight);
            SortImmediateNeighbours(neighbours, outUniqueId);
            if(depth[outUniqueId] < maxDepth){
                for(int k = 0; k < neighbours.size(); k++){
                    double new_distance,weight;
                    if(visited[neighbours[k]]);
                    else{
                        new_distance = Double3::Distance(vertices[vertexId].position3D,vertices[neighbours[k]].position3D);
                        visited[neighbours[k]] = true;
                        depth[neighbours[k]] = depth[outUniqueId]+1;//?
                        distance[neighbours[k]] = new_distance;
                        priority_heap.Add(neighbours[k],count++);
                    }

                }
            }
            else j++;
        }
        for(int l = 0; l < vertices.size();l++){
            if(visited[l]){
                Double3 c;
                c.x = color.r;c.y = color.g; c.z = color.b;
                c.x *= filter_function(type,alpha,distance[l]); c.x = floor(c.x);
                c.y *= filter_function(type,alpha,distance[l]); c.y = floor(c.y);
                c.z *= filter_function(type,alpha,distance[l]); c.z = floor(c.z);
                outputColorAllVertex[l].r = c.x; outputColorAllVertex[l].g = c.y; outputColorAllVertex[l].b = c.z;
            }
        }
            
    }
}

void MeshGraph::WriteColorToFile(const std::vector<Color>& colors,
                                 const std::string& fileName)
{
    // IMPLEMENTED
    std::stringstream s;
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        int r = static_cast<int>(colors[i].r);
        int g = static_cast<int>(colors[i].g);
        int b = static_cast<int>(colors[i].b);

        s << r << ", " << g << ", " << b << "\n";
    }
    std::ofstream f(fileName.c_str());
    f << s.str();
}

void MeshGraph::PrintColorToStdOut(const std::vector<Color>& colors)
{
    // IMPLEMENTED
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        std::cout << static_cast<int>(colors[i].r) << ", "
                  << static_cast<int>(colors[i].g) << ", "
                  << static_cast<int>(colors[i].b) << "\n";
    }
}
