function(ConfigureShader ShaderType ShaderFile ShaderSourceList)
    
    set(ShaderSource "")
    foreach (ShaderLine IN LISTS ShaderSourceList)
        set( ShaderSource "${ShaderSource}\n\t\t\"${ShaderLine}\\n\"" )
    endforeach()

    string( TOLOWER ${ShaderType} ShaderTypeLc )

    get_filename_component( ShaderName ${ShaderFile} NAME_WE )
    string( TOLOWER ${ShaderName} ShaderLcName )    

    set( OutputShaderName ${ShaderLcName}.h )
    configure_file( shader_template.h.in ${OutputShaderName} @ONLY )
    target_sources( ${EngineTargetName} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${OutputShaderName} )

endfunction()

function(ConfigureAllShaders ShaderDirectory ShaderType)

    file( GLOB ShaderList ${ShaderDirectory}/*.glsl )

    foreach ( Shader IN LISTS ShaderList )

        file( STRINGS ${Shader} Source )
        ConfigureShader( ${ShaderType} ${Shader} "${Source}" )

    endforeach()

endfunction()

ConfigureAllShaders( vertex OpenGLVertexShader )
ConfigureAllShaders( fragment OpenGLFragmentShader )