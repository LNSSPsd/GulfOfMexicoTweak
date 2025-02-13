//#import <Foundation/Foundation.h>
#include <substrate.h>
#include <string>

static std::string gulfOfMexicoName("Gulf of Test");

int offset=0;

static std::string *(*orig_title)(void*,uint64_t);
static std::string *myTitle(void *t,uint64_t v) {
	if(*(uint64_t*)((uint64_t)t+offset)==15921830447484598765ULL) {
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
		uint32_t *featureIDFunc=(uint32_t*)MSFindSymbol(img,"__ZNK2md17PointLabelFeature9featureIDEv");
		uint32_t featureIDLDRInstruction=*featureIDFunc;
		// https://developer.arm.com/documentation/ddi0596/2020-12/Base-Instructions/LDR--immediate---Load-Register--immediate--
		offset=((featureIDLDRInstruction>>10)&((1<<12)-1))<<3; // get imm12 and lsl 3
		// directly decode instruction as a workaround of PAC
		void *mdLabelTitle=MSFindSymbol(img,"__ZNK2md17PointLabelFeature10publicNameEm");
		MSHookFunction(mdLabelTitle,(void*)myTitle, (void**)&orig_title);
	}
}