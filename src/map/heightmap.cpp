#include "map/heightmap.h"

#include <cstdlib>

#include "map/map.h"
#include "map/point.h"
#include "tool/simplexnoise.h"


namespace map
{


HeightMap::HeightMap(unsigned int width, unsigned int height) :
  m_width(width),
  m_height(height),
  m_points(m_width * m_height),
  m_vertices(m_height * m_width * 3),
  m_indices(m_height * m_width * 3 / 2),
  m_normals(m_height * m_width * 3 / 2),
  m_uvs()
{
    /*
    m_points.reserve(m_width * m_height);
    m_vertices.reserve(m_height * m_width * 3);
    m_indices.reserve(m_height * m_width * 3 / 2);
    m_normals.reserve(m_height * m_width * 3 / 2);
    */
}

HeightMap::~HeightMap()
{
}

// vérifie qu'un point s appartient au triangle a,b,c
bool HeightMap::pointInsideTrigon(glm::vec3 s, glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
    float as_x = s.x-a.x;
    float as_z = s.z-a.z;

    bool s_ab = (b.x-a.x)*as_z-(b.z-a.z)*as_x >= 0;

    if(((c.x-a.x)*as_z-(c.z-a.z)*as_x > 0) == s_ab) return false;

    if(((c.x-b.x)*(s.z-b.z)-(c.z-b.z)*(s.x-b.x) > 0) != s_ab) return false;

    return true;
}

/*
// génère la mesh du terrain en procédant deux triangles par deux triangles (ou carré par carré)
void    HeightMap::generateMesh()
{
    m_vertices.reserve(m_height * m_width * 3);
    m_indices.reserve(m_height * m_width * 3 * 2);
    m_normals.reserve(m_height * m_width * 3 * 2);
    m_uvs.reserve(m_height * m_width * 2);

    for (unsigned int i = 0; i < m_height - 1; i++)
        for (unsigned int j = 0; j < m_width - 1; j++)
        {
	    float scaleZ = 1000000;
            glm::vec3 p1 = glm::vec3(static_cast<float>(m_points[i * m_width + j].x),
                                     static_cast<float>(m_points[i * m_width + j].y),
                                     static_cast<float>(m_points[i * m_width + j].z) * scaleZ);
	    glm::vec3 p2 = glm::vec3(static_cast<float>(m_points[i * m_width + j + 1].x),
                                     static_cast<float>(m_points[i * m_width + j + 1].y),
                                     static_cast<float>(m_points[i * m_width + j + 1].z) * scaleZ);
	    glm::vec3 p3 = glm::vec3(static_cast<float>(m_points[(i + 1) * m_width + j].x),
                                     static_cast<float>(m_points[(i + 1) * m_width + j].y),
                                     static_cast<float>(m_points[(i + 1) * m_width + j].z) * scaleZ);
	    glm::vec3 p4 = glm::vec3(static_cast<float>(m_points[(i + 1) * m_width + j + 1].x),
                                     static_cast<float>(m_points[(i + 1) * m_width + j + 1].y),
                                     static_cast<float>(m_points[(i + 1) * m_width + j + 1].z) * scaleZ);

            m_vertices.push_back(p1.x);
            m_vertices.push_back(p1.y);
            m_vertices.push_back(p1.z);

        m_uvs.push_back(static_cast<float>(j)/static_cast<float>(m_width));
        m_uvs.push_back(static_cast<float>(i)/static_cast<float>(m_height));

	    if (j == m_width - 2)
	    {
		m_vertices.push_back(p2.x);
            	m_vertices.push_back(p2.y);
            	m_vertices.push_back(p2.z);
        m_uvs.push_back(static_cast<float>(j + 1)/static_cast<float>(m_width));
            m_uvs.push_back(static_cast<float>(i)/static_cast<float>(m_height));
	    }
	    if (i == m_height - 2)
	    {
		m_vertices.push_back(p3.x);
		m_vertices.push_back(p3.y);
		m_vertices.push_back(p3.z);
        m_uvs.push_back(static_cast<float>(j)/static_cast<float>(m_width));
            m_uvs.push_back(static_cast<float>(i + 1)/static_cast<float>(m_height));
		if (j == m_width - 2)
	    	{
	    	    m_vertices.push_back(p4.x);
                    m_vertices.push_back(p4.y);
                    m_vertices.push_back(p4.z);
                m_uvs.push_back(static_cast<float>(j + 1)/static_cast<float>(m_width));
                m_uvs.push_back(static_cast<float>(i + 1)/static_cast<float>(m_height));
	    	}
	    }


            m_indices.push_back(j + i * m_width); //p1
            m_indices.push_back(j + 1 + i * m_width); //p2
            m_indices.push_back(j + (i + 1) * m_width); //p3

            m_indices.push_back(j + (i + 1) * m_width); //p3
            m_indices.push_back(j + 1 + (i + 1) * m_width); //p4
            m_indices.push_back(j + 1 + i * m_width); //p2

	    glm::vec3 result = glm::cross(p2 - p1, p3 - p1);

            m_normals.push_back(result.x);
            m_normals.push_back(result.y);
            m_normals.push_back(result.z);

            result = glm::cross(p4 - p3, p2 - p3);

            m_normals.push_back(result.x);
            m_normals.push_back(result.y);
            m_normals.push_back(result.z);
       }
}
*/
}
