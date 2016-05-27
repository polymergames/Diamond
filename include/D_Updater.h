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

#ifndef D_UPDATER_H
#define D_UPDATER_H

#include <functional>
#include "duSwapVector.h"

namespace Diamond {
    template <class T>
    class Updater {
    public:
        tD_id   addMember(T *member) {
            tD_id id = m_members.insert(member);

            // TODO: use SFINAE to check if has setRemover()
            std::function<void(void)> remover = std::bind(&Updater<T>::remove, this, id);
            member->setRemover(remover);

            return id;
        }

        void    remove(tD_id member_id) { m_members.erase(member_id); }

        void    update(tD_delta delta) {
            for (T* member : m_members)
                // TODO: use SFINAE to check update function signature
                member->update(delta);
        }

    private:
        SwapVector<T*> m_members;
    };
}

#endif // D_UPDATER_H
