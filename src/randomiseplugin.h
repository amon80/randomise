// exampleplugin.h : main header file for the BRIDGEREMOVAL DLL
//

#ifndef RANDOMISEPLUGIN_H
#define RANDOMISEPLUGIN_H

#include "BVQXPluginInterface.h"

/*
 * This class implements a plugin by deriving it from the generic PluginInterface
 */
class RandomisePlugin : public BVQXPluginInterface
{
public:
	
	PLUGIN_ACCESS RandomisePlugin();
	PLUGIN_ACCESS virtual ~RandomisePlugin();

	PLUGIN_ACCESS bool initPlugin();
	PLUGIN_ACCESS bool execute();
private:
    int num_of_maps;
    struct VMR_Header vmr_header;
    struct NR_VMPs_Header vmps_header;
};

// To avoid C++ name mangling problems, we need to bootstrap access of plugin via C functions
//
extern "C" {
	PLUGIN_ACCESS BVQXPluginInterface *createPlugin();
	PLUGIN_ACCESS const char *getPluginName();
	PLUGIN_ACCESS const char *getPluginDescription();
	PLUGIN_ACCESS const char *getAuthor();
	PLUGIN_ACCESS const char *getHelpFile();
	PLUGIN_ACCESS const char *getPluginVersion();
	PLUGIN_ACCESS const char *getGUIScript();
}


#endif // RANDOMISEPLUGIN_H
