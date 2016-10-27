#ifndef HEIGHTMAP_NAMESPACE_H
#define HEIGHTMAP_NAMESPACE_H

#include <vector>
#include <glm/glm.hpp>
#include "heightpoint.h"

namespace map
{

///
/// \brief This class stores the height of the (x, y) points of a 2D map
/// and also generates the buffers describing the map's mesh
///
class HeightMap
{
public:
    ///
    /// \brief Default constructor.
    /// \param Width of the heightmap.
    /// \param Height of the heightmap.
    ///
    HeightMap(unsigned int width, unsigned int height);

    ///
    /// \brief Default destructor.
    ///
    ~HeightMap();

    ///
    /// \brief Veryfies that a point s is inside the abc triangle.
    /// \param Point to be checked.
    /// \param Vertice a.
    /// \param Vertice b.
    /// \param Vertice c.
    ///
    static bool pointInsideTrigon(glm::vec3 s, glm::vec3 a, glm::vec3 b, glm::vec3 c);

    ///
    /// \brief Generates the mesh associated to the heightmap.
    ///
    void    generateMesh();

    inline HeightPoint  &pointAt(unsigned int x, unsigned int y)
    { return m_points[x * m_width + y]; }

    ///
    /// \brief points buffer getter
    ///
    inline const std::vector<HeightPoint>   &points()
    { return m_points; }

    ///
    /// \brief Vertice buffer getter.
    ///
    inline const std::vector<float>         &vertices()
    { return m_vertices; }

    ///
    /// \brief Indices buffer getter.
    ///
    inline const std::vector<unsigned int>  &indices()
    { return m_indices; }

    ///
    /// \brief Normals buffer getter.
    ///
    std::vector<float> const &normals()
    { return m_normals; }

    ///
    /// \brief UV buffer getter.
    ///
    std::vector<float> const &UVs()
    { return m_uvs; }

private:

    ///
    /// \brief Width of the heightmap.
    ///
    unsigned int m_width;

    ///
    /// \brief Height of the heightmap.
    ///
    unsigned int m_height;

    ///
    /// \brief Every point of the heightmap.
    ///
    std::vector<HeightPoint>    m_points;

    ///
    /// \brief Heightmap's vertices buffer.
    ///
    std::vector<float> m_vertices;

    ///
    /// \brief Heightmap's indices buffer.
    ///
    std::vector<unsigned int>   m_indices;

    ///
    /// \brief Heightmap's normals buffer.
    ///
    std::vector<float> m_normals;

    ///
    /// \brief Heightmap's normals buffer.
    ///
    std::vector<float> m_uvs;

};

}

#endif // HEIGHTMAP_NAMESPACE_H
