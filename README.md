Graphics System for Custom Game Engine

This graphics system is a standalone component of my custom game engine. Coded in Xcode on MacOSX.
require Vulkan Graphics API and GLFW for window management

code example, from initialization to rendering something on screen.

```
    Ref< Graphics > graphics = Graphics::create();
    graphics->setInputCallback();
    graphics->setTitle( "Hello Cube" );
    graphics->setHeight( 720 );
    graphics->setWidth( 1280 );

    if ( !graphics->init() )
    {
        graphics->uninit();
        return 0;
    }

    Renderer* renderer = graphics->renderer();
    RenderTarget* render_target = graphics->getRenderTarget();


    Ref< ShaderProgram > shader_program = kege::ShaderProgram::load
    (
        "/Users/kae/Projects/vulkan-renderer/assets/shaders/graphics/basic/shader.json",
        render_target->getFramebuffer()
    );
    if ( !shader_program )
    {
        graphics->uninit();
        return 0;
    }
    
    Ref< ShaderResource > camera_shader_resource = ShaderResource::create();
    camera_shader_resource->insertUniformBuffer
    (
        "ShaderCameraParams", 0,
        kege::UniformBuffer::create({ sizeof( ShaderCameraParams ), nullptr, kege::STREAM_BUFFER })
    );
    camera_shader_resource->update();

    Cuboid cube( 0.0, 0.5 );
    while( graphics->windowIsOpen() )
    {
        ShaderCameraParams camera_params = { kege::mat44(1.0), kege::mat44(1.0), kege::vec3(1.0) };
        if ( renderer->begin() )
        {
            // update uniform buffer
            camera_shader_resource->get( 0 ).uniform->buffer()->setBufferData( 0, sizeof( ShaderCameraParams ), &camera_params );

            // begin a render-process. you can have multiple render-processes
            RenderProcess* process = renderer->beginRenderProcess( render_target, 0 );
            {
                // begin a render-phase. you can have multiple render-phasees
                RenderPhase* phase = process->beginRenderPhase();
                phase->setViewport();
                phase->setScissor();
                phase->clearBuffers();
                process->endRenderPhase( phase );

                phase = process->beginRenderPhase();
                {
                    // set the render area viewport and scissor
                    phase->setViewport();
                    phase->setScissor();

                    // bind resource globally
                    camera_shader_resource->bind( phase->commandBuffer(), 0 );

                    // bind shader-program
                    shader_program->use( phase->commandBuffer() );
                    ObjectMatrices object_matrices = { kege::mat44(1.0), kege::mat33(1.0) };
                    shader_program->pushConstants
                    (
                        phase->commandBuffer(),
                        {
                            kege::VERTEX_SHADER, 0,
                            sizeof( ObjectMatrices ), &object_matrices
                        }
                    );
                    cube.bind( phase->commandBuffer() );
                    cube.draw( phase->commandBuffer() );
                }
                process->endRenderPhase( phase );
            }
            renderer->endRenderProcess( process );
            renderer->end();
        }
        graphics->poolEvents();
    }
    camera_shader_resource.clear();
    shader_program.clear();
    cube.clear();
    graphics->uninit();
    return 0;
```
