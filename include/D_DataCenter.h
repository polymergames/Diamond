/*
    Copyright 2016 Ahnaf Siddiqui

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

#ifndef D_DATA_CENTER_H
#define D_DATA_CENTER_H

#include "D_sparsevector.h"
#include "D_Transform2.h"

namespace Diamond {
    class DataCenter {
    public:

        /**
         Creates a transform object and returns its id.
         The returned id can be used to access the transform with getTransform(id).
        */
        transform2_id genTransform() { return transforms.emplace_back(); }

        /**
         Returns a reference to the transform with the given id.
         Note: the reference returned is only guaranteed to be valid until the next time a new transform is created.
         Only use this reference immediately after calling this function!
        */
        Transform2<tD_pos, tD_rot> &getTransform(transform2_id tid) { return transforms[tid]; }

        /**
         Frees the given transform's memory.
        */
        void freeTransform(transform2_id tid) { transforms.erase(tid); }

    private:
        sparsevector<Transform2<tD_pos, tD_rot> > transforms;
    };
}

#endif // D_DATA_CENTER_H
