#  <#Title#>

 
 Take the following entity.

 entity->add< Skeleton >()
 entity->add< SkinMesh >()
 entity->add< BasicMaterial >()
 
 their is only one basic material object. The basic material object may or may not have any members or functions. 
 The purpose of the object is to differentiate which render-technique to use to render the mesh. Thus a system
 that must be created to handle an entity with a skin-mesh, skeleton, and a basic-material. BasicMaterial is 
 the shader parameter/effect to load into the shader-program. The shader program is contained with in the system
 that renders this entity.
 
 Now take the following entity. This time with a different component-signature.

 entity->add< Mesh >()
 entity->add< BasicMaterial >()
 
 Now once again we want to render the following entity above. This time with the same BasicMaterial object but
 a different mesh. This time it is just a standard mesh. Once again a system must be created to handle an entity 
 with a standard mesh, and a basic material.
 
 What this tells us then is that we need two rendering-system, both with their own shader-programs. One with 
 skeleton mesh support and another with out. These basic-material-rendering-system may or may not have lighting 
 support. that is totally up to the programmer. But if lighting is supported then the rendering-system will
 need to get the lights to render with the mesh.
 
 BasicMaterial shouldn't be the only supported material. If the type of system we are going for is like the one 
 described above, then one entity can have multiple material. For instance take the following entity.

 entity->add< Mesh >()
 entity->add< PBRMaterial >()
 entity->add< OutlineMaterial >()
 
 Keep in mind that the Material here may or may not contain member data, and the material is use to determine 
 how the object should be render. namely which rendering-system/render-technique should be use to render the 
 entity.

 Now whats the definitions of the components? These components are structs, which just holds data. Very simple. 
 The render-techniques are the systems that knows how to deal with these structs. a Mesh is just a struct with a 
 vertex-buffer, an optional instance-buffer and a draw-command. Additional certain entities can also have 
 draw-command-buffers attached to them, which another system will need to handle the rendering technque for
 such an entity. This is just an idea, because their will come a time when you need to use draw-command-buffers.

 Things to consider. Entity signature is represended using a bitmask. Using a bitmask of 256 bits means that you can 
 only support 256 distinct components. This can be adjusted to your needs. Its important to not just go crazy an 
 turn everthing into a component. Their are a limited number of bits, its not infinite. Keep this in mind when
 creating components.


 SphericalTerrainRenderer
 AtmosphereRenderer
 ObjectRenderer
 BasicRenderer

 Material
 TerrainMaterial
 AtmosphereMaterial
 PhongMaterial
 PBRMaterial


 struct BasicMaterial
 {};
 struct PBRMaterial
 { ... };

 struct Mesh
 {
    VertexBuffer* vbo;
    IndexBuffer* ibo;
 };



 class BasicMaterialMeshRenderer
 {
    ShaderProgram* shader_program;
 }
 class BasicMaterialAnimMeshRenderer
 {
    ShaderProgram* shader_program;
 }
 
 

 struct AtmosphereMaterial
 {
    // atmosphere parameters
 };
 
 entity->add< AtmosphereMaterial >();
 entity->add< Atmosphere >();
 
 
 
 struct TerrainMaterial
 {
    // grass_textures, rock_textures, dirt_textures etc...
    // tese texture will be mapped with triplaner mapping
 };
 
 struct SphericalTerrain
 {
    SphericalQuadtree quadtrees[ 6 ];
    DrawPatchBuffer* draw_buffer;
    HeightmapsBuffer* heightmaps;
    ...
 };

 entity->add< TerrainMaterial >();
 entity->add< SphericalTerrain >();







struct StdVertex
{
    kege::vec3 position;
    kege::vec3 normal;
    kege::vec2 texcoord;
    kege::vec3 tangent;
    kege::vec3 bitangent;
};
class DrawCommand
{
public:
    virtual void draw( kege::CommandBuffer* command_buffer ) = 0;
    virtual ~DrawCommand(){}
};
class ArrayedDrawCommand
{
public:
    virtual void draw( kege::CommandBuffer* command_buffer ) = 0;
    virtual ~ArrayedDrawCommand(){}
};
class IndexedDrawCommand
{
public:
    virtual void draw( kege::CommandBuffer* command_buffer ) = 0;
    virtual ~IndexedDrawCommand(){}
};

class Skeleton
{
public:
    virtual void bind( kege::CommandBuffer* command_buffer ) = 0;
    virtual ~Skeleton(){}
};

class Mesh
{
public:
    virtual void draw( kege::CommandBuffer* command_buffer, kege::ShaderProgram* shader_program ) = 0;
    virtual void bind( kege::CommandBuffer* command_buffer, kege::ShaderProgram* shader_program ) = 0;
    virtual ~Mesh(){}
};

class SpriteMesh
{
public:
    virtual void draw( kege::CommandBuffer* command_buffer, kege::ShaderProgram* shader_program ) = 0;
    virtual void bind( kege::CommandBuffer* command_buffer, kege::ShaderProgram* shader_program ) = 0;
    virtual ~SpriteMesh(){}
};


//class StdMesh : public kege::Mesh
//{
//public:
//
//    void bind( kege::CommandBuffer* command_buffer, kege::ShaderProgram* shader_program );
//    void draw( kege::CommandBuffer* command_buffer, kege::ShaderProgram* shader_program );
//    ~StdMesh();
//    StdMesh();
//
//    kege::Ref< kege::VertexBuffer > vertex_buffer;
//    ArrayedDrawCommand draw_command;
//};

class SkeletalMesh : public kege::Mesh
{
public:

    void bind( kege::CommandBuffer* command_buffer, kege::ShaderProgram* shader_program );
    void draw( kege::CommandBuffer* command_buffer, kege::ShaderProgram* shader_program );
    ~SkeletalMesh();
    SkeletalMesh();

    kege::Ref< kege::VertexBuffer > _vertex_buffer;
    kege::Ref< kege::IndexBuffer > _index_buffer;
    kege::Ref< kege::DrawCommand > _draw_comand;
    kege::Ref< Skeleton > _skeleton;
};

class BillboardMesh : public kege::Mesh
{
public:

    void bind( kege::CommandBuffer* command_buffer, kege::ShaderProgram* shader_program );
    void draw( kege::CommandBuffer* command_buffer, kege::ShaderProgram* shader_program );
    ~BillboardMesh();
    BillboardMesh();

    kege::Ref< kege::VertexBuffer > vertex_buffer;
    ArrayedDrawCommand draw_command;
};
