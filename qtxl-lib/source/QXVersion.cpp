#include <QXVersion.h>
#include <util.h>

#include <tuple>

using namespace qtxl;

// -- Helper functionality

// --- General ---
Version::Version(uint major, uint minor, uint patch,
                 QStringList const& preReleaseIdentifiers,
                 QStringList const& buildMetadata,
                 QDate const& date) :
    m_major{major},
    m_minor{minor},
    m_patch{patch},
    m_preReleaseIdentifiers{preReleaseIdentifiers},
    m_buildMetadata{buildMetadata},
    m_date{date}{}

// --- Getters ---
uint
qtxl::Version::major() const{
    return m_major;
}

uint
qtxl::Version::minor() const {
    return m_minor;
}

uint
Version::patch() const {
    return m_patch;
}

QStringList
Version::preReleaseIdentifiers() const {
    return m_preReleaseIdentifiers;
}

QStringList
Version::buildMetaData() const {
    return m_buildMetadata;
}

QDate
Version::date() const {
    return m_date;
}

// --- Operators ---
bool
Version::operator==(Version const& other) const {

    using Tied = std::tuple<uint, uint, uint, QStringList, QDate> const;

     Tied left = std::tie(m_major, m_minor, m_patch,
                          m_preReleaseIdentifiers, m_date);
     Tied right = std::tie(other.m_major, other.m_minor, other.m_patch,
                           other.m_preReleaseIdentifiers, other.m_date);

    return left == right;
}

bool
Version::operator!=(Version const& other) const {
    return !operator==(other);
}

bool
Version::operator< (Version const& other) const {

    using Tied = std::tuple<uint, uint, uint, QStringList, QDate> const;

     Tied left = std::tie(m_major, m_minor, m_patch,
                          m_preReleaseIdentifiers, m_date);
     Tied right = std::tie(other.m_major, other.m_minor, other.m_patch,
                           other.m_preReleaseIdentifiers, other.m_date);

    return left < right;
}

bool
Version::operator> (Version const& other) const {
    return (!operator<(other) && operator!=(other));
}

bool
Version::operator<=(Version const& other) const {
    return(operator<(other) || operator==(other));
}

bool
Version::operator>=(Version const& other) const {
    return !operator<(other);
}

bool
Version::hasPreReleaseIdentifiers() const {
    return !m_preReleaseIdentifiers.isEmpty();
}

bool
Version::hasBuildMetaData() const {
    return !m_buildMetadata.isEmpty();
}

// --- Utility functions ---
bool
Version::compatibleWith(Version const& other) const {

    return m_major == other.m_major;
}

QString
Version::toQString() const {

    QString versionText = QString("%1.%2.%3").arg(m_major, m_minor, m_patch);

    if(hasPreReleaseIdentifiers()){
        versionText.append(PreReleaseIdOpener);
        versionText.append(m_preReleaseIdentifiers.join(IdentifierSeparator));
    }

    if(hasBuildMetaData()){
        versionText.append(BuildMetadataOpener);
        versionText.append(m_buildMetadata.join(IdentifierSeparator));
    }

    return versionText;
}
