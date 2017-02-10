#pragma once

#include <qtxl_global.h>

#include <QDate>
#include <QObject> // for flag declaration
#include <QString>

namespace qtxl {

/**
 * @brief The Version class provides a container for version information and
 * utility functions for <a href=http://semver.org/>semantic versioning 2.0.0</a>.
 * A version may optionally contain a date stamp.
 * @author Fredo Erxleben
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

    enum StateFlag {
        Ok                          = 0,
        // --- Error flags ---
        InvalidPreReleaseIdentifier = 1 << 0,
        InvalidBuildMetadata        = 1 << 1,
        InvalidSemanticVersion      = 1 << 2
    };
    Q_DECLARE_FLAGS(StateFlags, StateFlag)
    Q_FLAG(StateFlags)
    // Operators for flags declared after the class

private:
    uint m_major;
    uint m_minor;
    uint m_patch;

    QStringList m_preReleaseIdentifiers;
    QStringList m_buildMetadata;

    QDate m_date;

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

    /**
     * @brief isValid checks whether this version is a correct and well-formed
     * semantic version.
     * @return <b>true</b> if this is a valid semantic version, <b>false</b>
     * otherwise.
     */
    bool isValid() const;

    /**
     * @brief hasBuildMetaData checks whether pre-release identifiers are available
     * for this version.
     * @return <b>true</b> if there are pre-release identifiers, <b>false</b>
     * otherwise.
     */
    bool hasPreReleaseIdentifiers() const;

    /**
     * @brief hasBuildMetaData checks whether build metadata are available
     * for this version.
     * @return <b>true</b> if there are build metadata, <b>false</b> otherwise.
     */
    bool hasBuildMetaData() const;

    /**
     * @brief compatibleWith checks whether this version is compatible with
     * another given version.
     * Two versions are considered compatible with each other if they share the
     * same major version number.
     * @param other is the version to check against.
     * @return <b>true</b> if both versions are compatible, <b>false</b>
     * otherwise.
     */
    bool compatibleWith(Version const& other) const;

    /**
     * @brief toQString creates a new QString representing this version.
     * The constructed string contains major, minor and patch version numbers.
     * If available, pre-release identifiers are appended first, then
     * build metadata.
     * The date is not included in the string representation
     * (unless provided manually in the build metadata).
     * @return a new QString representing this version according to the
     * SemVer 2.0.0 specification.
     */
    QString toQString() const;
};

// This is also required so flags can be combined with the "|" operator
Q_DECLARE_OPERATORS_FOR_FLAGS(Version::StateFlags)

}
