//
//  WeakSpansListTests.m
//  BugsnagPerformance-iOSTests
//
//  Created by Karl Stenerud on 08.12.23.
//  Copyright © 2023 Bugsnag. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "WeakSpansList.h"
#import "BugsnagPerformanceSpan+Private.h"
#import "SpanOptions.h"

using namespace bugsnag;

@interface WeakSpansListTests : XCTestCase

@end

static BugsnagPerformanceSpan *createSpan() {
    return [[BugsnagPerformanceSpan alloc]
            initWithSpan:std::make_unique<Span>(@"test",
                                                IdGenerator::generateTraceId(),
                                                IdGenerator::generateSpanId(),
                                                IdGenerator::generateSpanId(),
                                                SpanOptions().startTime,
                                                BSGFirstClassNo,
                                                ^void(std::shared_ptr<SpanData>) {
                                                })];
}

@implementation WeakSpansListTests

- (void)testAllReleased {
    WeakSpansList list;
    @autoreleasepool {
        list.add(createSpan());
        list.add(createSpan());
        list.add(createSpan());
    }
    XCTAssertEqual(3U, list.count());
    list.compact();
    XCTAssertEqual(0U, list.count());
}

- (void)testNoneReleased {
    WeakSpansList list;
    list.add(createSpan());
    list.add(createSpan());
    list.add(createSpan());
    XCTAssertEqual(3U, list.count());
    list.compact();
    XCTAssertEqual(3U, list.count());
}

- (void)testSomeReleased {
    WeakSpansList list;
    list.add(createSpan());
    @autoreleasepool {
        list.add(createSpan());
        list.add(createSpan());
        list.add(createSpan());
    }
    list.add(createSpan());
    XCTAssertEqual(5U, list.count());
    list.compact();
    XCTAssertEqual(2U, list.count());
}

@end
