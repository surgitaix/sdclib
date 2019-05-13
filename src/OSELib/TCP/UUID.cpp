#include "OSELib/TCP/UUID.h"
#include <cstring>
#include <regex>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <string>


const std::vector<std::string> split(const std::string& subject, const std::regex seperator) {
    std::vector<std::string> container{
        std::sregex_token_iterator(subject.begin(), subject.end(), seperator, -1),
        std::sregex_token_iterator()
    };
    return container;
};

const std::string join(const std::vector<std::string> & container)
{
    std::stringstream joinedStringStream;
    for (auto word : container)
    {
        joinedStringStream << word;
    }
    return joinedStringStream.str();
}

namespace Network {

UUID::UUID() {
    _timeLow = 0;
    _timeMid = 0;
    _timeHiAndVersion = 0;
    _clockSeqHighReservedAndLow = 0;
    std::memset(&_node, 0, sizeof (_node));
}

UUID::UUID(const std::string &uuidStringRepresentation)
{
    UUID();
    this->setFromString(uuidStringRepresentation);
}

UUID::UUID(const UUID& uuid)
{
    this->_timeLow = uuid._timeLow;
    this->_timeMid = uuid._timeMid;
    this->_timeHiAndVersion = uuid._timeHiAndVersion;
    this->_clockSeqHighReservedAndLow = uuid._clockSeqHighReservedAndLow;
    std::memcpy(&this->_node ,  &uuid._node, sizeof (_node));
}

UUID& UUID::operator=(const UUID& uuid) {
    this->_timeLow = uuid._timeLow;
    this->_timeMid = uuid._timeMid;
    this->_timeHiAndVersion = uuid._timeHiAndVersion;
    this->_clockSeqHighReservedAndLow = uuid._clockSeqHighReservedAndLow;
    std::memcpy(&this->_node ,  &uuid._node, sizeof (_node));
    return *this;
}

bool UUID::operator==(const UUID &uuid) const {
    if(_timeLow == uuid._timeLow &&
       _timeMid == uuid._timeMid &&
       _timeHiAndVersion == uuid._timeHiAndVersion &&
       _clockSeqHighReservedAndLow == uuid._clockSeqHighReservedAndLow)
    {
        for(unsigned int i = 0; i < sizeof (_node); ++i)
        {
            if(_node[i] != uuid._node[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool UUID::operator!=(const UUID &uuid) const {
    if(*this == uuid)
    {
        return false;
    }
    return true;
}

bool UUID::operator<(const UUID &uuid) const {
    if(this->toString() < uuid.toString()) {
        return true;
    }
    return false;
}

bool UUID::setFromString(const std::string &uuidStringRepresentation)
{

    if(validUUIDString(uuidStringRepresentation))
    {
        auto splitString = split(uuidStringRepresentation, std::regex("-"));
        this->_timeLow = static_cast<uint32_t> (std::stoul(splitString[0], nullptr, 16));
        this->_timeMid = static_cast<uint16_t> (std::stoul(splitString[1], nullptr, 16));
        this->_timeHiAndVersion = static_cast<uint16_t> (std::stoul(splitString[2], nullptr, 16));
        this->_clockSeqHighReservedAndLow = static_cast<uint16_t> (std::stoul(splitString[3], nullptr, 16));
        for (unsigned int i = 0; i < sizeof (_node); ++i)
        {
            std::string splitsplitString = splitString[4].substr(i*2, 2);
            this->_node[i] = static_cast<uint8_t>(std::stoul(splitsplitString, nullptr, 16));

        }
        return true;
    }
    return false;
}

const std::string UUID::toString() const {
    std::stringstream stringRepresentationStream;
    stringRepresentationStream << std::hex << this->_timeLow << "-" <<
                                  std::hex << this->_timeMid << "-" <<
                                  std::hex << this->_timeHiAndVersion << "-" <<
                                  std::hex << this->_clockSeqHighReservedAndLow << "-";
    for (unsigned int i = 0; i < sizeof (_node); ++i)
    {
        stringRepresentationStream << std::hex << static_cast<int>(_node[i]);
    }

    return stringRepresentationStream.str();
}

bool UUID::validUUIDString(const std::string &uuidStringRepresentation)
{
    std::regex uuidRegex("[0-9a-fA-F]{8}\\-[0-9a-fA-F]{4}\\-[0-9a-fA-F]{4}\\-[0-9a-fA-F]{4}\\-[0-9a-fA-F]{12}");
    if(std::regex_match(uuidStringRepresentation, uuidRegex))
    {
        return true;
    }
    return false;
}

bool UUID::isNil()
{
    if (_timeLow == 0 &&
        _timeMid == 0 &&
        _timeHiAndVersion == 0 &&
        _clockSeqHighReservedAndLow == 0)
    {
        for(auto data : _node)
            if(data != 0) {
                return false;
            }
    }
    return true;
}

template <typename T>
inline std::vector<uint8_t> pack (T& data, bool sytemIsBigEndian) {
    std::vector< uint8_t > destination;
    uint8_t * src = reinterpret_cast<uint8_t*>(&data);
    destination.insert (destination.end(), src, src + sizeof (T));
    if(sytemIsBigEndian)
    {
        std::reverse(destination.begin(), destination.end());
    }
    return destination;
}

const std::vector<uint8_t> UUID::toBytes() {
    std::vector<uint8_t> result;
    std::vector<uint8_t> tmp;
    tmp = pack(_timeLow, true);
    result.insert(result.end(), tmp.begin(), tmp.end()) ;
    tmp = pack(_timeMid, true);
    result.insert(result.end(), tmp.begin(), tmp.end()) ;
    tmp = pack(_timeHiAndVersion, true);
    result.insert(result.end(), tmp.begin(), tmp.end()) ;
    tmp = pack(_clockSeqHighReservedAndLow, true);
    result.insert(result.end(), tmp.begin(), tmp.end()) ;
    tmp = pack(_node, false);
    result.insert(result.end(), tmp.begin(), tmp.end());

    return result;
}


UUID UUID::createUUIDv5(UUID &UUIDNamespace, const std::string &name)
{
    std::cout << UUIDNamespace.toString() << std::endl;
    std::vector<uint8_t> UUIDNameSpaceBytes = UUIDNamespace.toBytes();
    std::vector<uint8_t> hexRepresentationOfName(name.begin(), name.end());
    std::vector<uint8_t> byteRepresentation;
    byteRepresentation.reserve(sizeof (UUIDNameSpaceBytes) + sizeof (hexRepresentationOfName));
    byteRepresentation.insert(byteRepresentation.end(), UUIDNameSpaceBytes.begin(), UUIDNameSpaceBytes.end());
    byteRepresentation.insert(byteRepresentation.end(), hexRepresentationOfName.begin(), hexRepresentationOfName.end());
    std::vector<uint8_t> outPutBuffer;
    outPutBuffer.reserve(20);
    SHA1(&(byteRepresentation)[0], byteRepresentation.size(), &(outPutBuffer)[0]);

    //Set Version to v5
    outPutBuffer[6] &= 0x0F;
    outPutBuffer[6] |= 0X05 << 4;
    //Set the two most significant bits (bits 6 and 7) of the clock_seq_hi_and_reserved to zero and one, respectively.
    outPutBuffer[8] &= 0x3F;
    outPutBuffer[8] |= 0x80;

    std::stringstream ss;

    ss << std::hex;

    for (unsigned int i = 0; i < 16; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(outPutBuffer[i]);
    }
    std::string stringRep = ss.str();

    stringRep.insert(8, "-");
    stringRep.insert(13, "-");
    stringRep.insert(18, "-");
    stringRep.insert(23, "-");

    return UUID(ss.str());

}


} // end Network
