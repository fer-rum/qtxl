#include <QxVersion.h>
#include <QxUtil.h>

#include <QRegularExpression>

#include <tuple>

using namespace qtxl;

// -- Helper functionality
namespace {
// These are helpers for this compile unit only,
// thus they are wrapped in an anonymous namespace.

/*
 * A pre-release identifier can be one of the following:
 * * purely numeric without a leading zero
 * * alphanumeric with a leading zero.
 */
const QRegularExpression
preReleaseRegex{R"regex(^([1-9][0-9]*)|([0-9]*[A-Za-z-]+[0-9A-Za-z-]*)$)regex",
                QRegularExpression::OptimizeOnFirstUsageOption};

/*
 * A build metadata identifier can be
 * * alphanumeric or purely numeric with leading zero.
 */
const QRegularExpression
buildMetadataRegex{R"regex(^[0-9A-Za-z-]+$)regex",
                  QRegularExpression::OptimizeOnFirstUsageOption};

bool
isValidIdentifier(QString const& identifier,
                  QRegularExpression const& usedRegex){

    // Seee SemVer spec §9, §10

    if(identifier.isEmpty()){ // Identifiers are not allowed to be empty
        return false;
    }

    QRegularExpressionMatch match = usedRegex.match(identifier);
    if(!match.hasMatch()){ //
        return false;
    }

    return true;
}

} // end anonymous namespace

// --- General ---
QxVersion::QxVersion(uint major, uint minor, uint patch,
                 QStringList const& preReleaseIdentifiers,
                 QStringList const& buildMetadata,
                 QDate const& date) :
    m_major{major},
    m_minor{minor},
    m_patch{patch},
    m_preReleaseIdentifiers{preReleaseIdentifiers},
    m_buildMetadata{buildMetadata},
    m_date{date},
    m_state{StateFlag::Ok}{

    // check the validity of the version numbers
    if( (m_major == 0) &&
        (m_minor == 0) &&
        (m_patch == 0)) {
        m_state |= StateFlag::InvalidSemanticVersion;
    }

    // check the validity of the pre-release identifiers
    for(QString const& identifier : m_preReleaseIdentifiers){
        if(!isValidIdentifier(identifier, preReleaseRegex)){
            m_state |= StateFlag::InvalidPreReleaseIdentifier;
            break;
        }
    }

    // check the validity of the build metadata
    for(QString const& identifier : m_buildMetadata){
        if(!isValidIdentifier(identifier, buildMetadataRegex)){
            m_state |= StateFlag::InvalidBuildMetadata;
            break;
        }
    }
}

// --- Getters ---
uint
qtxl::QxVersion::major() const{
    return m_major;
}

uint
qtxl::QxVersion::minor() const {
    return m_minor;
}

uint
QxVersion::patch() const {
    return m_patch;
}

QStringList
QxVersion::preReleaseIdentifiers() const {
    return m_preReleaseIdentifiers;
}

QStringList
QxVersion::buildMetaData() const {
    return m_buildMetadata;
}

QDate
QxVersion::date() const {
    return m_date;
}

// --- Operators ---
bool
QxVersion::operator==(QxVersion const& other) const {

    using Tied = std::tuple<uint, uint, uint, QStringList, QDate> const;

     Tied left = std::tie(m_major, m_minor, m_patch,
                          m_preReleaseIdentifiers, m_date);
     Tied right = std::tie(other.m_major, other.m_minor, other.m_patch,
                           other.m_preReleaseIdentifiers, other.m_date);

    return left == right;
}

bool
QxVersion::operator!=(QxVersion const& other) const {
    return !operator==(other);
}

bool
QxVersion::operator< (QxVersion const& other) const {

    using Tied = std::tuple<uint, uint, uint, QStringList, QDate> const;

     Tied left = std::tie(m_major, m_minor, m_patch,
                          m_preReleaseIdentifiers, m_date);
     Tied right = std::tie(other.m_major, other.m_minor, other.m_patch,
                           other.m_preReleaseIdentifiers, other.m_date);

    return left < right;
}

bool
QxVersion::operator> (QxVersion const& other) const {
    return (!operator<(other) && operator!=(other));
}

bool
QxVersion::operator<=(QxVersion const& other) const {
    return(operator<(other) || operator==(other));
}

bool
QxVersion::operator>=(QxVersion const& other) const {
    return !operator<(other);
}

bool
QxVersion::hasPreReleaseIdentifiers() const {
    return !m_preReleaseIdentifiers.isEmpty();
}

bool
QxVersion::hasBuildMetaData() const {
    return !m_buildMetadata.isEmpty();
}

// --- Utility functions ---

bool
QxVersion::isValid() const {

    return (m_state == StateFlag::Ok);
}

bool
QxVersion::compatibleWith(QxVersion const& other) const {

    return m_major == other.m_major;
}

QString
QxVersion::toQString() const {

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
