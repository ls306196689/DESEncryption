//
//  Controller.m
//  DESEncryption
//
//  Created by pengfei sun on 5/27/13.
//  Copyright (c) 2013 pengfei sun. All rights reserved.
//

#import "Controller.h"
#import "DESHeaders.h"

@implementation Controller
@synthesize mythread;
- (void) awakeFromNib
{
	filenames = [[NSMutableArray alloc] init];
    NSThread *thread = [[NSThread alloc]initWithTarget:self selector:@selector(threadMain:) object:nil];
    [thread start];
    self.mythread = thread;
    [thread release];
}
- (void) acceptFilenameDrag:(NSString *) filename
{
	[self.arrayController addObject:filename];
}
-(IBAction) OK:(id)sender
{
    [self enctypt];
//    [self performSelector:@selector(enctypt) onThread:self.mythread withObject:nil waitUntilDone:NO];
    
}
-(IBAction)jiemi:(id)sender
{
    [self dencrypt];
//    [self performSelector:@selector(dencrypt) onThread:self.mythread withObject:nil waitUntilDone:NO];
    
}
- (void)threadMain:(id)data {
    NSAutoreleasePool *pool = [NSAutoreleasePool new];
    
    NSRunLoop *runloop = [NSRunLoop currentRunLoop];
    [runloop addPort:[NSMachPort port] forMode:NSDefaultRunLoopMode];
    isAlive = YES;
    while (isAlive) { // 'isAlive' is a variable that is used to control the thread existence...
        [runloop runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
    }
    
    [pool release];
}
-(void) enctypt
{
    if (self.m_textfield.stringValue.length >= 8) {
        long counter = [filenames count];
        for (int i = 0; i < counter; i ++) {
            
            NSString* filepath = [filenames objectAtIndex:i];
            long filelength = CCFileManager::getFileLength([filepath UTF8String]);
            char * filedata = new char[filelength +1];
            CCFileManager::getFileData([filepath UTF8String], filedata, filelength);
            
            char *dddlength = new char[filelength + 17];
            CCDESEncrypt::DESEncrypt(filedata, dddlength, [self.m_textfield.stringValue UTF8String], filelength, true);
            NSString* newfilename = [NSString stringWithFormat:@"%@%s",filepath,"ttt"];
            CCFileManager::writeDataToFile([newfilename UTF8String], dddlength, filelength);
            delete [] filedata;
            delete []dddlength;
        }
        [self.arrayController removeObjects:filenames];
    }
}
-(void) dencrypt
{
    if (self.m_textfield.stringValue.length >= 8) {
        long counter = [filenames count];
        for (int i = 0; i < counter; i ++) {
            
            NSString* filepath = [filenames objectAtIndex:i];
            long filelength = CCFileManager::getFileLength([filepath UTF8String]);
            char * filedata = new char[filelength +1];
            CCFileManager::getFileData([filepath UTF8String], filedata, filelength);
            
            char *dddlength = new char[filelength + 17];
            CCDESEncrypt::DESEncrypt(filedata, dddlength, [self.m_textfield.stringValue UTF8String], filelength, false);
            NSString* newfilename = [filepath substringWithRange:NSMakeRange(0,filepath.length - 3)];
            
            CCFileManager::writeDataToFile([newfilename UTF8String], dddlength, filelength);
            delete [] filedata;
            delete []dddlength;
        }
        [self.arrayController removeObjects:filenames];
    }
}

@end
