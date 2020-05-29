#pragma once

namespace e_table {
    namespace utils {
        template<class T>
        class SmartPtr;

        template<class U, class T>
        SmartPtr<U> smart_ptr_cast(const SmartPtr<T>& p);

        template<class T>
        class SmartPtr {
        protected:
            template<class Z> friend class SmartPtr;
            template<class U, class Z> friend SmartPtr<U> smart_ptr_cast(const SmartPtr<Z>& p);
            // TODO: fix it to work only with this class/type
            // template<class U> friend SmartPtr<U> smart_ptr_cast(SmartPtr<T> p);
            // template<class U> friend SmartPtr<T> smart_ptr_cast(SmartPtr<U> p);
            
            T* t;
            unsigned int* count;
        public:
            SmartPtr() : t(nullptr), count(nullptr) {}

            SmartPtr(T* t) : t(t) {
                if(t != nullptr) {
                    count = new unsigned int(1);
                }
            }

            SmartPtr(const SmartPtr& p) : t(p.t), count(p.count) { ++(*count); }

            template<class Z>
            SmartPtr(const SmartPtr<Z>& p) : t(p.t), count(p.count) { ++(*count); }

            ~SmartPtr() {
                if(!is_null() && --(*count) == 0) {
                    delete t;
                    delete count;
                }
            }

            SmartPtr& operator= (const SmartPtr& p) {
                T* const old_t = t;
                unsigned int* const old_count = count;

                t = p.t;
                count = p.count;
                ++(*count);

                if (old_t != nullptr && --(*old_count) == 0) {
                    delete old_t;
                    delete old_count;
                }
                return *this;
            }

            T* operator-> () const { return t; }
            T& operator* ()  { return *t; }
            const T& operator* () const { return *t; }

            bool is_null() const { return t == nullptr; }
        };

        template<class U, class T>
        SmartPtr<U> smart_ptr_cast(const SmartPtr<T>& p) {
            U* t = dynamic_cast<U*>(p.t);
            if(t == nullptr) return nullptr;

            SmartPtr<U> new_p(t);
            new_p.count = p.count;
            ++(*new_p.count);

            return new_p;
        }

    }
}