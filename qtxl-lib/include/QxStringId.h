#pragma once

#include <qtxl_global.h>
#include <QxInterfaces.h>

#include <QList>
#include <QObject> // for QGadget
#include <QString>


namespace qtxl {

class QTXLSHARED_EXPORT QxStringId :
    public IsQStringConvertible {

    Q_GADGET

private:

    /**
     * @brief m_internal is where an id stores all its sub-parts from which
     * different representations can be derived.
     */
    QStringList m_internal;

    /**
     * @brief QStringId is the internally used way of initializing the Id.
     * This is required to allow a proper initialization of @see rootId
     * @param representation is the representation to be used in this Id.
     */
    QxStringId(QStringList representation);

public:

    enum Representation {
        LocalRepresentation,
        GlobalRepresentation
    };
    Q_ENUM(Representation);

    /**
     * @brief QStringId constructs an invalid identifier.
     */
    QxStringId();
    QxStringId(QString const& localId, QxStringId const& directParentId);

    /**
     * @brief rootId is the parent of all valid identifiers.
     * There can only be one.
     * It is constructed from a single empty, non-null string.
     * The root Id is the only Id that may have a level of 0.
     *
     */
    static QxStringId const rootId;

    /**
     * @brief separator is the character that is put between the local Ids of
     * the different levels to form a global Id.
     */
    static QChar const separator;

    /**
     * @brief parentId attempts to obtain the Id of the direct parent.
     * Invalid Ids and the root Id do not have a valid parent.
     * @return
     */
    QxStringId directParentId() const;

    /** Evaluates whether this id is a parent - direct or transitive - of the
     * provided child id.
     * @brief isParentOf
     * @param childId
     * @return true, if this id is a parent id of the provided child id,
     * false otherwise;
     */
    bool isParentOf(QxStringId const& childId) const;

    /** Evaluates whether this id is a direct parent -not transitive - of the
     * provided child id.
     * @brief isDirectParentOf
     * @param childId
     * @return true, if this id is a direct parent id of the provided child id,
     * false otherwise;
     */
    bool isDirectParentOf(QxStringId const& childId) const;

    /**
     * @brief level returns the hierarchical level of this Id.
     * The root id has level 0. Each other Id has one level more than its
     * parent.
     * Invalid ids have a negative level.
     * @return
     */
    int level() const;

    /**
     * @brief isValid determines whether this QStringId is considered to be
     * valid. A valid Id is a (transitive) child of the root Id and has a level
     * above 0 (except for the rootId itself).
     * The root Id is always valid.
     * @return
     */
    bool isValid() const;
    bool isRoot() const;

    /**
     * @brief toQString converts the identifier to a QString based on the
     * selected representation.
     * @param usedRepresentation
     * @return a null @see QString if the identifier is not valid. If a global
     * representation was selected, the returned QString contains all local ids
     * of all parents in hierarchical order, beginning with the root identifier.
     * All local identifiers are joined by the @see separator character.
     */
    QString toQString(Representation usedRepresentation) const;

    /**
     * @brief toQString is an alias for @see toQString(Representation::Global)
     * @return the global representation of the identifier as QString.
     */
    QString toQString() const override;

    // --- Operators ---
    bool operator==(QxStringId const& other) const;
};

}
