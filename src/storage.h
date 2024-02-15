//
// Created by cab on 01.06.19.
//

#ifndef SHASHKI_STORAGE_H
#define SHASHKI_STORAGE_H

namespace cab {

    template<class T, int n>
    struct Block {
        T list[n];
        Block *next;
    };

    template<class _Block>
    class Storage {
        _Block *free = nullptr;
    public:
        ~Storage() {
            release();
        }

        _Block *get() {
            if (free == nullptr) {
                free = new _Block;
                free->next = nullptr;
            }
            _Block *block = free;
            free = free->next;
            return block;
        }

        void freeBlock(_Block *block) {
            block->next = free;
            free = block;
        }

        void init(int size) {
            if (free) release();

            free = new _Block;
            free->next = nullptr;
            for (int i = 1; i < size; ++i) {
                _Block *b = new _Block;
                b->next = free;
                free = b;
            }
        }

        void release() {
            while (free) {
                _Block *next = free->next;
                delete free;
                free = next;
            }
        }
    };

    template<class _Block, class _T>
    class List {
        void *_block;
        Storage<_Block> *_storage;
    public:

        List(Storage<_Block> *storage) : _storage(storage) {
            _block = _storage->get();
        }

        ~List() {
            _storage->freeBlock((_Block *) _block);
        }

        _T &operator[](int i) {
            return ((_Block *) _block)->list[i];
        }

        _T *ptr() {
            return ((_Block *) _block)->list;
        }

    };

}

#endif //SHASHKI_STORAGE_H
