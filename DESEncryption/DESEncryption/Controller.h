//
//  Controller.h
//  DESEncryption
//
//  Created by pengfei sun on 5/27/13.
//  Copyright (c) 2013 pengfei sun. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Controller : NSObject
{
    NSMutableArray *filenames;
    bool isAlive;
}
@property (assign) NSThread* mythread;
@property (assign) IBOutlet NSArrayController *arrayController;
@property (assign) IBOutlet NSSecureTextField* m_textfield;
-(IBAction) OK:(id)sender;
-(IBAction)jiemi:(id)sender;
-(void) enctypt;
-(void) dencrypt;
@end
