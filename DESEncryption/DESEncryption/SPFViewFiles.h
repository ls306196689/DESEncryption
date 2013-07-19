//
//  SPFViewFiles.h
//  DESEncryption
//
//  Created by pengfei sun on 5/26/13.
//  Copyright (c) 2013 pengfei sun. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

@interface SPFViewFiles : NSImageView <NSDraggingSource, NSDraggingDestination, NSPasteboardItemDataProvider>
- (id)initWithCoder:(NSCoder *)coder;
@end
