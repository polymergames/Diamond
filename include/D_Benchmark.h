/*
    Copyright 2017 Ahnaf Siddiqui

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef D_BENCHMARK_H
#define D_BENCHMARK_H

#include <deque>
#include <ostream>
#include "D_Component.h"

namespace Diamond {
    /**
     * Calculates the average frames per time unit
     * over the last countInterval time units.
     * Although FPS is in the name, the actual unit of time
     * is not assumed by this class.
     * For example, if millisecond units are passed
     * to this class for countInterval and delta,
     * then it will report frames per millisecond.
     */
    class FPSCounter {
    public:
        /**
         * countInterval is the length of time in tD_delta
         * over which average FPS should be calculated.
         */
        FPSCounter(tD_delta countInterval);

        /**
         * Updates the average FPS over the last countInterval
         * including the current frame.
         */
        float fps(tD_delta delta);

        /**
         * Calculates the overall average FPS since this object
         * was constructed. Requires fps to have been called every frame.
         */
        float overallFPS();

    private:
        std::deque<tD_delta> deltas;
        tD_delta countInterval;
        tD_delta currentInterval;
        int currentSumFrames;

        tD_time totalDelta;
        int totalFrames;
    };

    class BenchmarkLogger : public Component {
    public:
        /**
         * Benchmark results will be stored in ostream.
         *
         * countInterval is the length of time in tD_delta
         * over which average FPS should be calculated
         * (default is 10 seconds assuming delta is in milliseconds).
         *
         * unitsPerSecond is used to convert the delta
         * time unit passed in update to seconds
         * (the default value assumes that delta is in milliseconds).
         */
        BenchmarkLogger(std::ostream &stream,
                        tD_delta countInterval = 10000,
                        float unitsPerSecond = 1000);

        void update(tD_delta delta) override;

    private:
        FPSCounter fpsMachine;
        float unitsPerSecond;
        std::ostream &mStream;
    };
}

#endif // D_BENCHMARK_H
