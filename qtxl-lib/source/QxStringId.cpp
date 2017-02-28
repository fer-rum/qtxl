#include <QxStringId.h>

using namespace qtxl;

// --- Static members ---

QxStringId  const QxStringId::rootId    { {""} };
QChar       const QxStringId::separator {'/'};

// --- Constructors ---

QxStringId::QxStringId(QStringList representation) :
    m_internal{representation} {}

QxStringId::QxStringId() :
    m_internal{} {}

QxStringId::QxStringId(const QString& localId, const QxStringId& parentId) {

    if(!parentId.isValid()){
        return; // this will be invalid as well
    }

    if(localId.contains(separator)){
        return; // no separator allowed in local Ids
    }

    // construct a proper Id
    m_internal = parentId.m_internal;
    m_internal.append(localId);
}

QxStringId
QxStringId::directParentId() const {

    if(!isValid() || isRoot()){
        return QxStringId();
    }

    QStringList parentRepresentation = m_internal;
    parentRepresentation.removeLast();

    return QxStringId(parentRepresentation);
}

bool
QxStringId::isParentOf(const QxStringId& childId) const {

    if(!isValid() ||
       !childId.isValid() ||
       childId.isRoot()){ // root can not be the child of any id
        return false;
    }

    // parent level must be lesser then child level
    if(level() >= childId.level()){
        return false;
    }

    // Cut the part from the childs internal representation that is supposed to
    // be the parent representation and compare if it is.equal to the parents
    // internal representation.

    QStringList parentSubPart = childId.m_internal.mid(0, level() + 1);
    // level() +1 to offset levels being counted from 0

    if(parentSubPart != m_internal){
        return false;
    }

    return true;
}

bool
QxStringId::isDirectParentOf(const QxStringId& childId) const {

    if(!isValid() ||
       !childId.isValid() ||
       childId.isRoot()){ // root can not be the child of any id
        return false;
    }

    // direct parent level must be lesser by one then child level
    if(level() != childId.level() - 1){
        return false;
    }

    // Cut the part from the childs internal representation that is supposed to
    // be the parent representation and compare if it is.equal to the parents
    // internal representation.

    QStringList parentSubPart = childId.m_internal;
    parentSubPart.removeLast();
    // level() +1 to offset levels being counted from 0

    if(parentSubPart != m_internal){
        return false;
    }

    return true;
}

int QxStringId::level() const {

    return m_internal.size() - 1;
    // 1 has to be subtracted, since the root Id has an internal representation
    // containing an empty string. This would give a size of 1, which incurrs an
    // offset. Also, this way the return value becomes negative for an invalid
    // Id.
}

bool
QxStringId::isValid() const {

    if(isRoot()) {
        // root is always valid
        return true;
    }

    if(level() < 1){
        // level < 0 -> invalid
        // level == 0 -> did not equal root before
        // but has root level, which is not allowed.
        return false;
    }

    return true;
}

bool
QxStringId::isRoot() const {
    return this->m_internal == rootId.m_internal;
}

QString
QxStringId::toQString(QxStringId::Representation usedRepresentation) const {

    if(!isValid()){
        return QString();
    }

    switch(usedRepresentation){
    case Representation::GlobalRepresentation :
        return m_internal.join(separator);
    case Representation::LocalRepresentation:
        return m_internal.last();
    default:
        return QString();
    }
}

QString
QxStringId::toQString() const {

    return toQString(Representation::GlobalRepresentation);
}

bool
QxStringId::operator==(const QxStringId& other) const {

    // Invalid is invalid, no matter what.
    if( !isValid() && !other.isValid()){
        return true;
    }

    return (m_internal == other.m_internal);
}
