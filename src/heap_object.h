//
// Created by cab on 15.02.24.
//

#ifndef HEAP_OBJECT_H
#define HEAP_OBJECT_H

#include <vector>

namespace cab {

    struct IHeapObject;

    void addToStorage(IHeapObject *);

    struct IHeapObject {
        IHeapObject() {
            addToStorage(this);
        }
        virtual ~IHeapObject() {}
    };


    class ObjectStorage {
        std::vector<IHeapObject *> _objects;
        friend void addToStorage(IHeapObject *);
    public:
        ObjectStorage() {}
        ~ObjectStorage() {
            for (IHeapObject *obj : _objects) {
                delete obj;
            }
        }
    };

    namespace {
        ObjectStorage _storage;
    }

    inline void addToStorage(IHeapObject *o) {
        _storage._objects.push_back(o);
    }

}

#endif //HEAP_OBJECT_H
