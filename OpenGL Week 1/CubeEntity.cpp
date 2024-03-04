#include "CubeEntity.h"
#include "GraphicsEngine.h"
#include "Vec2.h"
#include "Game.h"

struct Vertex
{
    Vec3 position;
    Vec2 texCoords;
};

//during the oncreate method of this entity, we initialize the graphics data of the cube
void CubeEntity::onCreate()
{
    Vec3 position_list[] =
    {
        //front face
        { Vec3(-0.5f,-0.5f,-0.5f)},
        { Vec3(-0.5f,0.5f,-0.5f) },
        { Vec3(0.5f,0.5f,-0.5f) },
        { Vec3(0.5f,-0.5f,-0.5f)},

        //back face
        { Vec3(0.5f,-0.5f,0.5f) },
        { Vec3(0.5f,0.5f,0.5f) },
        { Vec3(-0.5f,0.5f,0.5f)},
        { Vec3(-0.5f,-0.5f,0.5f) }
    };

    Vec2 texcoord_list[] =
    {
        { Vec2(0.0f,0.0f) },
        { Vec2(0.0f,1.0f) },
        { Vec2(1.0f,0.0f) },
        { Vec2(1.0f,1.0f) }
    };

    Vertex verticesList[] =
    {
        //front face
        { position_list[0],texcoord_list[1] },
        { position_list[1],texcoord_list[0] },
        { position_list[2],texcoord_list[2] },
        { position_list[3],texcoord_list[3] },

        //back face
        { position_list[4],texcoord_list[1] },
        { position_list[5],texcoord_list[0] },
        { position_list[6],texcoord_list[2] },
        { position_list[7],texcoord_list[3] },

        //top face
        { position_list[1],texcoord_list[1] },
        { position_list[6],texcoord_list[0] },
        { position_list[5],texcoord_list[2] },
        { position_list[2],texcoord_list[3] },

        //bottom face
        { position_list[7],texcoord_list[1] },
        { position_list[0],texcoord_list[0] },
        { position_list[3],texcoord_list[2] },
        { position_list[4],texcoord_list[3] },

        //right face
        { position_list[3],texcoord_list[1] },
        { position_list[2],texcoord_list[0] },
        { position_list[5],texcoord_list[2] },
        { position_list[4],texcoord_list[3] },

        //left face
        { position_list[7],texcoord_list[1] },
        { position_list[6],texcoord_list[0] },
        { position_list[1],texcoord_list[2] },
        { position_list[0],texcoord_list[3] }
    };

    uint indicesList[] =
    {
        //front face
        0,1,2,  //first triangle
        2,3,0,  //second triangle
        //back face
        4,5,6,
        6,7,4,
        //top face
        8,9,10,
        10,11,8,
        //bottom face
        12,13,14,
        14,15,12,
        //right face
        16,17,18,
        18,19,16,
        //left face
        20,21,22,
        22,23,20
    };



    static const VertexAttribute attribsList[] = {
        { 3 }, //numElements position attribute
        { 2 } //numElements texture coordinates attribute
    };
    
    m_mesh = getGame()->getGraphicsEngine()->createVertexArrayObject(
        //vertex buffer
        {
                (void*)verticesList,
                sizeof(Vertex), //size in bytes of a single composed vertex (in this case composed by vertex (3 nums* sizeof float) + texcoord (2 nums* sizeof float))
                sizeof(verticesList) / sizeof(Vertex),  //number of composed vertices,

                (VertexAttribute*)attribsList,
                2 //numelements attrib list
        },
        //index buffer
        {
            (void*)indicesList,
            sizeof(indicesList)
        }
        );
}

void CubeEntity::onGraphicsUpdate(float deltaTime)
{
    //during the graphcis update, we call the draw function
    getGame()->getGraphicsEngine()->setVertexArrayObject(m_mesh); //bind vertex buffer to graphics pipeline
    getGame()->getGraphicsEngine()->drawIndexedTriangles(TriangleType::TriangleList, 36);//draw triangles through the usage of index buffer
}
