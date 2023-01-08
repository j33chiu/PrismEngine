#pragma once

#include <optional>
#include <functional>
#include <type_traits>

#include "Exception.h"

namespace prism {

template <class T>
concept IsPointer = std::is_pointer_v<T>;

template <class T>
concept IsNotPointer = !std::is_pointer_v<T>;

/**
 * wrapper class that holds a resource and calls a set function when it goes out of scope
 * use cases: file i/o, destructor functions on other resources (like windows, release etc...)
 * uses:
 * pointer types (for modifying, storing, reading, easy to add "delete" in destructor function if init with "new")
 * non-pointer types (for storing, reading, can modify, but requires (&autoResource).modifyingFunc())
 *      modifying can be hassle, so ideal if resource can be copied without repercussions
*/
template<class T>
class AutoResource {

public:
    AutoResource() 
    {}

    AutoResource(T resource) {
        this->resource.emplace(resource);
    }

    AutoResource(T resource, std::function<void(T)> destructor) {
        this->resource.emplace(resource);
        if (destructor)
            this->destructor.emplace(destructor);
    }

    ~AutoResource() {
        if (destructor.has_value() && resource.has_value()) {
            destructor.value()(resource.value());
        }
    }

    void swap(AutoResource<T> &otherResource) noexcept {
        std::swap(resource, otherResource.resource);
        std::swap(destructor, otherResource.destructor);
    }

    // disallow copy constructor:
    AutoResource(const AutoResource<T> &autoResource) = delete;

    // disallow reassignment
    AutoResource<T> &operator=(AutoResource<T> &) = delete;

    // move constructor:
    AutoResource(AutoResource<T> &&otherResource) noexcept
        : AutoResource(nullptr, nullptr)
    {
        swap(otherResource);
    }

    // move assignment:
    AutoResource<T> &operator=(AutoResource<T> &&otherResource) 
    {
        AutoResource<T> newAutoResource(std::move(otherResource));

        swap(newAutoResource);

        return *this;
    }

    // get resource:
    T get() const {
        if (!resource.has_value()) 
            throw Exception("AutoResource does not contain valid resource: cannot return resource");
        return resource.value();
    }

    // address of resource
    T *operator&() {
        if (!resource.has_value()) 
            throw Exception("AutoResource does not contain valid resource: cannot return address of resource");
        return std::addressof(resource.value());
    }

    // overload the -> operator, but only for resources that are passed as pointers
    T operator->() const requires IsPointer<T> {
        if (!resource.has_value()) 
            throw Exception("AutoResource does not contain valid resource: cannot return pointer to resource");
        return resource.value();
    }

    // overload bool operator, to check if AutoResource object manages an actual resource
    explicit operator bool() const noexcept {
        return resource.has_value();
    }

    // overload cast operator
    operator T() const {
        if (!resource.has_value()) 
            throw Exception("AutoResource does not contain valid resource: cannot cast resource");
        return resource.value();
    }

private:
    // remove constructors for nullptr and NULL resources
    AutoResource(std::nullptr_t resource);
    AutoResource(std::nullptr_t resource, std::nullptr_t destructor) 
        : AutoResource()
    {}
    AutoResource(std::nullptr_t resource, std::function<void(T)> destructor);

    std::optional<T> resource;
    std::optional<std::function<void(T)>> destructor;

};

}