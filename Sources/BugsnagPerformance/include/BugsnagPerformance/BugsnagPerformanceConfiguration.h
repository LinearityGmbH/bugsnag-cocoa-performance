//
//  BugsnagPerformanceConfiguration.h
//  BugsnagPerformance
//
//  Created by Nick Dowell on 23/09/2022.
//

#import <BugsnagPerformance/BugsnagPerformanceErrors.h>
#import <BugsnagPerformance/BugsnagPerformanceNetworkRequestInfo.h>

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef BOOL (^ BugsnagPerformanceViewControllerInstrumentationCallback)(UIViewController *viewController);

OBJC_EXPORT
@interface BugsnagPerformanceConfiguration : NSObject

- (instancetype)initWithApiKey:(NSString *)apiKey NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)loadConfig;

- (BOOL) validate:(NSError * __autoreleasing _Nullable *)error NS_SWIFT_NAME(validate());

@property (nonatomic) NSString *apiKey;

@property (nonatomic) NSURL *_Nullable endpoint;

@property (nonatomic) BOOL autoInstrumentAppStarts;

@property (nonatomic) BOOL autoInstrumentViewControllers;

@property (nonatomic) BOOL autoInstrumentNetworkRequests;

/**
 *  The version of the application
 */
@property (copy, nullable, nonatomic) NSString *appVersion;

/**
 *  The app's bundleVersion
 */
@property (copy, nullable, nonatomic) NSString *bundleVersion;

@property (nullable, nonatomic) BugsnagPerformanceViewControllerInstrumentationCallback viewControllerInstrumentationCallback;

@end

@interface BugsnagPerformanceConfiguration (/* App metadata */)

/**
 *  The release stage of the application, such as production, development, beta
 *  et cetera
 */
@property (copy, nonatomic) NSString *releaseStage;

/**
 *  Release stages which are allowed to notify Bugsnag
 */
@property (copy, nullable, nonatomic) NSSet<NSString *> *enabledReleaseStages;

/**
 * Callback used to control how network request spans are created.
 */
@property(nullable, nonatomic) BugsnagPerformanceNetworkRequestCallback networkRequestCallback;

@end

NS_ASSUME_NONNULL_END
