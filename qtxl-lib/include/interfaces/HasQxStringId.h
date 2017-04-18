#pragma once

#include <QxStringId.h>

namespace qtxl {

class HasQxStringId {

private:
    QxStringId m_id;

protected:

    HasQxStringId(QxStringId const& id) :
        m_id{id}{};

public:
    QxStringId id() const {
        return m_id;
    }

};

} // namespace qtxl
