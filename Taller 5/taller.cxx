#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "grafo.h"

int filas, cols;

// -------------------------------------------------------------------------

// -------------------------------------------------------------------------

// TODO 1: typedef Graph< Point, float > TGraph

// -------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr
            << "Usage: " << argv[0] << " input_mesh start end"
            << std::endl;
        return (1);

    } // fi
    long start_id = std::atoi(argv[2]);
    long end_id = std::atoi(argv[3]);

    // TODO 2: TGraph g;
    Grafo grafo;
    // Load file in a buffer
    std::ifstream in_mesh_stream(argv[1], std::ifstream::binary);
    if (!in_mesh_stream)
    {
        std::cerr << "Error reading \"" << argv[1] << "\"" << std::endl;
        return (1);

    } // fi
    in_mesh_stream.seekg(0, in_mesh_stream.end);
    unsigned long in_mesh_file_length = in_mesh_stream.tellg();
    in_mesh_stream.seekg(0, in_mesh_stream.beg);
    char *in_mesh_file_buffer = new char[in_mesh_file_length];
    in_mesh_stream.read(in_mesh_file_buffer, in_mesh_file_length);
    in_mesh_stream.close();
    std::istringstream in_mesh(in_mesh_file_buffer);

    // Read vertices
    long nPoints;

    in_mesh >> nPoints;
    for (long pId = 0; pId < nPoints; pId++)
    {
        Point pnt;
        in_mesh >> pnt.X >> pnt.Y >> pnt.Z;

        // TODO 3: g.AddVertex( pnt );
        grafo.insertarVertice(pnt);
    } // rof
    std::cout << "termino la insercion de los datos de los vertices" << std::endl;
    grafo.generarArregloVertices();
    std::cout << "termino la verificacion de vertices y asignacion de la matriz" << std::endl;

    grafo.iniciarMatrix(grafo.obtenerTamanoArregloVectores());
    std::cout << "termino la verificacion de vertices y asignacion de la matriz" << std::endl;
    // Read edges
    long nEdges;
    float costo = 0;
    in_mesh >> nEdges;
    for (long eId = 0; eId < nEdges; eId++)
    {
        long start, end;
        in_mesh >> start >> end;

        /*
        TODO 4:
        cost = g.GetVertex( start ).distanceTo( g.GetVertex( end ) );
        g.AddEdge( start, end, cost );
        g.AddEdge( end, start, cost );
        */

        Point startP, endP;
        startP = grafo.buscarVerticePorPosicion((int)start);
        endP = grafo.buscarVerticePorPosicion((int)end);
        costo = startP.distanceTo(endP);
        grafo.insetarArista(startP, endP, costo);

    } // rof
    delete[] in_mesh_file_buffer;

    if (start_id < 0 || start_id >= grafo.obtenerTamanoArregloVectores() || end_id < 0 || end_id >= grafo.obtenerTamanoArregloVectores())
    {
        std::cerr << "Invalid path endpoints." << std::endl;
        return (1);

    } // fi

    /*
    TODO 5:
    std::vector< long > path = g.Dijkstra( start_id, end_id );
    std::cout << path.size( ) << std::endl;
    for( unsigned int i = 0; i < path.size( ); ++i )
    std::cout
    << vertices[ path[ i ] ].X << " "
    << vertices[ path[ i ] ].Y << " "
    << vertices[ path[ i ] ].Z << std::endl;
  */
    std::vector<Point> dk = grafo.dijkstra((float)start_id, (float)end_id);
    //std::vector<std::vector<float>> f = grafo.obtenerMatrix();
    
    //grafo.imprimirVertices();
    //std::cout << "---------------------------------------" << std::endl;
    for (int i = 0; i < dk.size(); i++)
    {
        std::cout
            << dk[i].X << " "
            << dk[i].Y << " "
            << dk[i].Z << " | "<< grafo.buscarVerticePosicion(dk[i]) << std::endl;

    }
    return (0);
}
