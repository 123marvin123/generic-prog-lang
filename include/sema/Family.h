//
// Created by Marvin Haschker on 23.03.25.
//

#ifndef FAMILY_H
#define FAMILY_H

#include "sema/SemaIdentifier.h"

struct Family final : SemaIdentifier {
    Family(const std::string& name, const Namespace* ns)
        : SemaIdentifier(name, ns)
    {
    }



};

#endif //FAMILY_H
