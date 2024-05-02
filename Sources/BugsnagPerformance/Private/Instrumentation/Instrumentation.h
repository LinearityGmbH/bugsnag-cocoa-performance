//
//  Instrumentation.h
//  BugsnagPerformance-iOS
//
//  Created by Karl Stenerud on 24.04.23.
//  Copyright © 2023 Bugsnag. All rights reserved.
//

#pragma once

#import "../PhasedStartup.h"
#import "../Instrumentation/AppStartupInstrumentation.h"
#import "../Instrumentation/NetworkInstrumentation.h"
#import "../Instrumentation/ViewLoadInstrumentation.h"

namespace bugsnag {

class Instrumentation: public PhasedStartup {
public:
    Instrumentation(std::shared_ptr<Tracer> tracer,
                    std::shared_ptr<SpanAttributesProvider> spanAttributesProvider,
                    std::shared_ptr<SpanStackingHandler> spanStackingHandler,
                    std::shared_ptr<Sampler> sampler) noexcept
    : appStartupInstrumentation_(std::make_shared<AppStartupInstrumentation>(tracer, spanAttributesProvider))
    , viewLoadInstrumentation_(std::make_shared<ViewLoadInstrumentation>(tracer, spanAttributesProvider))
    , networkInstrumentation_(std::make_shared<NetworkInstrumentation>(tracer,
                                                                       spanAttributesProvider,
                                                                       spanStackingHandler,
                                                                       sampler))
    {}

    void earlyConfigure(BSGEarlyConfiguration *config) noexcept;
    void earlySetup() noexcept;
    void configure(BugsnagPerformanceConfiguration *config) noexcept;
    void start() noexcept;

    void didStartViewLoadSpan(NSString *name) noexcept { appStartupInstrumentation_->didStartViewLoadSpan(name); }
    void willCallMainFunction() noexcept { appStartupInstrumentation_->willCallMainFunction(); }

private:
    Instrumentation() = delete;

    std::shared_ptr<class AppStartupInstrumentation> appStartupInstrumentation_;
    std::shared_ptr<class ViewLoadInstrumentation> viewLoadInstrumentation_;
    std::shared_ptr<class NetworkInstrumentation> networkInstrumentation_;
};

}
