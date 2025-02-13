//#import <Foundation/Foundation.h>
#include <substrate.h>
#include <string>

static std::string gulfOfMexicoName("Gulf of Mexico");

static std::string *(*orig_title)(void*,uint64_t);
static std::string *myTitle(void *t,uint64_t v) {
	if(*((uint64_t*)t+49)==15921830447484598765ULL) {
		return &gulfOfMexicoName;
	}
	return orig_title(t,v);
	/*char *title=orig_title(t,v);
	if(!title)
		return NULL;
	if(!strcmp(title,"Gulf of Mexico"))
		title[0]='T';
	return title;*/
}

__attribute__((constructor)) static void _gom_load() {
	MSImageRef img=MSGetImageByName("/System/Library/PrivateFrameworks/VectorKit.framework/VectorKit");
	if(img) {
		void *mdLabelTitle=MSFindSymbol(img,"__ZNK2md17PointLabelFeature10publicNameEm");
		MSHookFunction(mdLabelTitle,(void*)myTitle, (void**)&orig_title);
	}
}