//
//  cuboid.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 2/18/24.
//

#include "cuboid.hpp"
namespace kege
{
    Cuboid::Cuboid( const kege::vec3& center, const kege::vec3& lengths )
    {
        const uint64_t vertex_count = 24;

        kege::vec3 p[ 8 ];
        p[0] = center + kege::vec3(  lengths.x,  lengths.y,  lengths.z );
        p[1] = center + kege::vec3( -lengths.x,  lengths.y,  lengths.z );
        p[2] = center + kege::vec3( -lengths.x, -lengths.y,  lengths.z );
        p[3] = center + kege::vec3(  lengths.x, -lengths.y,  lengths.z );

        p[4] = center + kege::vec3(  lengths.x,  lengths.y, -lengths.z );
        p[5] = center + kege::vec3( -lengths.x,  lengths.y, -lengths.z );
        p[6] = center + kege::vec3( -lengths.x, -lengths.y, -lengths.z );
        p[7] = center + kege::vec3(  lengths.x, -lengths.y, -lengths.z );

        kege::vec3 n[ 6 ] = 
        {
            kege::vec3( 0.f, 0.f, 1.f),
            kege::vec3( 0.f, 0.f,-1.f),
            kege::vec3(-1.f, 0.f, 0.f),
            kege::vec3( 1.f, 0.f, 0.f),
            kege::vec3( 0.f, 1.f, 0.f),
            kege::vec3( 0.f,-1.f, 0.f)
        };

        kege::vec2 t[ 4 ] = {
            vec2(1.0f, 1.0f),
            vec2(0.0f, 1.0f),
            vec2(0.0f, 0.0f),
            vec2(0.0f, 1.0f)
        };

        uint32_t faces[6][4] =
        {
            { 0 , 1 , 2 , 3 }, // front plane
            { 4 , 5 , 6 , 7 }, // back plane
            { 1 , 5 , 6 , 2 }, // left plane
            { 4 , 0 , 3 , 7 }, // right plane
            { 4 , 5 , 1 , 0 }, // top plane
            { 3 , 2 , 6 , 7 }  // bottom plane
        };

        kege::VertexPNT vertices[ vertex_count ];
        for (int i=0,j,k; i<6; i++)
        {
            for (j=0; j<4; j++)
            {
                k = i * 4 + j;
                vertices[k].position = p[ faces[i][j] ];
                vertices[k].normal   = n[ i ];
                vertices[k].texcoord = t[ j ];
            }
        }
        uint32_t indices[] =
        {
            // front plane
            0 , 1 , 2 , 2 , 3 , 0 ,
            // back plane
            4 , 5 , 6 , 6 , 7 , 4 ,
            // left plane
            8 , 9 , 10, 10, 11, 8 ,
            // right plane
            12, 13, 14, 14, 15, 12,
            // left plane
            16, 17, 18, 18, 19, 16,
            // right plane
            20, 21, 22, 22, 23, 20
        };

        IndexedMesh::CreateInfo info;
        info.vertex_buffer_create_infos = { sizeof(vertices), vertices, kege::STATIC_BUFFER };
        info.index_buffer_create_info = { sizeof(indices), indices, kege::STATIC_BUFFER, kege::INDEX_TYPE_U32 };
        info.draw_command =
        {
            36, // index_count,
            1,  // instance_count,
            0,  // first_index,
            0,  //  vertex_offset,
            0,  // first_instance,
        };

        IndexedMesh::operator()( info );
    }
}
