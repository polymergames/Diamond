/*
    Copyright 2015 Ahnaf Siddiqui

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

#ifndef D_COMPONENT_H
#define D_COMPONENT_H

#include <functional>
#include "D_typedefs.h"

namespace Diamond {
    class Component {
    public:
        virtual ~Component() {
            if (m_remover)
                m_remover();
        }

        virtual void    update(tD_delta delta) {}

        /**
         Set a function that this component can call when it's destroyed
         to remove itself from any system that is using it.
        */
        void            setRemover(const std::function<void(void)> &remover) { m_remover = remover; }

    private:
        std::function<void(void)> m_remover;
    };
}

#endif // D_COMPONENT_H
