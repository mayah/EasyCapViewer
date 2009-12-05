/* Copyright (c) 2009, Ben Trask
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * The names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY BEN TRASK ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL BEN TRASK BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
#import <CoreVideo/CoreVideo.h>

// Models
@class ECVVideoStorage;

// Other Sources
@class ECVReadWriteLock;

@interface ECVVideoFrame : NSObject <NSLocking>
{
	@protected
	ECVVideoStorage *_videoStorage;
	ECVFieldType _fieldType;
	off_t _length;

	ECVReadWriteLock *_lock;
	NSUInteger _bufferIndex;
}

- (id)initWithStorage:(ECVVideoStorage *)storage bufferIndex:(NSUInteger)index fieldType:(ECVFieldType)type;
@property(readonly) ECVVideoStorage *videoStorage;
@property(readonly) NSUInteger bufferIndex;
@property(readonly) ECVFieldType fieldType;

@property(readonly) BOOL hasBuffer;
@property(readonly) void *bufferBytes;
- (BOOL)lockIfHasBuffer;

- (void)clearRange:(NSRange)range resetLength:(BOOL)flag;
- (void)clear;
- (void)clearHead;
- (void)clearTail;

- (void)fillWithFrame:(ECVVideoFrame *)frame;
- (void)blurWithFrame:(ECVVideoFrame *)frame;
- (void)appendBytes:(void const *)bytes length:(size_t)length;
- (void)copyToPixelBuffer:(CVPixelBufferRef)pixelBuffer;

- (void)removeFromStorage;

@end
