#pragma once

#include <optional>
#include <algorithm>
#include "SemaElement.h"
#include "Decls.h"


template <class T>
class SemaContext : SemaElement
{
public:
    using ElementType = std::unique_ptr<T, void(*)(T*)>;
    using ContainerType = vec<ElementType>;

protected:
    template <class SearchFn> requires std::is_invocable_r_v<bool, SearchFn, const ElementType&>
    opt<T*> find(SearchFn fn) const
    {
        auto it = std::ranges::find_if(data, fn);
        return it != data.end() ? opt<T*>{(*it).get()} : std::nullopt;
    }

    void register_element(u_ptr<T> element)
    {
        ElementType ptr(element.release(), [](T* p) { delete p; });
        data.push_back(std::move(ptr));
    }

    bool remove_element(const T* element)
    {
        const auto before = data.size();
        auto e = std::ranges::remove_if(data, [&element](const auto& v) { return v.get() == element; });
        data.erase(e.begin(), e.end());
        return before != data.size();
    }

    ContainerType data;
};
