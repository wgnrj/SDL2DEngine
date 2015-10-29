#include <cstdio>

#include <fstream>
#include <string>

std::string
loadFileToString( std::string path )
{
    std::string content;
    std::ifstream sourceFile( path.c_str() );

    if ( sourceFile )
    {
        content.assign( ( std::istreambuf_iterator< char >( sourceFile ) ), std::istreambuf_iterator< char >() );
    }
    else
    {
        printf( "Unable to open file %s.\n", path.c_str() );
    }

    return content;
}

