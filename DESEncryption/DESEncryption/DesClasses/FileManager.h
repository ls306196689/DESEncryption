//
//  MYFileManager.h
//  testAnimation
//
//  Created by pengfei sun on 5/23/13.
//
//

#ifndef __testAnimation__MYFileManager__
#define __testAnimation__MYFileManager__


#include <iostream>
std::string dictionaryTostring(NSDictionary* dic);
class CCFileManager {
    
    
public:
    static const char* getFullPath(const char* filename);
    static const char* getDocumentPath();
    static const char* getTempPath();
    static const char* getFullPathInDocument(const char* filename);
    static const char* getFullPathInTmp(const char* filename);
    
    static long getFileLength(const char* filepath);
    static bool getFileData(const char* filepath, char *filedata, long filelength );
    static bool writeDataToFile(const char* filepath,const char *filedata, long filelength );
};

#endif /* defined(__testAnimation__MYFileManager__) */
