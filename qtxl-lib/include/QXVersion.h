#pragma once

#include <qtxl_global.h>

#include <QDate>
#include <QObject> // for flag declaration
#include <QString>

namespace qtxl {

/**
 * @brief The Version class provides a container for version information and
 * utility functions for <a href=http://semver.org/>semantic versioning as
 * described by Tom Preston-Werner</a>.
 * A version may optionally contain a date stamp.
 */
class QTXLSHARED_EXPORT Version {

    Q_GADGET // required for flag metatyping

public:

    /**
     * @brief IdentifierSeparator is the character used to separate the
     * identifiers in the build metadata and pre-release identifiers.
     */
    static const char IdentifierSeparator   = '.';
    static const char BuildMetadataOpener   = '+';
    static const char PreReleaseIdOpener    = '-';

    enum class StateFlag {
        Ok                          = 0x00,
        // --- Error flags ---
        InvalidPreReleaseIdentifier = 0x01,
        InvalidBuildMetadata        = 0x02,
        InvalidSemanticVersion      = 0x04
    };
    Q_DECLARE_FLAGS(StateFlags, StateFlag)
    Q_FLAG(StateFlags)

private:
    uint m_major;
    uint m_minor;
    uint m_patch;
    QDate m_date;
    QStringList m_preReleaseIdentifiers;
    QStringList m_buildMetadata;
    StateFlags m_state;

public:

    Version(uint major          = 0,
            uint minor          = 0,
            uint patch          = 0,
            QStringList const& preReleaseIdentifiers = {},
            QStringList const& buildMetadata = {},
            QDate const& date   = {});

    ~Version() = default;
    Version(Version const& other) = default;

    // --- Getters ---
    uint major() const;
    uint minor() const;
    uint patch() const;
    QStringList preReleaseIdentifiers() const;
    QStringList buildMetaData() const;
    QDate date() const;

    // --- Operators ---

    bool operator==(Version const& other) const;
    bool operator!=(Version const& other) const;

    bool operator< (Version const& other) const;
    bool operator> (Version const& other) const;
    bool operator<=(Version const& other) const;
    bool operator>=(Version const& other) const;

    // --- Utility functions ---

    // TODO: Documentation
    bool hasPreReleaseIdentifiers() const;

    // TODO: Documentation
    bool hasBuildMetaData() const;

    // TODO: Documentation
    bool compatibleWith(Version const& other) const;

    // TODO: Documentation
    QString toQString() const;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Version::StateFlags)

}
