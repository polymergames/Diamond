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

#include "D_Benchmark.h"
#include "D_Log.h"

Diamond::FPSCounter::FPSCounter(tD_delta countInterval)
    : countInterval(countInterval),
      currentInterval(0),
      currentSumFrames(0),
      totalDelta(0),
      totalFrames(0) {}

float Diamond::FPSCounter::fps(tD_delta delta) {
    deltas.push_back(delta);

    currentInterval += delta;
    totalDelta += delta;
    currentSumFrames += 1;
    totalFrames += 1;

    float fps = (float)currentSumFrames / currentInterval;

    while (currentInterval > countInterval) {
        currentInterval -= deltas.front();
        currentSumFrames -= 1;
        deltas.pop_front();
    }

    return fps;
}

float Diamond::FPSCounter::overallFPS() {
    return (float)totalFrames / totalDelta;
}


Diamond::BenchmarkLogger::BenchmarkLogger(std::ostream &stream,
                                          tD_delta countInterval,
                                          float unitsPerSecond)
    : fpsMachine(countInterval), unitsPerSecond(unitsPerSecond), mStream(stream) {
    mStream << std::endl << "Benchmark started on ";
    Log::logTime(mStream);
    mStream << std::endl;

    // header
    mStream << "Delta\tInstant FPS\t"
            << (int)(countInterval / unitsPerSecond) << "-sec avg. FPS\t"
            << "Total avg. FPS" << std::endl;
}

void Diamond::BenchmarkLogger::update(tD_delta delta) {
    mStream << delta << "\t"
            << unitsPerSecond / delta << "\t"  // Instant FPS
            << fpsMachine.fps(delta) * unitsPerSecond << "\t" // time interval FPS
            << fpsMachine.overallFPS() * unitsPerSecond << std::endl; // total average FPS
}
