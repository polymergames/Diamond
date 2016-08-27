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

#ifndef Q_COLLIDER_2D_H
#define Q_COLLIDER_2D_H

#include <functional>
#include "Q_Rigidbody2D.h"
#include "Q_typedefs.h"

namespace Quantum2D {
    enum Coltype {
        eNONE, eAABB, eCIRCLE, ePOLY, eNUMCOLTYPES
    };

    class Collider2D {
    public:
        Collider2D(const BodyList &bodylist,
                   Coltype type,
                   body2d_id body,
                   void *parent,
                   const std::function<void(void *other)> &onCollision,
                   QLayer layer = 0)
            : bodylist(bodylist),
              type(type),
              body(body),
              parent(parent),
              onCollision(onCollision),
              layer(layer) {};
        
        
        virtual ~Collider2D() {};

        Coltype getType() const { return type; }
        
        QLayer getLayer() const { return layer; }
        void setLayer(QLayer newlayer) { layer = newlayer; }
        
        body2d_id getBodyID() const { return body; }

        void *getParent() const { return parent; }

        void onCollide(const Collider2D *other) { onCollision(other->getParent()); }

        void setColFunc(const std::function<void(void *other)> &onCollision) { this->onCollision = onCollision; }
        
        /**
         Called by a physics world once per frame to update this collider.
        */
        virtual void update(tQ_delta delta) = 0;

    protected:
        Coltype type;
        QLayer layer;
        
        const BodyList &bodylist;
        body2d_id body;
        
        void *parent;
        std::function<void(void *other)> onCollision;
    };
}

#endif // Q_COLLIDER_2D_H
