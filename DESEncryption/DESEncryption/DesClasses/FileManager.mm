//
//  MYFileManager.cpp
//  testAnimation
//
//  Created by pengfei sun on 5/23/13.
//
//
#ifdef TARGET_OS_MAC
#include <Cocoa/Cocoa.h>
#elif  TARGET_OS_IPHONE
#include <UIKit/UIKit.h>
#endif
#include <fstream>
#include "FileManager.h"

#define TYPE_NSARRAY_RYE 0
#define TYPE_NSDICTIONARY_RYE 1
#define TYPE_NSSTRING_RYE 2
#define TYPE_NSNUMBER_RYE 3
#define TYPE_NSDATA_RYE   4
#define TYPE_NSDATE_RYE   5
#define TYPE_NSBOOL_RYE   6

using namespace std;

string dictionary_String(NSDictionary* dic);
string arryToString(NSArray*array);
string dictionaryTostring(NSDictionary* dic);
int    getObjectType(id obj);

string dictionaryTostring(NSDictionary* dic)
{
    if (dic == nil) {
        return "";
    }
    else
    {
        
        string str_dic  =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">"
        "<plist version=\"1.0\">\n";
        str_dic = str_dic+ dictionary_String(dic) + "</plist>";
        return str_dic;
    }
}
string dictionary_String(NSDictionary* dic)
{
    string str = "";
    if (dic == nil) {
        return "";
    }
    str.append("<dict>\n");
    NSArray* allkeys = [dic allKeys];
    int counter = allkeys.count;
    for (int i = 0; i < counter; i ++) {
        NSString* key = [allkeys objectAtIndex:i];
        str.append("<key>" + string([key UTF8String]) + "</key>\n");
        id ob = [dic objectForKey:key];
        int type = getObjectType(ob);
        switch (type) {
            case TYPE_NSBOOL_RYE:
            {
                NSString *strdata = [NSString stringWithFormat:@"%@",ob];
                if ([strdata boolValue]) {
                    str.append("<false/>");
                }
                else
                {
                    str.append("<true/>");
                }
            }
                break;
            case TYPE_NSNUMBER_RYE:
            {
                NSString *strdata = [NSString stringWithFormat:@"%@",ob];
                str.append("<integer>"+ string([strdata UTF8String])+"</integer>");
            }
                break;
            case TYPE_NSARRAY_RYE:
                str.append(arryToString(ob));
                break;
            case TYPE_NSDATE_RYE:
            {
                NSString* strdate = [NSString stringWithFormat:@"%@",ob];
                str.append("<date>" + string([strdate UTF8String]) + "</date>");
            }
                break;
            case TYPE_NSDATA_RYE:
            {
                NSString* strdate = [NSString stringWithFormat:@"%@",ob];
                str.append("<data>" + string([strdate UTF8String]) + "</data>");
            }
                break;
            case TYPE_NSDICTIONARY_RYE:
                str.append(dictionary_String(ob));
                break;
            case TYPE_NSSTRING_RYE:
            {
                NSString* strdate = [NSString stringWithFormat:@"%@",ob];
                str.append("<string>" + string([strdate UTF8String]) + "</string>");
            }
                break;
                
            default:
                break;
        }
        
    }
    str.append("</dict>\n");
    
    return str;
}
int    getObjectType(id obj)
{
    NSString *type = [NSString stringWithFormat:@"%@",[obj class]];
    
    if ([type rangeOfString:@"Boolean"].location != NSNotFound) {
        return TYPE_NSBOOL_RYE;
    }
    else if ([type rangeOfString:@"Number"].location != NSNotFound)
    {
        return TYPE_NSNUMBER_RYE;
    }
    else if ([type rangeOfString:@"Data"].location != NSNotFound)
    {
        return TYPE_NSDATA_RYE;
    }
    else if ([type rangeOfString:@"Dictionary"].location != NSNotFound)
    {
        return TYPE_NSDICTIONARY_RYE;
    }
    else if ([type rangeOfString:@"Date"].location != NSNotFound)
    {
        return TYPE_NSDATE_RYE;
    }
    else if ([type rangeOfString:@"Array"].location != NSNotFound)
    {
        return TYPE_NSARRAY_RYE;
    }
    else if ([type rangeOfString:@"String"].location != NSNotFound)
    {
        return TYPE_NSSTRING_RYE;
    }
    return -1;
}

string arryToString(NSArray* array)
{
    string str = "";
    if (array == nil) {
        return "";
    }
    str.append("<array>\n");
    
    int counter = array.count;
    for (int i = 0; i < counter; i ++) {
        id ob = [array objectAtIndex:i];
        
        int type = getObjectType(ob);
        switch (type) {
            case TYPE_NSBOOL_RYE:
            {
                NSString *strdata = [NSString stringWithFormat:@"%@",ob];
                if ([strdata boolValue]) {
                    str.append("<false/>");
                }
                else
                {
                    str.append("<true/>");
                }
            }
                break;
            case TYPE_NSNUMBER_RYE:
            {
                NSString *strdata = [NSString stringWithFormat:@"%@",ob];
                str.append("<integer>"+ string([strdata UTF8String])+"</integer>");
            }
                break;
            case TYPE_NSARRAY_RYE:
                str.append(arryToString(ob));
                break;
            case TYPE_NSDATE_RYE:
            {
                NSString* strdate = [NSString stringWithFormat:@"%@",ob];
                str.append("<date>" + string([strdate UTF8String]) + "</date>");
            }
                break;
            case TYPE_NSDATA_RYE:
            {
                NSString* strdate = [NSString stringWithFormat:@"%@",ob];
                str.append("<data>" + string([strdate UTF8String]) + "</data>");
            }
                break;
            case TYPE_NSDICTIONARY_RYE:
                str.append(dictionary_String(ob));
                break;
            case TYPE_NSSTRING_RYE:
            {
                NSString* strdate = [NSString stringWithFormat:@"%@",ob];
                str.append("<string>" + string([strdate UTF8String]) + "</string>");
            }
                break;
        }
        
    }
    str.append("</array>\n");
    
    return str;
}

const char* CCFileManager::getDocumentPath()
{
    NSString* str = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString*ful = [NSString stringWithFormat:@"%@%@",str,@"/"];
    return [ful UTF8String];
}
const char* CCFileManager::getTempPath()
{
    NSString* str = NSTemporaryDirectory();
    return [str UTF8String];
}
const char* CCFileManager::getFullPathInDocument(const char* filename)
{
    NSString* str = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString*ful = [NSString stringWithFormat:@"%@%@%s",str,@"/",filename];
    return [ful UTF8String];
}
const char* CCFileManager::getFullPathInTmp(const char* filename)
{
    NSString* str = NSTemporaryDirectory();
    NSString*ful = [NSString stringWithFormat:@"%@%s",str,filename];
    return [ful UTF8String];
}

long CCFileManager::getFileLength(const char* filepath)
{
    
    assert(filepath != NULL);
    
    std::string path(filepath);

    long length = 0;
    fstream file;
    file.open(filepath,ios::in);
    
    if (file.good()) {
        if (path.find(".plist") == path.length()- 6) {
            NSDictionary* dic = [NSDictionary dictionaryWithContentsOfFile:[NSString stringWithFormat:@"%s",filepath]];
            string data = dictionaryTostring(dic);
            length = data.length();
        }
        else
        {
            file.seekg(0,ios::end);
            length = file.tellg();
        }
    }
    return length;
}
bool CCFileManager::getFileData(const char* filepath, char *filedata, long filelength )
{
    assert(filepath != NULL);
    assert(filedata != NULL);
    std::string path(filepath);
    bool res = true;
    fstream file;
    file.open(filepath,ios::in);
    if (file.good()) {
        if (path.find(".plist") == path.length()- 6) {
            NSDictionary* dic = [NSDictionary dictionaryWithContentsOfFile:[NSString stringWithFormat:@"%s",filepath]];
            string data = dictionaryTostring(dic);
            memcpy(filedata, data.c_str(), data.length());
        }
        else
        {
            
            file.read(filedata, filelength);
        }
    }
    else
    {
        res = false;
    }
    return res;
}
const char* CCFileManager::getFullPath(const char* filename)
{
    NSString* str = [NSString stringWithFormat:@"%s",filename ];
    NSRange range = [str rangeOfString:@"." options:NSBackwardsSearch];
    NSRange rangtype = NSMakeRange(0, range.location +1);
    NSRange rangname = NSMakeRange(range.location, str.length - range.location);
    NSString* type = [str stringByReplacingCharactersInRange:rangtype withString:@""];
    NSString* name = [str stringByReplacingCharactersInRange:rangname withString:@""];
    NSString*strfulpath = [[NSBundle mainBundle]pathForResource:name ofType:type];
    return [strfulpath UTF8String];
}
bool CCFileManager::writeDataToFile(const char* filepath,const char *filedata, long filelength )
{
    assert(filepath != NULL);
    assert(filedata != NULL);
    bool res = true;
    fstream file;
    file.open(filepath,ios::out);
    
    if (file.good()) {
        file.write(filedata, filelength);
    }
    else
    {
        res = false;
    }
    file.close();
    return res;
}