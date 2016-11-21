/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus <https://github.com/maldicion069/monkeybrushplusplus>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef __MB_ANY__
#define __MB_ANY__

// Code based on
// http://www.codeproject.com/Articles/11250/High-Performance-Dynamic-Typing-in-C-using-a-Repla

#include <stdexcept>

namespace MB
{
    namespace anyimpl
    {
        struct bad_any_cast
        {
        };

        struct empty_any
        {
        };

        struct base_any_policy
        {
            virtual ~base_any_policy() {}
            virtual void static_delete( void** x) = 0;

            virtual void copy_from_value(void const* src, void** dest) = 0;

            virtual void clone(void* const* src, void** dest) = 0;

            virtual void move(void* const* src, void** dest) = 0;

            virtual void* get_value(void** src) = 0;

            virtual size_t get_size() = 0;

        };

        template<typename T>
        struct typed_base_any_policy : base_any_policy
        {
            virtual size_t get_size() { return sizeof(T); }
        };

        template<typename T>
        struct small_any_policy : typed_base_any_policy<T>
        {

            virtual void static_delete(void** /*x*/) { }

            virtual void copy_from_value(void const* src, void** dest)
            {
                //This used to be:
                //new(dest) T(*reinterpret_cast<T const*>(src));
                //But this is the small_any_policy, and ints and other small objects
                //shouldn't need to be pointed to by an object.
                //In this case, we are really receiving the address of the the 'object' variable
                *dest = *(reinterpret_cast<void**>((const_cast<void*>(src))));
            }

            virtual void clone(void* const* src, void** dest) { *dest = *src; }

            virtual void move(void* const* src, void** dest) { *dest = *src; }

            virtual void* get_value(void** src) { return reinterpret_cast<void*>(src); }

        };

        template<typename T>
        struct remove_const
        {
            typedef T type;
        };

        template<typename T>
        struct remove_const<const T>
        {
            typedef T type;
        };

        template<typename T>
        struct big_any_policy : typed_base_any_policy<T>
        {
            virtual void static_delete( void** x)
            {
                if ( *x )
                    delete( *reinterpret_cast<T**>( x ) );
                *x = nullptr;
            }

            virtual void copy_from_value(void const* src, void** dest)
            {
                *dest = new T( *reinterpret_cast<T const*>( src ) );
            }

            virtual void clone( void* const* src, void** dest )
            {
              *dest = new T( **reinterpret_cast<T* const*>( src ) );
            }

            virtual void move(void* const* src, void** dest)
            {

                ( *reinterpret_cast<T**>( dest ) )->~T();
                ** reinterpret_cast<T**>( dest ) = **reinterpret_cast<T* const*>( src );
            }

            virtual void* get_value(void** src) { return *src; }
        };

        template<typename T>
        struct choose_policy
        {
            typedef big_any_policy<T> type;
        };

        template<typename T>
        struct choose_policy<T*>
        {
            typedef small_any_policy<T*> type;
        };

        struct any; //Forward declaration

        /// Choosing the policy for an any type is illegal, but should never happen.
        /// This is designed to throw a compiler error.
        template<>
        struct choose_policy<any>
        {
            typedef void type;
        };

        /// Specializations for small types.
#define SMALL_POLICY(TYPE) template<> struct choose_policy<TYPE> { typedef small_any_policy<TYPE> type; };
        SMALL_POLICY(signed char);
        SMALL_POLICY(unsigned char);
        SMALL_POLICY(signed short);
        SMALL_POLICY(unsigned short);
        SMALL_POLICY(signed int);
        SMALL_POLICY(unsigned int);
        SMALL_POLICY(signed long);
        SMALL_POLICY(unsigned long);
        SMALL_POLICY(float);
        SMALL_POLICY(bool);
        SMALL_POLICY(const signed char);
        SMALL_POLICY(const unsigned char);
        SMALL_POLICY(const signed short);
        SMALL_POLICY(const unsigned short);
        SMALL_POLICY(const signed int);
        SMALL_POLICY(const unsigned int);
        SMALL_POLICY(const signed long);
        SMALL_POLICY(const unsigned long);
        SMALL_POLICY(const float);
        SMALL_POLICY(const bool);
#undef SMALL_POLICY

        /// This function will return a different policy for each type.
        template<typename T>
        base_any_policy* get_policy()
        {
            static typename choose_policy<T>::type policy;
            return &policy;
        };

    }  //End of anyimpl namespace

    struct any
    {
    private:
        // fields
        anyimpl::base_any_policy* policy;
        void* object;

    public:
        /// Initializing constructor.
        template <typename T>
        //This used to be:
        //any(const T& x) : policy(anyimpl::get_policy<anyimpl::empty_any>()), object(nullptr) {
        //I am changing it to force the initial construction to use the small_policy:
        any(const T& x) : policy(anyimpl::get_policy<unsigned int>()), object(nullptr)
        {
            assign(x);
        }

        /// Empty constructor.
        //This used to be:
        //any() : policy(anyimpl::get_policy<anyimpl::empty_any>()), object(nullptr) {
        //But why should an empty 'any' receive a default 'big_any_policy'???
        //This starts calling 'new' and 'delete' under the hood.
        //So let's try the following to force a small_policy:
        any() : policy(anyimpl::get_policy<unsigned int>()), object(nullptr)
        {
        }

        /// Special initializing constructor for string literals.
        any(const char* x) : policy(anyimpl::get_policy<anyimpl::empty_any>()),
            object(nullptr)
        {
                assign(x);
        }

        /// Copy constructor.
        any(const any& x) : policy(anyimpl::get_policy<anyimpl::empty_any>()), object(nullptr)
        {
            assign(x);
        }

        /// Destructor.
        ~any()
        {
            policy->static_delete(&object);
        }

        /// Assignment function from another any.
        any& assign(const any& x)
        {
            reset();
            policy = x.policy;
            policy->clone(&x.object, &object);
            return *this;
        }

        /// Assignment function.
        template <typename T>
        any& assign(const T& x)
        {
            reset();
            policy = anyimpl::get_policy<T>();
            policy->copy_from_value(&x, &object);
            return *this;
        }

        /// Assignment operator.
        template<typename T>
        any& operator=(const T& x)
        {
            return assign(x);
        }

        any& operator=(const any & x)
        {
            /*policy = x.policy;
            policy->copy_from_value(&x.object, &object);
            return *this;*/
            reset();
            return assign(x);
        }

        any& operator()(const any & x)
        {
            policy = x.policy;
            policy->copy_from_value(&x.object, &object);
            return *this;
        }

        /// Assignment operator, specialed for literal strings.
        /// They have types like const char [6] which don't work as expected.
        any& operator=(const char* x)
        {
            return assign(x);
        }

        /// Utility functions
        any& swap(any& x)
        {
            std::swap(policy, x.policy);
            std::swap(object, x.object);
            return *this;
        }

        /// Cast operator. You can only cast to the original type.
        template<typename T>
        T& cast()
        {
            if (policy != anyimpl::get_policy<T>())
            {
                throw anyimpl::bad_any_cast();
            }
            T* r = reinterpret_cast<T*>(policy->get_value(&object));
            return *r;
        }

        /// Returns true if the any contains no value.
        bool empty() const
        {
            return policy == anyimpl::get_policy<anyimpl::empty_any>();
        }

        /// Frees any allocated memory, and sets the value to nullptr.
        void reset()
        {
            policy->static_delete(&object);
            //The following used to be:
            //policy = anyimpl::get_policy<anyimpl::empty_any>();
            //But why should the policy default to the big_any_policy?  Therefore,:
            policy = anyimpl::get_policy<unsigned int>();
        }

        /// Returns true if the two types are the same.
        bool isA(const any& x) const
        {
            return policy == x.policy;
        }

        template<typename T>
        bool isA()
        {
            return policy == anyimpl::get_policy<T>();
        }

    };
}

#endif /* __MB_ANY__ */
