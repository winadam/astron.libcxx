//
// Created by adam on 8/6/18.
//

#pragma once

namespace astron   // open namespace
{
    class DistributedField {
    public:
        DistributedField(DCField* field);
    private:
        DCField* m_field;
    };
}




